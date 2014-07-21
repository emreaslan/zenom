#include "targetmanager.h"
#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <termios.h>
#include <QDir>
#include <QVector>
#include "targetreaderwritertask.h"


TargetManager::TargetManager() : mIsTargetConnected(false), mContiuneReading(false), mFileReaderTask(NULL), mTargetFileID(-1)
{
    reset();
    /*
    int connectionResult = initArduinoConnection();
    switch ( connectionResult)
    {
    case 0:
        mIsArduinoConnected = true;
        mContiuneReading = true;
        mLastErrorString = QString("No error");
        break;
    case -1:
        mIsArduinoConnected = false;
        mLastErrorString = QString("No Arduino Device Detected");
        break;
    case -2:
        mIsArduinoConnected = false;
        mLastErrorString = QString("Can not connect to Ardunio");
        break;
    default:
        mIsArduinoConnected = false;
        mLastErrorString = QString("Unknown Error");
        break;
    }
    */
}

TargetManager::~TargetManager()
{
    if (mTargetFileID != -1)
    {
        close(mTargetFileID);
    }
}

void TargetManager::reset()
{
    mLogVariableCurrentName = 'A';
    mControlVariableCurrentName = 'a';
}


void TargetManager::initTarget()
{
    int connectionResult = initTargetConnection();
    switch ( connectionResult)
    {
    case 0:
        mIsTargetConnected = true;
        mContiuneReading = true;
        mLastErrorString = QString("No error");
        break;
    case -1:
        mIsTargetConnected = false;
        mLastErrorString = QString("No Arduino Device Detected");
        break;
    case -2:
        mIsTargetConnected = false;
        mLastErrorString = QString("Can not connect to Ardunio");
        break;
    default:
        mIsTargetConnected = false;
        mLastErrorString = QString("Unknown Error");
        break;
    }
}


int TargetManager::initTargetConnection()
{
    QDir dir("/dev/");
    QStringList nameFilters;
    nameFilters.append(QString("ttyACM*"));

    QStringList fileList = dir.entryList(nameFilters, QDir::AllEntries | QDir::System, QDir::Name | QDir::Reversed);

    if ( fileList.size() == 0)
    {
        std::cout  << "No Arduino device" << std::endl;
        return -1;
    }


    bool isOpened = false;
    for (int i = 0 ; i < fileList.size(); ++i )
    {
        isOpened = openTargetFile(fileList.at(i));
        if (isOpened)
        {
            break;
        }
    }

    if (!isOpened)
    {
        std::cout << "Target Communication File cannot be opened" << std::endl;
        return -2;
    }

    return 0;
}

bool TargetManager::openTargetFile(const QString &pFileName)
{
    std::cout << "Opening : " << pFileName.toStdString() << std::endl;

    QString filePath = QString("/dev/") + pFileName;
   /* Open the file descriptor in non-blocking mode */
    mTargetFileID = open(filePath.toStdString().c_str(), O_RDWR | O_NOCTTY ); // | O_NONBLOCK );

    if (mTargetFileID == -1)
    {
        return false;
    }

   // Set up the control structure
    struct termios toptions;

    /* Get currently set options for the tty */
    tcgetattr(mTargetFileID, &toptions);

   /* Set custom options */

   /* 9600 baud */
    cfsetispeed(&toptions, B9600);
    cfsetospeed(&toptions, B9600);
    /* 8 bits, no parity, no stop bits */
    toptions.c_cflag &= ~PARENB;
    toptions.c_cflag &= ~CSTOPB;
    toptions.c_cflag &= ~CSIZE;
    toptions.c_cflag |= CS8;
    /* no hardware flow control */
    toptions.c_cflag &= ~CRTSCTS;
    /* enable receiver, ignore status lines */
    toptions.c_cflag |= CREAD | CLOCAL;
    /* disable input/output flow control, disable restart chars */
    toptions.c_iflag &= ~(IXON | IXOFF | IXANY);
    /* disable canonical input, disable echo,
    disable visually erase chars,
    disable terminal-generated signals */
    toptions.c_iflag &= ~(ICANON | ECHO | ECHOE | ISIG);
    /* disable output processing */
    toptions.c_oflag &= ~OPOST;

   /* wait for 24 characters to come in before read returns */
    toptions.c_cc[VMIN] = 20;
    /* no minimum time to wait before read returns */
    toptions.c_cc[VTIME] = 0;

   /* commit the options */
    tcsetattr(mTargetFileID, TCSANOW, &toptions);

   /* Wait for the Arduino to reset */
    usleep(1000*1000);
    /* Flush anything already in the serial buffer */
    tcflush(mTargetFileID, TCIFLUSH);
    /* read up to 128 bytes from the fd */

    char buffer[128];
    int n = read(mTargetFileID, buffer, 128);
    std::cout << "Opened : " << pFileName.toStdString() << std::endl;
    return true;
}

