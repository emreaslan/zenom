/*
 * LoopTask.cpp
 *
 *  Created on: Apr 4, 2012
 *      Author: root
 */

#include "looptask.h"
#include <datarepository.h>
#include "arduinomanager.h"

LoopTask::LoopTask( ControlBase* pControlBase )
{
	mControlBase = pControlBase;
}

void LoopTask::run()
{
	RTIME now, previous;
	RTIME elapsedTime = 0;
    unsigned long totalOverruns = 0;
    unsigned long overruns;
	double frequency = mControlBase->mFrequency;
	double duration = mControlBase->mDuration;

	this->setPeriodic( TM_NOW , SECOND_TO_NANO / frequency );
	previous = rt_timer_read();

    while( mControlBase->mState != STOPPED )
    {
        waitPeriod( &overruns );
        totalOverruns += overruns;
        mControlBase->setOverruns( totalOverruns );

        if( mControlBase->mState != PAUSED )
        {
            mControlBase->mArduinoManager->doLoopPreProcess();
            mControlBase->doloop();
            mControlBase->mArduinoManager->doLoopPostProcess();
            mControlBase->logVariables( elapsedTime );
            mControlBase->syncMainHeap();

            now = rt_timer_read();
            elapsedTime += (now - previous);
            mControlBase->setElapsedTime( elapsedTime );
            previous = now;
        }
        else
        {
            now = rt_timer_read();
            previous = now;
        }

        if( mControlBase->mElapsedTimeInSecond > duration )
        {
            DataRepository::instance()->sendStateRequest( R_STOP );
            break;
        }

	}
}
