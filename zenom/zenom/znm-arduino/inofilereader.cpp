#include "inofilereader.h"

InoFileReader::InoFileReader(const std::string &pFile)
{
    readFile(pFile);
}


const std::vector<std::string>& InoFileReader::getLogVariables() const
{
    return mLogVariables;
}

const std::vector<std::string>& InoFileReader::getControlVariables() const
{
    return mControlVariables;
}

void InoFileReader::readFile(const std::string &pFile)
{
}


