#include "ControlBase.h"


//==============================================================================
// ControlBase::ControlBase
//==============================================================================
ControlBase::ControlBase(int argc, char* argv[])
{
    applicationName = new char[NAMELENGTH];
    int pathPoint = -1;
    isGUI = false;
    zenomState = STOP;
    rtMessageTask = NULL;
    isStartMessageReceived = false;
    rtnetListener = NULL;

    copyConfigFileName((char*)"[configFileName]");

    for(int counter = 0 ; counter < LINELENGTH ; ++counter )
    {
        if( ( argv[0][counter] == ' ' ) || ( argv[0][counter] == '\000' ) )
            break;
        else if( argv[0][counter] == '/' )
            pathPoint = counter;
    }

    strcpy (this->applicationName , &(argv[0][pathPoint+1]) ) ;

    if (argc == 1)
    {
         copyConfigFileName ( argv[0] );
         cout << "ControlBase started in console Mode" << endl;

    }
    else if( argc == 2 )
    {
        if( strcmp (argv[1] , HELPCOMMAND ) == 0)
        {
            showHelp();
            exit(-1);
        }
        else
        {
            showUsage();
            exit(-1);
        }
    }
    else if (argc == 3)
    {
        if (strcmp (argv[1] , GUICOMMAND ) == 0)
        {
            copyConfigFileName ( argv[2] );
            isGUI = true;
            cout << "ControlBase started in GUI Mode" << endl;
        }
        else
        {
             showUsage();
             exit(-1);
        }
    }
    else
    {
         showUsage();
         exit(-1);
    }

    
}

//==============================================================================
// ControlBase::~ControlBase
//==============================================================================
ControlBase::~ControlBase()
{
    if( isGUI )
        delete guiComQueueReceiver;


    delete config;
    delete controlHeap;
    delete applicationName;
    delete configFileName;

    for (int counter = 0 ; counter < controlVariableArray.getNumElements() ; ++counter )
        delete controlVariableArray.getElement(counter);

    for (int counter = 0 ; counter < logVariableArray.getNumElements() ; ++counter )
        delete logVariableArray.getElement(counter);

}





//==============================================================================
// ControlBase::copyToSourceHeap
//==============================================================================
void ControlBase::copyToSourceHeap()
{
    *controlHeapAddress = elapsedTimeSecond;
    controlHeapAddress[3] = mOverrunCount;
    
    double *heapPtr;
    double *valuePtr;
    int *intValuePtr;
    for(int i = 0; i < logVariableArray.getNumElements(); ++i)
    {
        heapPtr = logVariableArray.getElement(i)->getSourceAddress();

        if( logVariableArray.getElement(i)->isInteger() )
        {
            intValuePtr = logVariableArray.getElement(i)->getIntElementPtr();
            for(int counter = 0; counter < logVariableArray.getElement(i)->getSize() ;++counter)
                heapPtr[counter] = (double)intValuePtr[counter];
        }
        else
        {
            valuePtr = logVariableArray.getElement(i)->getElementPtr();
            for(int counter = 0; counter < logVariableArray.getElement(i)->getSize() ;++counter)
                heapPtr[counter] = valuePtr[counter];
        }
        
    }
}

//==============================================================================
// ControlBase::registerMessageObject
//==============================================================================
void ControlBase::registerMessageObject(RTMessage& messenger)
{
    messengerArray.appendElement(&messenger);
}



//==============================================================================
// ControlBase::registerLogVariable
//==============================================================================
void ControlBase::registerLogVariable(double *variable, const char* nm, const char* desc,int row,int col)
{
    LogVariable *ptr = new LogVariable( variable, nm ,desc , row ,col );

    this->logVariableArray.appendElement(ptr);
}

//==============================================================================
// ControlBase::registerLogVariable
//==============================================================================
void ControlBase::registerLogVariable(int *variable, const char* nm, const char* desc,int row,int col)
{
    LogVariable *ptr = new LogVariable( variable, nm ,desc , row ,col );

    this->logVariableArray.appendElement(ptr);
}


