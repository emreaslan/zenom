#include "zenom.h"

//==============================================================================
// WindowUpdater::WindowUpdater
//==============================================================================
WindowUpdater::WindowUpdater( Zenom* znm )
{
    runFlag = true;
    zenom = znm;
    printf("GUI RTNET waiting start message\n");
}



//==============================================================================
// WindowUpdater::run
//==============================================================================
void WindowUpdater::run()
{
    char msgBuf[MAXARRAYSIZE];
    setPeriodic(TM_NOW, ONESECOND / 10 );
    while(runFlag)
    {

        waitPeriod();
        rt_printf("GUI RTNET waiting start message\n");
        zenom->rtnetComQueueReceiver->receiveMessage( msgBuf );
        if( !strcmp ( QUEUESTART , msgBuf ) )
        {
            cout << "RTNET start mesaji geldi" << endl;
            snprintf(msgBuf,MAXARRAYSIZE," ");
            zenom->start();
        }
        else if( !strcmp ( QUEUEPAUSE , msgBuf ) )
        {
            cout << "RTNET pause mesaji geldi" << endl;
            snprintf(msgBuf,MAXARRAYSIZE," ");
            zenom->pause();

        }
        else if( !strcmp ( QUEUESTOP , msgBuf ) )
        {
            cout << "RTNET stop mesaji geldi" << endl;
            snprintf(msgBuf,MAXARRAYSIZE," ");
            zenom->stop();

        }
           
    }

}

//==============================================================================
// WindowUpdater::stopThread
//==============================================================================
void WindowUpdater::stopThread()
{
    runFlag = false;
}






