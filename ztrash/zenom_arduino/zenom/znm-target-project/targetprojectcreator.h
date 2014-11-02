#ifndef PROJECTCREATOR_H
#define PROJECTCREATOR_H

#include "targetprojectbase.h"
#include <QString>

class TargetProjectCreator : public TargetProjectBase
{
public:
    TargetProjectCreator();
    virtual bool checkParameters(int argc, char *argv[]);
    virtual bool processParameters(int argc, char *argv[]);
    virtual void printUsage();

protected:

    virtual bool createProject(QString pProjectName);
    QString getexepath();
    void createFile(const QString pTemplate, const QString pDestination, const QString pClassName, const QString pParentName = QString("ControlBase"), const QString pHeaderName = QString("controlbase.h"));
};

#endif // PROJECTCREATOR_H