//==============================================================================
// ControlBase::registerLogVariable
//==============================================================================
void ControlBase::registerLogVariable(double **variable, const char* nm, const char* desc,int row,int col)
{
    LogVariable *ptr = new LogVariable( &(variable[0][0]), nm ,desc , row ,col );

    this->logVariableArray.appendElement(ptr);
}


//==============================================================================
// ControlBase::registerLogVariable
//==============================================================================
void ControlBase::registerLogVariable(int **variable, const char* nm, const char* desc,int row,int col)
{
    LogVariable *ptr = new LogVariable( &(variable[0][0]), nm ,desc , row ,col );

    this->logVariableArray.appendElement(ptr);
}


//==============================================================================
// ControlBase::registerLogVariable
//==============================================================================
void ControlBase::registerLogVariable(int &variable, const char* nm, const char* desc,int row,int col)
{
    LogVariable *ptr = new LogVariable(&variable, nm, desc, row, col);

    this->logVariableArray.appendElement(ptr);
}

//==============================================================================
// ControlBase::registerLogVariable
//==============================================================================
void ControlBase::registerLogVariable(double &variable, const char* nm, const char* desc)
{
    this->registerLogVariable( &variable,nm,desc,1,1);
}


//==============================================================================
// ControlBase::registerLogVariable
//==============================================================================
void ControlBase::registerLogVariable(MatrixBase<double>& varMatrix, const char* nm, const char* desc)
{
    LogVariable *ptr = new LogVariable( varMatrix.getElementsPointer() , nm ,desc , varMatrix.getNumRows() , varMatrix.getNumColumns() );

    this->logVariableArray.appendElement(ptr);

}

//==============================================================================
// ControlBase::registerLogVariable
//==============================================================================
void ControlBase::registerLogVariable(MatrixBase<int>& varMatrix, const char* nm, const char* desc)
{
    LogVariable *ptr = new LogVariable( varMatrix.getElementsPointer() , nm ,desc , varMatrix.getNumRows() , varMatrix.getNumColumns() );

    this->logVariableArray.appendElement(ptr);

}


//==============================================================================
// ControlBase::registerControlVariable
//==============================================================================
void ControlBase::registerControlVariable(double *variable, const char* nm, const char* desc,int row,int col)
{
    ControlVariable *ptr = new ControlVariable( variable, nm ,desc , row ,col );

    this->controlVariableArray.appendElement(ptr);

}

//==============================================================================
// ControlBase::registerControlVariable
//==============================================================================
void ControlBase::registerControlVariable(double &variable, const char* nm, const char* desc)
{
    this->registerControlVariable( &variable,nm,desc);
}


//==============================================================================
// ControlBase::registerControlVariable
//==============================================================================
void ControlBase::registerControlVariable(MatrixBase<double>& varMatrix, const char* nm, const char* desc)
{
    ControlVariable *ptr = new ControlVariable( varMatrix.getElementsPointer() , nm ,desc , varMatrix.getNumRows() , varMatrix.getNumColumns() );

    this->controlVariableArray.appendElement(ptr);

}


//==============================================================================
// ControlBase::loadConfigFile
//==============================================================================
bool ControlBase::loadConfigFile()
{
    this->config = new Config(configFileName);
    frequency = config->getFrequency();
    duration = config->getDuration();
    Utils::setControlVariableVec(&controlVariableArray);
    Utils::setLogVariableVec(&logVariableArray);
    config->setValue( controlVariableArray );
    config->setValue( logVariableArray );
    return true;
}

//==============================================================================
// ControlBase::showUsage
//==============================================================================
void ControlBase::showUsage()
{
    cout << "Dostum bu program soyle calistirilir" << endl ;
    cout << applicationName << " " << configFileName << endl;
    cout << "Ya da : " <<applicationName << " " << configFileName << " "
            << GUICOMMAND << endl;

    cout << endl << "Yardim icin " << HELPCOMMAND << " ile calistirin" << endl;
}


//==============================================================================
// ControlBase::showHelp
//==============================================================================
void ControlBase::showHelp()
{
    cout << "Cuneyt bu fonksiyon ellerinden oper" << endl ;
}


