#ifndef INOFILEREADER_H
#define INOFILEREADER_H

#include <string>
#include <vector>

class InoFileReader
{
public:
    InoFileReader(const std::string& pFile);
    const std::vector<std::string>& getLogVariables() const;
    const std::vector<std::string>& getControlVariables() const;

protected:
    void readFile(const std::string &pFile);
    std::vector<std::string> mLogVariables;
    std::vector<std::string> mControlVariables;
};

#endif // INOFILEREADER_H
