#ifndef INOGENERATOR_H
#define INOGENERATOR_H

#include "targetprojectbase.h"
#include "cppparser.h"
#include <QString>
#include <QFile>


class InoGenerator : public TargetProjectBase
{
public:
    InoGenerator();

    virtual void printUsage();
    virtual bool checkParameters(int argc, char *argv[]);
    virtual bool processParameters(int argc, char *argv[]);

protected:

    bool generateIno(QString pFileName);
    void fillInoFile(QFile& pInoFile);

    CppParser mCppParser;
};

#endif // INOGENERATOR_H
