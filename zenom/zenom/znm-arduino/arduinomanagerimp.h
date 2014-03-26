#ifndef ARDUINOMANAGERIMP_H
#define ARDUINOMANAGERIMP_H

#include "znm-arduino_global.h"
#include <map>
#include <QMap>
#include <QString>
#include "arduinofilereadertask.h"

class ArduinoManagerImp
{
    friend class ArduinoFileReaderTask;

public:
    ArduinoManagerImp();
    ~ArduinoManagerImp();

    void initArduino(const std::string&);

    const std::map<std::string, double*>& getLogVaribleMap();
    const std::map<std::string, double*>& getControlVaribleMap();

    void doLoopPreProcess();
    void doLoopPostProcess();
    bool isConnected();
    void start();
    void stop();

protected:

    int parseArduinoFile();
    int initArduinoConnection(); // 0 - connection successed, -1 - No Device, -2 - File error
    void terminate();

    bool openArduinoFile(const QString&);
    void updateValue(QString& pMes);

    std::map<std::string, double*> mLogVaribleMap;
    std::map<std::string, double*> mControlvariableMap;

    QMap<std::string, double> mLogVaribleFileValueMap;
    QMap<std::string, double> mControlvariableFileValueMap;


    ArduinoFileReaderTask* mFileReaderTask;
    int mArduinoFileID;
    QString mArduinoFilePath;
    QString mLastErrorString;
    bool mIsArduinoConnected;
    QString mInoFile;
    bool mContiuneReading;
};

#endif // ARDUINOMANAGERIMP_H
