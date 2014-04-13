#ifndef CPPPARSER_H
#define CPPPARSER_H

#include <QString>
#include <QVector>

class CppParser
{
public:
    CppParser();
    void parseFile(const QString& pFile);

protected:
    QVector<QString> mLogVariableVec;
    QVector<QString> mControlVariableVec;
};

#endif // CPPPARSER_H
