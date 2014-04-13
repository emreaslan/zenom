#ifndef ARDUINOMANAGER_H
#define ARDUINOMANAGER_H

#include "znm-arduino_global.h"
#include <string>
#include <map>

class ArduinoManagerImp;
class ZNMARDUINOSHARED_EXPORT ArduinoManager
{
public:
    ArduinoManager();
    ~ArduinoManager();

    void initArduino();
    void doLoopPreProcess();
    void doLoopPostProcess();
    bool isConnected();
    void start();
    void stop();

    void registerLogVariable(double *, const std::string&);
    void registerControlVariable(double *, const std::string&);
private:
    ArduinoManagerImp* mManager;
};
#endif // ARDUINOMANAGER_H
