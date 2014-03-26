#include "arduinomanager.h"
#include "arduinomanagerimp.h"

ArduinoManager::ArduinoManager()
{
    mManager = new ArduinoManagerImp;
}

ArduinoManager::~ArduinoManager()
{
   delete mManager;
}

void ArduinoManager::initArduino(const std::string& pFile)
{
    return mManager->initArduino(pFile);
}

const std::map<std::string, double*>& ArduinoManager::getLogVaribleMap()
{
    return mManager->getLogVaribleMap();
}

const std::map<std::string, double*>& ArduinoManager::getControlVaribleMap()
{
    return mManager->getControlVaribleMap();
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


