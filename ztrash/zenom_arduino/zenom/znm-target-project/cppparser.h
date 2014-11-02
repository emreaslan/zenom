#ifndef CPPPARSER_H
#define CPPPARSER_H

#include <QString>
#include <QVector>

class CppParser
{
public:
    CppParser();
    bool parseFile(const QString& pFile);

    QString projectName();
    QVector<QString>& logVariables();
    QVector<QString>& controlVariables();

protected:
    void processClassName(const QString& pLine);
    void processLogVariableLine(const QString& pLine);
    void processControlVariableLine(const QString& pLine);
    void processVariableLine(const QString& pLine, const QString& pProc, QVector<QString>& pVec );

    QString readBetweenParenthesis(const QString& pLine, int pBeginIndex);
    QString extractVariableName(const QString& pParameters);

    QVector<QString> mLogVariableVec;
    QVector<QString> mControlVariableVec;
    QString mProjectName;
};

#endif // CPPPARSER_H
