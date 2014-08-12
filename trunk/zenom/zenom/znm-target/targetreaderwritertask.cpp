#include "targetreaderwritertask.h"
#include "targetmanager.h"

#include <QByteArray>
#include <QVector>
#include <iostream>
#include <unistd.h>
#include <math.h>

TargetReaderWriterTask::TargetReaderWriterTask(TargetManager *pManager) : mTargetManager(pManager)
{

}

void TargetReaderWriterTask::run()
{
    int counter = 0;
    while (mTargetManager->mContiuneReading)
    {
        //std::cout << "Arduino File Reader loop" << std::endl;
        if (mTargetManager->mLogVaribleVec.size() > 0)
        {
            ++counter;
            readSerial();
        }

        if (mTargetManager->mControlvariableVec.size() > 0)
        {
            writeSerial();
        }

        if (counter == 10 )
        {
            /* Flush anything already in the serial buffer */
            mTargetManager->flushSerialFile();
            counter = 0;
            mByteArray.clear();
        }
    }
}


void TargetReaderWriterTask::readSerial()
{
    int n = read(mTargetManager->mTargetFileID, mBuffer, 128);

    if (n <= 0)
    {
        std::cout << "read returned : " << n << std::endl;
        return;
    }

    mByteArray.append(mBuffer, n);
    processBuffer(mByteArray);
    clearBuffer(mBuffer, 256);
}


void TargetReaderWriterTask::clearBuffer(char* pBuffer, unsigned int pSize)
{
    // clears buffer
    for (unsigned int i = 0; i < pSize; ++i)
    {
        pBuffer[i] = '\0';
    }
}


void TargetReaderWriterTask::processBuffer(QByteArray& pBuffer)
{
    QVector<QByteArray>  messageVec;

    if (pBuffer.size() == 0)
    {
        return;
    }

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

     for (int i = 0; i < messageVec.size(); ++i)
     {
         QString message(messageVec[i]);
         mTargetManager->updateValue(message);
     }
}

void TargetReaderWriterTask::writeSerial()
{
    clearBuffer(mSendBuffer, 256);
    std::string message;

    // --------------- Lock Begin ---------------------
    mTargetManager->mControlVarMutex.lock();
    for (int i = 0; i < mTargetManager->mControlVaribleFileValueVec.size(); ++i)
    {
        if ( isDoublesEqual(mTargetManager->mControlVaribleFileValueVec[i].second, mTargetManager->mControlVarDiffVec[i]) )
        {
            continue;
        }

        sprintf(mSendBuffer, "< %c : %.2f >", mTargetManager->mControlVaribleFileValueVec[i].first, mTargetManager->mControlVaribleFileValueVec[i].second);
        message.append(mSendBuffer);

        mTargetManager->mControlVarDiffVec[i] = mTargetManager->mControlVaribleFileValueVec[i].second;

        clearBuffer(mSendBuffer, 256);
    }
    mTargetManager->mControlVarMutex.unlock();
    // --------------- Lock End ---------------------

    if (message.size() != 0 )
    {
        message.push_back('\n');
        write(mTargetManager->mTargetFileID, message.c_str(), 128);
    }

    return;
}

bool TargetReaderWriterTask::isDoublesEqual(double pRight, double pLeft)
{
    if ( fabs( pRight - pLeft ) < 0.01 )
    {
        return true;
    }
    return false;
}
