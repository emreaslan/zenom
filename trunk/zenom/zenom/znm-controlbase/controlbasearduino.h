#ifndef ZENOMARDUINOMANAGER_H
#define ZENOMARDUINOMANAGER_H

#include <string>
#include "controlbase.h"
#include "znm-controlbase_global.h"


class ArduinoManager;

class ZNMCONTROLBASESHARED_EXPORT ControlBaseArduino : public ControlBase
{
public:
    enum VariableType
    {
        NONE = 0,
        LOG_VARIABLE = 1,
        CONTROL_VARIABLE = 2
    };

    ControlBaseArduino();
    ~ControlBaseArduino();

    void registerArduinoLogVariable(double *pVariable, const std::string& pName, unsigned int pRow = 1, unsigned int pCol = 1, const std::string& pDesc= "");
    void registerArduinoControlVariable(double *pVariable, const std::string& pName, VariableType = CONTROL_VARIABLE, unsigned int pRow = 1, unsigned int pCol = 1, const std::string& pDesc= "");

    virtual int initialize(){return 0;}

    virtual int start(){return 0;}

    virtual int doloop(){return 0;}

    virtual int stop(){return 0;}

    virtual int terminate(){return 0;}


protected:
    void initArduino();

    void startArduino();
    void stopArduino();
    void doLoopPreProcess();
    void doLoopPostProcess();

    //============================================================================//
    //		WRAPPER OPERATIONS												  //
    //============================================================================//
    virtual int initializeWrapper();
    virtual int startWrapper();
    virtual int doloopWrapper();
    virtual int stopWrapper();
    virtual int terminateWrapper();

    ArduinoManager* mArduinoManager;
};

#endif // ZENOMARDUINOMANAGER_H
