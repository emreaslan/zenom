#ifndef ARDUINOPROJECTTOOL_H
#define ARDUINOPROJECTTOOL_H

#include <vector>
#include "targetprojectbase.h"


class TargetProjectManager
{
public:
    TargetProjectManager();
    ~TargetProjectManager();
    void printUsage();
    bool checkParameters(int argc, char *argv[]);

protected:
    std::vector<TargetProjectBase*> mProjectOperatorVec;
};

#endif // ARDUINOPROJECTTOOL_H
