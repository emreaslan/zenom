#ifndef ARDUINOUPLOADER_H
#define ARDUINOUPLOADER_H

#include "targetprojectbase.h"

class ArduinoUploader : public TargetProjectBase
{
public:
    ArduinoUploader();

    bool checkParameters(int argc, char *argv[]);
    bool processParameters(int argc, char *argv[]);
    void printUsage();

protected:
    bool uploadToArduino();
};

#endif // ARDUINOUPLOADER_H
