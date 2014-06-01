#ifndef ARDUINOPROJECTCREATOR_H
#define ARDUINOPROJECTCREATOR_H

#include "targetprojectcreator.h"

class ArduinoProjectCreator : public TargetProjectCreator
{
public:
    ArduinoProjectCreator();

    bool checkParameters(int argc, char *argv[]);
    bool processParameters(int argc, char *argv[]);
    void printUsage();

protected:
   virtual bool createProject(QString pProjectName);
};

#endif // ARDUINOPROJECTCREATOR_H
