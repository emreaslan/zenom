#include "ControlBase.h"


//==============================================================================
// ControlBase::ControlBase
//==============================================================================
ControlBase::ControlBase(int argc, char* argv[])
{
    config = new Config(argv[0], true);      
}

//==============================================================================
// ControlBase::~ControlBase
//==============================================================================
ControlBase::~ControlBase()
{
 
    delete config;

    for (int counter = 0 ; counter < controlVariableArray.getNumElements() ; ++counter )
        delete controlVariableArray.getElement(counter);

    for (int counter = 0 ; counter < logVariableArray.getNumElements() ; ++counter )
        delete logVariableArray.getElement(counter);

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

void ControlBase::fillControlVarsWithZero()
{
    for (int i = 0; i < controlVariableArray.size() ; ++i)
    {
        for (int j = 0; j < controlVariableArray[i]->getSize(); ++j )
        {
            controlVariableArray[i]->setElement(j, 0);
        }
    }
}

//==============================================================================
// ControlBase::Run
//==============================================================================
void ControlBase::run()
{
    initialize();
    int frequency = config->getFrequency();
    int duration = config->getDuration();
    if ( (frequency == 0) && (duration == 0) )
    {
        frequency = 1000;
        duration = 100;
    }
    Utils::setControlVariableVec(&controlVariableArray);
    Utils::setLogVariableVec(&logVariableArray);
    
    if ( config->isConfigFileFound())
    {
        config->setValue(logVariableArray);
        config->setValue(controlVariableArray);
    }
    else
    {
        fillControlVarsWithZero();
    }
    config->resetXMLFile(true);
    config->updateVariable(frequency, duration);
    config->updateVariable(logVariableArray);
    config->updateVariable(controlVariableArray);
    config->saveToFile();
}

