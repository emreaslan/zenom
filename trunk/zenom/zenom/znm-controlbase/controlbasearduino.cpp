#include "controlbasearduino.h"
#include "arduinomanager.h"


ControlBaseArduino::ControlBaseArduino() : mArduinoManager(new ArduinoManager)
{
}

ControlBaseArduino::~ControlBaseArduino()
{
    delete mArduinoManager;
}


void ControlBaseArduino::registerArduinoLogVariable(double *pVariable, const std::string& pName, unsigned int pRow, unsigned int pCol, const std::string& pDesc)
{
    mArduinoManager->registerLogVariable(pVariable, pName);
    registerLogVariable(pVariable, pName, pRow, pCol, pDesc);
}

void ControlBaseArduino::registerArduinoControlVariable(double *pVariable, const std::string& pName, VariableType pVariableType, unsigned int pRow, unsigned int pCol, const std::string& pDesc)
{
    mArduinoManager->registerControlVariable(pVariable, pName);
    if (pVariableType == CONTROL_VARIABLE)
    {
        registerControlVariable(pVariable, pName, pRow, pCol, pDesc);
    }
    else if (pVariableType == LOG_VARIABLE)
    {
        registerLogVariable(pVariable, pName, pRow, pCol, pDesc);
    }
}


void ControlBaseArduino::startArduino()
{
    return mArduinoManager->start();
}

void ControlBaseArduino::stopArduino()
{
    return mArduinoManager->stop();
}

void ControlBaseArduino::doLoopPreProcess()
{
    return mArduinoManager->doLoopPreProcess();
}

void ControlBaseArduino::doLoopPostProcess()
{
    return mArduinoManager->doLoopPostProcess();
}



//============================================================================//
//		ARDUINO OPERATIONS												  //
//============================================================================//
void ControlBaseArduino::initArduino()
{
    mArduinoManager->initArduino();
    if (!mArduinoManager->isConnected())
    {
        std::cout << "ControlBase init arduino cannot connect" << std::endl;
        return;
    }

    std::cout << "ControlBase init arduino connected" << std::endl;
    return;
}

int ControlBaseArduino::initializeWrapper()
{
    initArduino();
    int result = initialize();
    startArduino();
    return result;
}

int ControlBaseArduino::startWrapper()
{
    return start();
}

int ControlBaseArduino::doloopWrapper()
{
    doLoopPreProcess();
    int result = doloop();
    doLoopPostProcess();
    return result;
}

int ControlBaseArduino::stopWrapper()
{
    return stop();
}

int ControlBaseArduino::terminateWrapper()
{
    int result = terminate();
    stopArduino();
    return result;
}
