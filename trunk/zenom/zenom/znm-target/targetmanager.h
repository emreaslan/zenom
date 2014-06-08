#ifndef ZNMTARGETMANAGER_H
#define ZNMTARGETMANAGER_H

#include "znm-target_global.h"
#include <vector>
#include <map>
#include <QString>

class TargetReaderWriterTask;

struct ZenomVariableData
{
  ZenomVariableData(char pName, double* pValue) : mName(pName), mValue(pValue) {}
  ZenomVariableData() : mName(0), mValue(NULL) {}

  char mName;
  double* mValue;
};

class TargetManager
{
    friend class TargetReaderWriterTask;

public:
    TargetManager();
    ~TargetManager();

    void initTarget();

    void registerLogVariable(double *, const std::string&);
    void registerControlVariable(double *, const std::string&);

    void doLoopPreProcess();
    void doLoopPostProcess();
    bool isConnected();
    void start();
    void stop();

protected:

    int initTargetConnection(); // 0 - connection successed, -1 - No Device, -2 - File error
    void terminate();
    void reset();



    bool openTargetFile(const QString &pFileName);
    void updateValue(QString& pMes);

    std::vector<ZenomVariableData> mLogVaribleVec;
    std::vector<ZenomVariableData> mControlvariableVec;

    std::map<char, double> mLogVaribleFileValueMap;
    std::vector< std::pair<char, double > > mControlVaribleFileValueVec;
    std::vector<double> mControlVarDiffVec;

    TargetReaderWriterTask* mFileReaderTask;
    int mTargetFileID;
    QString mLastErrorString;
    bool mIsTargetConnected;
    bool mContiuneReading;
    char mLogVariableCurrentName;
    char mControlVariableCurrentName;
};

#endif // ZNMTARGETMANAGER_H
