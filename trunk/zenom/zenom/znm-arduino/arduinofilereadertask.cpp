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
    QByteArray buffer;
    char buf[256];
    while (mArduinoManager->mContiuneReading)
    {
        std::cout << "Arduino File Reader loop" << std::endl;
        int n = read(mArduinoManager->mArduinoFileID, buf, 128);
        buffer.append(buf, n);

       processBuffer(buffer);

        // clears buffer
        for (int i = 0; i < 256; ++i)
        {
            buf[i] = '\0';
        }

   //     char* testStr = "test";
   //     write(fd, testStr, 4);
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
