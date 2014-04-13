#include "zenomarduinomanager.h"
#include "controlbase.h"
#include "arduinomanager.h"


ZenomArduinoManager::ZenomArduinoManager() : mControlBase(NULL), mArduinoManager(new ArduinoManager)
{
}

ZenomArduinoManager::~ZenomArduinoManager()
{
    delete mArduinoManager;
}


void ZenomArduinoManager::registerArduinoLogVariable(double *pVariable, const std::string& pName, unsigned int pRow, unsigned int pCol, const std::string& pDesc)
{
    if (!mControlBase)
    {
        return;
    }

    mArduinoManager->registerLogVariable(pVariable, pName);
    mControlBase->registerLogVariable(pVariable, pName, pRow, pCol, pDesc);
}

void ZenomArduinoManager::registerArduinoControlVariable(double *pVariable, const std::string& pName, unsigned int pRow, unsigned int pCol, const std::string& pDesc)
{
    if (!mControlBase)
    {
        return;
    }

    mArduinoManager->registerControlVariable(pVariable, pName);
    mControlBase->registerControlVariable(pVariable, pName, pRow, pCol, pDesc);
}


void ZenomArduinoManager::start()
{
    return mArduinoManager->start();
}

void ZenomArduinoManager::stop()
{
    return mArduinoManager->stop();
}

void ZenomArduinoManager::doLoopPreProcess()
{
    return mArduinoManager->doLoopPreProcess();
}

void ZenomArduinoManager::doLoopPostProcess()
{
    return mArduinoManager->doLoopPostProcess();
}



//============================================================================//
//		ARDUINO OPERATIONS												  //
//============================================================================//
void ZenomArduinoManager::initArduino(ControlBase* pControlBase)
{
    mControlBase = pControlBase;

    if (!mControlBase)
    {
        return;
    }

    std::cout << "ControlBase init arduino" << std::endl;
    mArduinoManager->initArduino();
    if (!mArduinoManager->isConnected())
    {
        std::cout << "ControlBase init arduino cannot connect" << std::endl;
        return;
    }

    std::cout << "ControlBase init arduino connected" << std::endl;
    return;
}
