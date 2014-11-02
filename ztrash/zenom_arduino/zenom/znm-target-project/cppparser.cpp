#include "cppparser.h"
#include <QFile>
#include <QStringList>
#include <iostream>

#define ARDUINO_CONTROL_BASE_CLASS_NAME (QString("ControlBaseArduino"))
#define REGISTER_LOG_PROC (QString("registerArduinoLogVariable"))
#define REGISTER_CONTROL_PROC (QString("registerArduinoControlVariable"))

CppParser::CppParser()
{
}


bool CppParser::parseFile(const QString &pFile)
{
    mLogVariableVec.clear();
    mControlVariableVec.clear();

    QFile zenomFile(pFile);
    if ( !zenomFile.open(QFile::ReadOnly))
    {
        return false;
    }

    while (!zenomFile.atEnd())
    {
        QString text(zenomFile.readLine() );
        if (text.contains(QString("class")) && text.contains(ARDUINO_CONTROL_BASE_CLASS_NAME) )
        {
            processClassName(text);
        }
        if( text.contains(REGISTER_LOG_PROC))
        {
            processLogVariableLine(text);
        }
        if ( text.contains(REGISTER_CONTROL_PROC) );
        {
            processControlVariableLine(text);
        }
    }
    return true;
}

QString CppParser::projectName()
{
    return mProjectName;
}

QVector<QString>& CppParser::logVariables()
{
    return mLogVariableVec;
}

QVector<QString>& CppParser::controlVariables()
{
    return mControlVariableVec;
}

void CppParser::processLogVariableLine(const QString &pLine)
{
    processVariableLine(pLine, REGISTER_LOG_PROC, mLogVariableVec);
}

void CppParser::processControlVariableLine(const QString &pLine)
{
   processVariableLine(pLine, REGISTER_CONTROL_PROC, mControlVariableVec);
}

void CppParser::processVariableLine(const QString &pLine, const QString &pProc, QVector<QString> &pVec)
{
    int count = pLine.count(pProc);
    int index = 0;
    for (int i = 0 ; i < count ; ++i)
    {
        index = pLine.indexOf(pProc, index);
        QString parameters = readBetweenParenthesis(pLine, index + pProc.size());
        QString variable = extractVariableName(parameters);
        if (variable != "")
        {
            pVec.push_back(variable);
        }
    }
}

QString CppParser::readBetweenParenthesis(const QString &pLine, int pBeginIndex)
{
    int openCount = 0;
    int closeIndex = 0;
    for ( int i = pBeginIndex; i < pLine.size(); ++i )
    {
        if ( pLine[i] == '(' )
        {
            openCount++;
        }
        else if (pLine[i] == ')')
        {
            openCount--;
            if ( openCount == 0)
            {
                closeIndex = i;
                break;
            }
        }
    }
    return pLine.mid(pBeginIndex, closeIndex - pBeginIndex + 1);
}

QString CppParser::extractVariableName(const QString &pParameters)
{
    QStringList list = pParameters.split("\"");
    if (list.size() == 3)
    {
        return list[1];
    }
    return QString("");
}

void CppParser::processClassName(const QString &pLine)
{
    QString line = pLine;
    line.remove(' '); line.remove('\t');
    line.chop( line.size() - line.indexOf(':') );
    line.remove("class");
    mProjectName = line;
}
