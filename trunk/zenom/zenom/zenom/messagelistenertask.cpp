#include "messagelistenertask.h"
#include <MessageQueueXn.h>
#include <datarepository.h>

MessageListenerTask::MessageListenerTask( Zenom* pZenom )
{
    mZenom = pZenom;
}

void MessageListenerTask::run()
{
    while( true )
    {
        StateRequest stateRequest;
        if( DataRepository::instance()->readState( &stateRequest ) >= 0 )
        {
            switch (stateRequest)
            {

                case R_INIT:
                    mZenom->mMutex.lock();
                    mZenom->mWaitCondition.wakeAll();
                    mZenom->mMutex.unlock();
                    break;

                case R_STOP:
                    QMetaObject::invokeMethod(mZenom, "on_stopButton_clicked");
                    break;

                default:
                    std::cout << "Message Listener Unhandled message" << std::endl;
                    break;
            }
        }
    }
}
