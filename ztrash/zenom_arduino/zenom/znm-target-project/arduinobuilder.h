#ifndef ARDUINOBUILDER_H
#define ARDUINOBUILDER_H

#include "targetprojectbase.h"

class ArduinoBuilder : public TargetProjectBase
{
public:
    ArduinoBuilder();

    bool checkParameters(int argc, char *argv[]);
    bool processParameters(int argc, char *argv[]);
    void printUsage();

protected:
    bool buildArduinoFile();
};

#endif // ARDUINOBUILDER_H
