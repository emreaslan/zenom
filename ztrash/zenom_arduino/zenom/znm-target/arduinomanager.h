#ifndef TARGETMANAGER_H
#define ARDUINOMANAGER_H

#include "znm-target_global.h"
#include <string>
#include <map>

class TargetManager;
class ZNM_TARGET_SHARED_EXPORT ArduinoManager
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
    TargetManager* mManager;
};
#endif // ARDUINOMANAGER_H
