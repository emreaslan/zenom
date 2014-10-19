#include "zenomwindow.h"

//==============================================================================
// MessageHandler::MessageHandler
//==============================================================================
MessageHandler::MessageHandler( ZenomWindow* zenomProgram )
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

        zenom->sceneWindowManager.update();
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






