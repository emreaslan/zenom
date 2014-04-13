#ifndef ARDUINOFILEREADERTASK_H
#define ARDUINOFILEREADERTASK_H


#include <TaskXn.h>
#include <native/timer.h>
#include <QByteArray>

class ArduinoManagerImp;
class QByteArray;

class ArduinoFileReaderTask : public TaskXn
{
public:
    ArduinoFileReaderTask(ArduinoManagerImp* pManager);

    virtual void run();

private:
    void readSerial();
    void writeSerial();
    void clearBuffer(char* pBuffer, unsigned int pSize);
    void processBuffer(QByteArray&);
    ArduinoManagerImp* mArduinoManager;

    char mBuffer[256];
    int mWriteCounter;
    QByteArray mByteArray;

};

#endif // ARDUINOFILEREADERTASK_H
