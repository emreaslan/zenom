#include "targetprojectmanager.h"

#include "arduinoprojectcreator.h"
#include "inogenerator.h"
#include "arduinobuilder.h"
#include "arduinouploader.h"

TargetProjectManager::TargetProjectManager()
{
    mProjectOperatorVec.push_back(new ArduinoProjectCreator);
    mProjectOperatorVec.push_back(new InoGenerator);
    mProjectOperatorVec.push_back(new ArduinoBuilder);
    mProjectOperatorVec.push_back(new ArduinoUploader);
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

bool TargetProjectManager::processParameters(int argc, char *argv[])
{
    int i = 0;
    for (; i < mProjectOperatorVec.size(); ++i)
    {
        if (mProjectOperatorVec[i]->checkParameters(argc, argv))
        {
            break;
        }
    }
    if ( i != mProjectOperatorVec.size())
    {
        return mProjectOperatorVec[i]->processParameters(argc, argv);
    }
    else
    {
        printUsage();
    }
    return false;
}