//==============================================================================
// ControlBase::copyConfigFileName
//==============================================================================
void ControlBase::copyConfigFileName ( char *nm )
{

    configFileName = new char[NAMELENGTH];
/*
    for(int counter = 0 ; counter < strlen(nm) ; ++counter )
        if( nm[counter] == '.' )
        {
            nm[counter] = '\000';
            break;
        }*/

    strcpy(configFileName , nm );
}

//==============================================================================
// ControlBase::createControlHeap
//==============================================================================
bool ControlBase::createControlHeap()
{
    size_t logSize = 0 ;
    size_t controlSize = 0 ;

    logSize += sizeof(double); // zaman bilgisi icin ayrilan yer
    controlSize += sizeof(double) * 3; // overrun, duration ve frequency icin ayrilan yer

    for (int counter = 0 ; counter < logVariableArray.getNumElements() ; ++counter )
    {
        logSize += logVariableArray.getElement( counter )->getSizeOf();
        logSize += 4 * sizeof(double);
    }

    for (int counter = 0 ; counter < controlVariableArray.getNumElements() ; ++counter )
        controlSize += controlVariableArray.getElement( counter )->getSizeOf();

    controlHeap = new HeapXn();
    
    controlHeapAddress = (double *)controlHeap->create( applicationName , logSize + controlSize);

    if( !controlHeapAddress )
        return false;

    double *tempHeapIndex = controlHeapAddress + 4;

    for (int counter = 0 ; counter < logVariableArray.getNumElements() ; ++counter )
    {
        logVariableArray.getElement(counter)->setTimeAddress(controlHeapAddress);
        logVariableArray.getElement(counter)->setHeapTFSDaddr( tempHeapIndex );
        tempHeapIndex += 4 ;
        logVariableArray.getElement(counter)->setSourceAddress(tempHeapIndex);
        tempHeapIndex += logVariableArray.getElement(counter)->getSize();
    }

    for (int counter = 0 ; counter < controlVariableArray.getNumElements() ; ++counter )
    {
        controlVariableArray.getElement(counter)->setSourceHeapAddress(tempHeapIndex);
        tempHeapIndex += controlVariableArray.getElement(counter)->getSize();
    }

    return true;
}


//==============================================================================
// ControlBase::printControlVariable
//==============================================================================
void ControlBase::printControlVariable()
{
    cout << endl << endl <<"----------------------------ControlVariables "
            << "Degerleri ----------------------------" << endl << endl;

    for (int counter = 0 ; counter < controlVariableArray.getNumElements() ; ++counter)
    {
        cout << "Name : " <<  controlVariableArray.getElement(counter)->getName() << endl;
        cout << "Description : " <<  controlVariableArray.getElement(counter)->getDescription()<< endl;
        cout << "Row : " <<  controlVariableArray.getElement(counter)->getRows() << endl;
        cout << "Col : " <<  controlVariableArray.getElement(counter)->getCols() << endl;
        cout << "Values :";

        for (int counter2 = 0 ; counter2 < controlVariableArray.getElement(counter)->getSize() ; ++counter2 )
            cout << " " << controlVariableArray.getElement(counter)->getElement(counter2);

        cout << endl << endl;
    }

}


//==============================================================================
// ControlBase::printLogVariable
//==============================================================================
void ControlBase::printLogVariable()
{
    cout << endl << endl <<"----------------------------LogVariables "
            << "Degerleri ----------------------------" << endl << endl;

    for (int counter = 0 ; counter < logVariableArray.getNumElements() ; ++counter)
    {
        cout << "Name : " <<  logVariableArray.getElement(counter)->getName() << endl;
        cout << "Description : " <<  logVariableArray.getElement(counter)->getDescription()<< endl;
        cout << "Frequency : " <<  logVariableArray.getElement(counter)->getFrequency() << endl;
        cout << "Duration : " <<  logVariableArray.getElement(counter)->getDuration() << endl;
        cout << "StartTime : " <<  logVariableArray.getElement(counter)->getStartTime() << endl;
        cout << "Row : " <<  logVariableArray.getElement(counter)->getRows() << endl;
        cout << "Col : " <<  logVariableArray.getElement(counter)->getCols() << endl;
        cout << endl << endl;
    }

}

