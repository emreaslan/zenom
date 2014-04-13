#ifndef ZENOMARDUINOMANAGER_H
#define ZENOMARDUINOMANAGER_H

#include <string>
#include "znm-controlbase_global.h"

class ControlBase;
class ArduinoManager;

class ZNMCONTROLBASESHARED_EXPORT ZenomArduinoManager
{
public:
    ZenomArduinoManager();
    ~ZenomArduinoManager();

    void registerArduinoLogVariable(double *pVariable, const std::string& pName, unsigned int pRow = 1, unsigned int pCol = 1, const std::string& pDesc= "");
    void registerArduinoControlVariable(double *pVariable, const std::string& pName, unsigned int pRow = 1, unsigned int pCol = 1, const std::string& pDesc= "");
    void initArduino(ControlBase*);

    void start();
    void stop();
    void doLoopPreProcess();
    void doLoopPostProcess();

protected:
    ControlBase* mControlBase;
    ArduinoManager* mArduinoManager;

};

#endif // ZENOMARDUINOMANAGER_H
