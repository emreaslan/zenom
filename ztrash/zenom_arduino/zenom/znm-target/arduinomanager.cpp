#include "arduinomanager.h"
#include "targetmanager.h"

ArduinoManager::ArduinoManager()
{
    mManager = new TargetManager;
}

ArduinoManager::~ArduinoManager()
{
   delete mManager;
}

void ArduinoManager::initArduino()
{
    return mManager->initTarget();
}

void ArduinoManager::doLoopPreProcess()
{
    return mManager->doLoopPreProcess();
}

void ArduinoManager::doLoopPostProcess()
{
    return mManager->doLoopPostProcess();
}

bool ArduinoManager::isConnected()
{
    return mManager->isConnected();
}

void ArduinoManager::start()
{
    return mManager->start();
}

void ArduinoManager::stop()
{
    return mManager->stop();
}

void ArduinoManager::registerLogVariable(double *pVariable, const std::string& pName)
{
    return mManager->registerLogVariable(pVariable, pName);
}

void ArduinoManager::registerControlVariable(double *pVariable, const std::string& pName)
{
     return mManager->registerControlVariable(pVariable, pName);
}