//==============================================================================
// ControlBase::updateVariablesFromHeap
//==============================================================================
void ControlBase::updateVariablesFromHeap(bool isStart)
{
    if( isStart )
    {
        frequency =  controlHeapAddress[1];
        duration =  controlHeapAddress[2];

        for(int counter =  0; counter < logVariableArray.getNumElements() ;++counter)
        {
            double *heapIndex = logVariableArray.getElement(counter)->getHeapTFSDaddr();

            logVariableArray.getElement(counter)->setFrequency( heapIndex[1] );
            logVariableArray.getElement(counter)->setStartTime( heapIndex[2] );
            logVariableArray.getElement(counter)->setDuration( heapIndex[3] );
            logVariableArray.getElement(counter)->setLogPeriod ( frequency / heapIndex[1] );
        }
        
    }

    for(int counter =  0; counter < controlVariableArray.getNumElements() ;++counter)
    {
        double *heapIndex = controlVariableArray.getElement(counter)->getSourceHeapAddress();

        double *elementPtr = controlVariableArray.getElement(counter)->getElementPtr();
        for(int counter2 = 0; counter2 < controlVariableArray.getElement(counter)->getSize() ;++counter2 )
            elementPtr[counter2] = heapIndex[counter2];
    }
     

}

//==============================================================================
// ControlBase::createLoggerHeaps
//==============================================================================
bool ControlBase::createLoggerHeaps()
{
    cout << "creating heaps" << endl;
    for(int counter = 0 ; counter < logVariableArray.getNumElements() ; ++counter )
    {
        LogVariable *varPtr = logVariableArray.getElement( counter );
        int heapSize = varPtr->getSizeOf() + sizeof(double);
        heapSize *= varPtr->getFrequency();
        heapSize *= varPtr->getDuration();

        int error  = varPtr->createHeap(heapSize + sizeof(double) );
        if( error != 0)
        {
              cout << "Heaps cannot be created" << endl;
              cout << "Hata :" << strerror(error) << endl;
              return false;
        }

    }
    cout << "Heaps created" << endl;
    return true;
}


//==============================================================================
// ControlBase::cleanLoggerHeaps
//==============================================================================
void ControlBase::cleanLoggerHeaps()
{
    cout << "deleting heaps" << endl;
    for(int counter = 0 ; counter < logVariableArray.getNumElements() ; ++counter )
    {
        LogVariable *varPtr = logVariableArray.getElement( counter );

        varPtr->deleteHeap();
    }
}

//==============================================================================
// ControlBase::Run
//==============================================================================
void ControlBase::run()
{
    mlockall ( MCL_CURRENT | MCL_FUTURE );
    rt_print_auto_init(1);
    
    initialize();
    loadConfigFile();
    

    if( !createControlHeap() )
    {
        cout << "Creating Control Heap Error ! \nSimulation Terminated''" << endl;
        return;
    }
    

   if( isGUI )
    {
        runWithGUI();
        rtnetListener->stopThread();
        rtnetListener->join();
        delete rtnetListener;
    }
    else
    {
        runWithConsole();
    }

    terminate();
    //cleanUp();    
}

