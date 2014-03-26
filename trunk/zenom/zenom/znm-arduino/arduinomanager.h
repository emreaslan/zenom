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

    void initArduino(const std::string&);
    void doLoopPreProcess();
    void doLoopPostProcess();
    bool isConnected();
    void start();
    void stop();

    const std::map<std::string, double*>& getLogVaribleMap();
    const std::map<std::string, double*>& getControlVaribleMap();
private:
    ArduinoManagerImp* mManager;
};
#endif // ARDUINOMANAGER_H
