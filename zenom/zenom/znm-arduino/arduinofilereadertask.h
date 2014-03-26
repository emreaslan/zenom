#ifndef ARDUINOFILEREADERTASK_H
#define ARDUINOFILEREADERTASK_H


#include <TaskXn.h>
#include <native/timer.h>

class ArduinoManagerImp;
class QByteArray;

class ArduinoFileReaderTask : public TaskXn
{
public:
    ArduinoFileReaderTask(ArduinoManagerImp* pManager);

    virtual void run();

private:
    void processBuffer(QByteArray&);
    ArduinoManagerImp* mArduinoManager;

};

#endif // ARDUINOFILEREADERTASK_H