//==============================================================================
// ControlBase::runWithGUI()
//==============================================================================
bool ControlBase::runWithGUI()
{
    char senderQueueName[ NAMELENGTH ];
    char receiverQueueName[ NAMELENGTH ];
    char rtnetComQueueSenderName[ NAMELENGTH ];


    sprintf(senderQueueName,"%s%s",applicationName,"BaseToGUI");
    sprintf(receiverQueueName,"%s%s",applicationName,"GUIToBase");
    snprintf(rtnetComQueueSenderName,NAMELENGTH,"%s%s",applicationName,"RTNETListener");
    

    cout << applicationName << endl;
    guiComQueueReceiver = new guiMessenger(receiverQueueName);
    guiComQueueSender = new guiMessenger(senderQueueName);
    rtnetComQueueSender = new guiMessenger(rtnetComQueueSenderName);


    if( messengerArray.getNumElements() != 0 )
    {
        rtnetUDPXn.bind(3701);
        rtnetUDPXn.setTimeout(1000000000); //timeout 1 second
        rtnetListener = new RTMessageListener(this);
        rtnetListener->create("RTMessangeListener");
        rtnetListener->start();
     }
        
    while(1)
    {
        cout << "Zenom :Waiting For Start Message" << endl ;
        guiComQueueReceiver->receiveStartMessage();
        cout << "Zenom :start message received "<< endl;
        
        char buffer[128];
        strcpy(buffer,"--start");
        for(int i = 0; i < messengerArray.getNumElements(); ++i)
            rtnetUDPXn.send(buffer, sizeof(char)*128,0, messengerArray.getElement(i)->getIp()); 

        start();
        zenomState = START;
        updateVariablesFromHeap(true);

        elapsedTimeSecond = 0;
        elapsedTimeNano = 0;
        elapsedTimeMiliSecond = 0;

        if( !createLoggerHeaps() )
        {
            cout << "Creating Logger Heaps Error ! \nSimulation Terminated''" << endl;
            return false;
        }

        guiComQueueSender->sendBindMessage();
        cout << "Zenom :bind message send"<< endl;
        
        loopTask = new LoopTask(this);
        loopTask->create("LoopTask");

        logTask = new LoggerTask(this);
        logTask->create("LogTask");

        if( messengerArray.getNumElements() != 0 )
        {
            rtMessageTask = new RTMessageTask(this);
            rtMessageTask->create("RTMessangeTask");
        }
        messengerThread = new MessengerThread(this);
        messengerThread->create("MessengerThread");

        //guiComQueueSender->sendStartMessage();
        loopTask->start();
        logTask->start();
        messengerThread->start();
        if( rtMessageTask != NULL )
            rtMessageTask->start();

        cout << "Threads Started ControlBase" << endl;
        loopTask->join();
        
        // RTNET objesi var ve program normal sonlanır ise state STOP edilir.
        if(rtnetListener)
            rtnetListener->setState(STOP);
            
        cout << "looptask joined" << endl;
        cout << "State ControlBase run : " << this->zenomState << endl;
        messengerThread->join();
        cout << "messenger joined" << endl;
        logTask->join();
        cout << "logtask joined" << endl;

        if( rtMessageTask != NULL )
        {
            rtMessageTask->join();
            cout << "rtMessageTask joined" << endl;
        }

        guiComQueueSender->sendStopMessage();
        cout << "Zenom : stop message gonderdi" << endl;

        //guiComQueueReceiver->receiveStopMessage();*/

        cout << "Zenom : unbind message bekliyor" << endl;
        guiComQueueReceiver->receiveUnbindMessage();
        cout << "Zenom : received unbind message" << endl;

        messengerThread->deleteTask();
        loopTask->deleteTask();
        logTask->deleteTask();

        if( rtMessageTask != NULL )
            rtMessageTask->deleteTask();


        delete messengerThread;
        delete loopTask;
        delete logTask;

        if( rtMessageTask != NULL )
        {
            delete rtMessageTask;
            rtMessageTask = NULL;
        }

        cleanLoggerHeaps();
        stop();
    }

    return true;
}
//==============================================================================
// ControlBase::runWithConsole()
//==============================================================================
bool ControlBase::runWithConsole()
{
    elapsedTimeSecond = 0;
    elapsedTimeNano = 0;
    elapsedTimeMiliSecond = 0;

    if( !createLoggerHeaps() )
    {
        cout << "Creating Logger Heaps Error ! \nSimulation Terminated''" << endl;
        return false;
    }

    zenomState = START;
    start();

    loopTask = new LoopTask(this);
    if( messengerArray.getNumElements() != 0 )
    {
        rtMessageTask = new RTMessageTask(this);
        rtMessageTask->create("RTMessangeTask");
    }

    loopTask->create("LoopTask");

    logTask = new LoggerTask(this);
    logTask->create("LogTask");

    loopTask->start();
    logTask->start();
    if( rtMessageTask != NULL )
        rtMessageTask->start();


    loopTask->join();
    logTask->join();
    if( rtMessageTask != NULL )
        rtMessageTask->join();


    stop();
    cleanLoggerHeaps();

    return true;
}



