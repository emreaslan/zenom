#ifndef TARGETREADERTASK_H
#define TARGETREADERTASK_H

#include <QFile>
#include <QThread>
#include <native/timer.h>

class TargetManager;
class QByteArray;

class TargetReaderWriterTask : public QThread
{
public:
    TargetReaderWriterTask(TargetManager* pManager);

    virtual void run();

private:
    void readSerial();
    void writeSerial();
    void clearBuffer(char* pBuffer, unsigned int pSize);
    void processBuffer(QByteArray&);
    bool isDoublesEqual(double pRight, double pLeft);

    TargetManager* mTargetManager;
    char mBuffer[256];
    char mSendBuffer[256];
    QByteArray mByteArray;
    //QFile mOutputFile;
};

#endif // TARGETREADERTASK_H
