#include "zenom.h"

//==============================================================================
// MessageHandler::MessageHandler
//==============================================================================
MessageHandler::MessageHandler( Zenom* zenomProgram )
{
    zenom = zenomProgram;
    runFlag = true;
}

//==============================================================================
// MessageHandler::run
//==============================================================================
void MessageHandler::run()
{


    setPeriodic(TM_NOW, ONESECOND / 30 );
    while(runFlag)
    {
        waitPeriod();
        // Control Baseden stop mesajı gelene kadar beklenir
        if( !zenom->guiComQueueReceiver->receiveStopMessage())
        {
            cout << "Stop Mesahi geldi" << endl;
            zenom->stop();
        }

        zenom->selectWatch->updateSevenSegments();

        zenom->progressBar->position(*(zenom->controlHeapAddress));

        // Program sonsuz zamanda calisirken gecen sure gosterilir.
        if( zenom->durationInput->ivalue() )
            snprintf(timeInfo,255,"Remaining Time: %.2f",
                    zenom->durationInput->ivalue() - *(zenom->controlHeapAddress));
        else
            snprintf(timeInfo,255,"Elapsed Time: %.2f", *(zenom->controlHeapAddress));
        zenom->progressBar->label(timeInfo);

        for( int i = 0; i < zenom->sceneWindows.getNumElements(); ++i)
            zenom->sceneWindows.getElement(i)->update();
    }
    cout << "CALISMA BITTI--------------------------------" << endl;

}

//==============================================================================
// MessageHandler::stopThread
//==============================================================================
void MessageHandler::stopThread()
{
    runFlag = false;
}






