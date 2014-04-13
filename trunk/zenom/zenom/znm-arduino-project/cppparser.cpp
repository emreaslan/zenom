#include "cppparser.h"

#include <QFile>

CppParser::CppParser()
{
}


void CppParser::parseFile(const QString &pFile)
{
    mLogVariableVec.clear();
    mControlVariableVec.clear();

    QFile zenomFile(pFile);
    if ( !zenomFile.open(QFile::ReadOnly))
    {
        return;
    }

    while (!zenomFile.atEnd())
    {
        QString text(zenomFile.readLine() );
    }



}
