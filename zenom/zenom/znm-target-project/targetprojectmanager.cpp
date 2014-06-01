#include "targetprojectmanager.h"

#include "arduinoprojectcreator.h"
#include "inogenerator.h"

TargetProjectManager::TargetProjectManager()
{
    mProjectOperatorVec.push_back(new ArduinoProjectCreator);
    mProjectOperatorVec.push_back(new InoGenerator);
}

TargetProjectManager::~TargetProjectManager()
{
    for (int i = 0; i < mProjectOperatorVec.size(); ++i)
    {
        delete mProjectOperatorVec[i];
    }
}

void TargetProjectManager::printUsage()
{
    for (int i = 0; i < mProjectOperatorVec.size(); ++i)
    {
        mProjectOperatorVec[i]->printUsage();
    }

}

bool TargetProjectManager::checkParameters(int argc, char *argv[])
{
    for (int i = 0; i < mProjectOperatorVec.size(); ++i)
    {
        if (mProjectOperatorVec[i]->checkParameters(argc, argv))
        {
            return mProjectOperatorVec[i]->processParameters(argc, argv);
        }
    }
    return false;
}