bool TargetManager::isConnected()
{
    return mIsTargetConnected;
}

void TargetManager::terminate()
{
    mContiuneReading = false;
}


void TargetManager::registerLogVariable(double *pVariable, const std::string& pName)
{
    mLogVaribleVec.push_back( ZenomVariableData(mLogVariableCurrentName, pVariable) );
    mLogVariableCurrentName++;

}

void TargetManager::registerControlVariable(double *pVariable, const std::string& pName)
{
    mControlvariableVec.push_back( ZenomVariableData(mControlVariableCurrentName, pVariable) );
    mControlVaribleFileValueVec.push_back( std::pair<char, double>(mControlVariableCurrentName, *pVariable) );
    mControlVarDiffVec.push_back( *pVariable );
    mControlVariableCurrentName++;
}


void TargetManager::updateValue(QString &pMes)
{
    QStringList list = pMes.split(" : ");
    QString variable = list.at(0);
    QString value = list.at(1);
    variable.remove(' ');

    // --------------- Lock Begin ---------------------
    mLogVarMutex.lock();
    mLogVaribleFileValueMap[variable.at(0).toLatin1()] = value.toDouble();
    mLogVarMutex.unlock();
     // --------------- Lock End ---------------------
}

void TargetManager::doLoopPreProcess()
{
    //std::cout << "Do loop pre process" << std::endl;
    if(!mIsTargetConnected)
    {
        std::cout << "do loop pre process not connected" << std::endl;
        return;
    }

    // --------------- Lock Begin ---------------------
    mLogVarMutex.lock();
    std::map<char, double>::iterator valueIter = mLogVaribleFileValueMap.begin();
    for(; valueIter != mLogVaribleFileValueMap.end(); valueIter++)
    {
        for (int i = 0; i < mLogVaribleVec.size(); ++i)
        {
            if (mLogVaribleVec[i].mName == valueIter->first )
            {
                *(mLogVaribleVec[i].mValue) =  valueIter->second;
                //std::cout << "Key : " << valueIter->first << " : Value : " << valueIter->second << std::endl;
                break;
            }
        }
    }
    mLogVarMutex.unlock();
    // --------------- Lock End ---------------------
}

void TargetManager::doLoopPostProcess()
{
    // --------------- Lock Begin ---------------------
    mControlVarMutex.lock();
    for (int i = 0; i < mControlvariableVec.size(); ++i)
    {
        //std::cout << "doLoopPostProcess - ControlVar Name : " << mControlvariableVec[i].mName << " - mValue : " <<  *(mControlvariableVec[i].mValue) << std::endl;
        mControlVaribleFileValueVec[i].second = *(mControlvariableVec[i].mValue);
    }
    mControlVarMutex.unlock();
    // --------------- Lock End ---------------------
}

void TargetManager::start()
{
    if (!mIsTargetConnected)
    {
        return;
    }

    std::cout << "Target start" << std::endl;
    mFileReaderTask = new TargetReaderWriterTask(this);
    //mFileReaderTask->( "Target Reader Task" );

    mFileReaderTask->start();
}


void TargetManager::stop()
{
    if (!mIsTargetConnected)
    {
        mContiuneReading = false;
        return;
    }

    std::cout << "Target stop" << std::endl;
    mContiuneReading = false;

    mFileReaderTask->wait();
    delete mFileReaderTask;

    mFileReaderTask = NULL;
}

