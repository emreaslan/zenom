#ifndef ARDUINOMANAGERIMP_H
#define ARDUINOMANAGERIMP_H

#include "znm-arduino_global.h"
#include <vector>
#include <map>
#include <QString>
#include "arduinofilereadertask.h"

struct ZenomVariableData
{
  ZenomVariableData(char pName, double* pValue) : mName(pName), mValue(pValue) {}
  ZenomVariableData() : mName(0), mValue(NULL) {}

  char mName;
  double* mValue;
};

class ArduinoManagerImp
{
    friend class ArduinoFileReaderTask;

public:
    ArduinoManagerImp();
    ~ArduinoManagerImp();

    void initArduino();

    void registerLogVariable(double *, const std::string&);
    void registerControlVariable(double *, const std::string&);

    void doLoopPreProcess();
    void doLoopPostProcess();
    bool isConnected();
    void start();
    void stop();

protected:

    int initArduinoConnection(); // 0 - connection successed, -1 - No Device, -2 - File error
    void terminate();
    void reset();



    bool openArduinoFile(const QString &pFileName);
    void updateValue(QString& pMes);

    std::vector<ZenomVariableData> mLogVaribleVec;
    std::vector<ZenomVariableData> mControlvariableVec;

    std::map<char, double> mLogVaribleFileValueMap;
    std::map<char, double> mControlVaribleFileValueMap;

    ArduinoFileReaderTask* mFileReaderTask;
    int mArduinoFileID;
    QString mLastErrorString;
    bool mIsArduinoConnected;
    bool mContiuneReading;
    char mLogVariableCurrentName;
    char mControlVariableCurrentName;
};

#endif // ARDUINOMANAGERIMP_H
