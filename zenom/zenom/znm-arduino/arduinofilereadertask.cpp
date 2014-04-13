#include "arduinofilereadertask.h"
#include "arduinomanagerimp.h"

#include <QByteArray>
#include <QVector>
#include <iostream>
#include <unistd.h>

ArduinoFileReaderTask::ArduinoFileReaderTask(ArduinoManagerImp *pManager) : mArduinoManager(pManager)
{
}

void ArduinoFileReaderTask::run()
{
    while (mArduinoManager->mContiuneReading)
    {
        std::cout << "Arduino File Reader loop" << std::endl;
        readSerial();

        writeSerial();
    }
}


void ArduinoFileReaderTask::readSerial()
{
    int n = read(mArduinoManager->mArduinoFileID, mBuffer, 128);
    mByteArray.append(mBuffer, n);

    processBuffer(mByteArray);
    clearBuffer(mBuffer, 256);
}

void ArduinoFileReaderTask::writeSerial()
{
    if (mWriteCounter != 5)
    {
        mWriteCounter++;
        return;
    }
    QMap<char, double>::iterator controlVarIter = mArduinoManager->mControlVaribleFileValueMap.begin();
    for (;controlVarIter != mArduinoManager->mControlVaribleFileValueMap.end(); controlVarIter++)
    {
        sprintf(mBuffer, "< %c : %.2f >\n", controlVarIter.key(), controlVarIter.value());
        std::cout  << "Buf: "<< mBuffer << std::endl;
        write(mArduinoManager->mArduinoFileID, mBuffer, 128);
        clearBuffer(mBuffer, 256);
    }
    mWriteCounter = 0;

}

void ArduinoFileReaderTask::clearBuffer(char* pBuffer, unsigned int pSize)
{
    // clears buffer
    for (int i = 0; i < pSize; ++i)
    {
        pBuffer[i] = '\0';
    }
}


void ArduinoFileReaderTask::processBuffer(QByteArray& pBuffer)
{

     QVector<QByteArray>  messageVec;

     while (true)
     {
         int beginPos = pBuffer.indexOf('<');
         if (beginPos == -1)
         {
             break;
         }

         int endPos = pBuffer.indexOf('>', beginPos);
         if (endPos == -1)
         {
             break;
         }

         QByteArray tempArray;
         for (int i = beginPos + 1; i < endPos -1 ; ++i )
         {
             tempArray.push_back(pBuffer[i]);
         }
         messageVec.push_back(tempArray);
         pBuffer = pBuffer.right( pBuffer.size() - endPos -1);
     }

     //QString str(pBuffer);

//     std::cout << "Buffer : " << str.toStdString() << std::endl;

     for (int i = 0; i < messageVec.size(); ++i)
     {
         QString message(messageVec[i]);
         mArduinoManager->updateValue(message);
         //std::cout << "Message : " << message.toStdString() << std::endl;
     }
}
