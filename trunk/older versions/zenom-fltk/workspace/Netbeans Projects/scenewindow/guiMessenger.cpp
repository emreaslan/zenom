//==============================================================================
// guiMessenger.cpp    - Message send and receive operations
//
// Author        :
// Version       : 1.0.00 (Agustos 2009)
// Compatibility : XENOMAI, GCC
//==============================================================================

#include "guiMessenger.h"


//==============================================================================
// guiMessenger::guiMessenger
//==============================================================================
guiMessenger::guiMessenger(char* nm,bool gui)
{
    isGui = gui;
    applicationName = new char[NAMELENGTH];
    queueName = new char[NAMELENGTH];
    strcpy( applicationName , nm);

    sprintf( queueName,"%sQueue",applicationName );

    guiComQueue = new MessageQueueXn();

    if (isGui)
    {
        if (  guiComQueue->bind( queueName ) )
        {
            cout << "MessageQueue bind error" << endl;
            cout << "Error : " << strerror (guiComQueue->getErrnoError() ) << endl;
        }
    }
    else
    {
        if (  guiComQueue->create( queueName,sizeof(char) * MAXARRAYSIZE , Q_UNLIMITED , Q_SHARED ) )
        {
            cout << "MessageQueue create error" << endl;
            cout << "Error : " << strerror (guiComQueue->getErrnoError() ) << endl;
        }
    }
}


//==============================================================================
// guiMessenger::~guiMessenger
//==============================================================================
guiMessenger::~guiMessenger()
{
    delete applicationName;

    if( isGui)
        guiComQueue->unbind();
    else
        guiComQueue->deleteQueue();

    delete guiComQueue;
}


//==============================================================================
// guiMessenger::sendStartMessage
//==============================================================================
int guiMessenger::sendStartMessage()
{
    return guiComQueue->write( QUEUESTART , MAXARRAYSIZE , Q_NORMAL );
}

//==============================================================================
// guiMessenger::sendStopMessage
//==============================================================================
int guiMessenger::sendStopMessage()
{
    return guiComQueue->write( QUEUESTOP , MAXARRAYSIZE , Q_NORMAL );
}

//==============================================================================
// guiMessenger::sendPauseMessage
//==============================================================================
int guiMessenger::sendPauseMessage()
{
    return guiComQueue->write( QUEUEPAUSE , MAXARRAYSIZE , Q_NORMAL );
}

//==============================================================================
// guiMessenger::sendUnbindMessage
//==============================================================================
int guiMessenger::sendUnbindMessage()
{
    return guiComQueue->write( QUEUEUNBIND , MAXARRAYSIZE , Q_NORMAL );
}

//==============================================================================
// guiMessenger::sendBindMessage
//==============================================================================
int guiMessenger::sendBindMessage()
{
    return guiComQueue->write( QUEUEBIND , MAXARRAYSIZE , Q_NORMAL );
}

//==============================================================================
// guiMessenger::sendActiveMessage
//==============================================================================
int guiMessenger::sendActiveMessage()
{
    return guiComQueue->write( QUEUEACTIVE , MAXARRAYSIZE , Q_NORMAL );
}

//==============================================================================
// guiMessenger::receiveStartMessage
//==============================================================================
int guiMessenger::receiveStartMessage()
{
    char msgBuf[ MAXARRAYSIZE ];
    int checkError = guiComQueue->read( msgBuf, MAXARRAYSIZE ,TM_INFINITE );
    if(  checkError < 0 )
        return checkError;

    cout << queueName <<" Start Message msgBuf : " <<  msgBuf << endl;

    if( strcmp ( msgBuf , QUEUESTART ) ==  0 )
        return 0;
   else
        return receiveStartMessage();

}

//==============================================================================
// guiMessenger::receiveStopMessage
//==============================================================================
int guiMessenger::receiveStopMessage()
{
    char msgBuf[ MAXARRAYSIZE ];
    int checkError = guiComQueue->read( msgBuf, MAXARRAYSIZE, TM_NONBLOCK );
    if( checkError < 0 )
        return checkError;

    //cout << queueName << " Stop Message msgBuf : " <<  msgBuf << endl;

    if( strcmp ( msgBuf , QUEUESTOP ) ==  0 )
        return 0;
    else
        return -1;
}


//==============================================================================
// guiMessenger::receivePauseMessage
//==============================================================================
int guiMessenger::receivePauseMessage()
{
    char msgBuf[ MAXARRAYSIZE ];
    int checkError;
    if( !(checkError = guiComQueue->read( msgBuf, MAXARRAYSIZE ,TM_NONBLOCK ) ) )
        return checkError;

    cout << queueName << " Pause Message msgBuf : " <<  msgBuf << endl;

    if( strcmp ( msgBuf , QUEUEPAUSE ) ==  0 )
        return 0;
    else
        return -1;
}

//==============================================================================
// guiMessenger::receiveUnbindMessage
//==============================================================================
int guiMessenger::receiveUnbindMessage()
{
    char msgBuf[ MAXARRAYSIZE ];
    int checkError = guiComQueue->read( msgBuf, MAXARRAYSIZE ,TM_INFINITE );
    if(  checkError < 0 )
        return checkError;

    cout << queueName << " Unbind Message msgBuf : " <<  msgBuf << endl;

    if( strcmp ( msgBuf , QUEUEUNBIND ) ==  0 )
        return 0;
   else
        return receiveUnbindMessage();

}

//==============================================================================
// guiMessenger::receiveBindMessage
//==============================================================================
int guiMessenger::receiveBindMessage()
{
    char msgBuf[ MAXARRAYSIZE ];
    int checkError = guiComQueue->read( msgBuf, MAXARRAYSIZE ,TM_INFINITE );
    if(  checkError < 0 )
        return checkError;

    cout << queueName << " Bind Message msgBuf : " <<  msgBuf << endl;

    if( strcmp ( msgBuf , QUEUEBIND ) ==  0 )
        return 0;
   else
        return receiveBindMessage();
}

//==============================================================================
// guiMessenger::receiveActiveMessage
//==============================================================================
int guiMessenger::receiveActiveMessage()
{
    char msgBuf[ MAXARRAYSIZE ];
    int checkError = guiComQueue->read( msgBuf, MAXARRAYSIZE ,TM_INFINITE );
    if(  checkError < 0 )
        return checkError;

    cout << queueName << " Active Message msgBuf : " <<  msgBuf << endl;

    if( strcmp ( msgBuf , QUEUEACTIVE ) ==  0 )
        return 0;
   else
        return receiveActiveMessage();
}


//==============================================================================
// guiMessenger::receiveMessage
//==============================================================================
int guiMessenger::receiveMessage(char *msgBuf)
{
    return guiComQueue->read( msgBuf, MAXARRAYSIZE , TM_NONBLOCK  );
    //cout << queueName << " Receive Message msgBuf : " <<  msgBuf << endl;
}


//==============================================================================
// guiMessenger::sendMessage
//==============================================================================
int guiMessenger::sendMessage(char *msgBuf)
{
    return guiComQueue->write( msgBuf , MAXARRAYSIZE , Q_NORMAL );

}



