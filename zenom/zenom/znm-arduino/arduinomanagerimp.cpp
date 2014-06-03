#include "arduinomanagerimp.h"
#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <termios.h>
#include <QDir>
#include <QVector>

ArduinoManagerImp::ArduinoManagerImp() : mIsArduinoConnected(false), mContiuneReading(false)
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

ArduinoManagerImp::~ArduinoManagerImp()
{
    if (mIsArduinoConnected)
    {
        close(mArduinoFileID);
    }
}

void ArduinoManagerImp::reset()
{
    mLogVariableCurrentName = 'A';
    mControlVariableCurrentName = 'a';
}


void ArduinoManagerImp::initArduino()
{
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
}


int ArduinoManagerImp::initArduinoConnection()
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
        isOpened = openArduinoFile(fileList.at(i));
        if (isOpened)
        {
            break;
        }
    }

    if (!isOpened)
    {
        std::cout << "Arduino Communication File cannot be opened" << std::endl;
        return -2;
    }
    return 0;
}

bool ArduinoManagerImp::openArduinoFile(const QString &pFileName)
{
    std::cout << "Opening : " << pFileName.toStdString() << std::endl;

    QString filePath = QString("/dev/") + pFileName;
   /* Open the file descriptor in non-blocking mode */
    mArduinoFileID = open(filePath.toStdString().c_str(), O_RDWR | O_NOCTTY ); // | O_NONBLOCK );

    if (mArduinoFileID == -1)
    {
        return false;
    }

   // Set up the control structure
    struct termios toptions;

    /* Get currently set options for the tty */
    tcgetattr(mArduinoFileID, &toptions);

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
    tcsetattr(mArduinoFileID, TCSANOW, &toptions);

   /* Wait for the Arduino to reset */
    usleep(1000*1000);
    /* Flush anything already in the serial buffer */
    tcflush(mArduinoFileID, TCIFLUSH);
    /* read up to 128 bytes from the fd */

    std::cout << "Opened : " << pFileName.toStdString() << std::endl;
    return true;
}

bool ArduinoManagerImp::isConnected()
{
    return mIsArduinoConnected;
}

void ArduinoManagerImp::terminate()
{
    mContiuneReading = false;
}


void ArduinoManagerImp::registerLogVariable(double *pVariable, const std::string& pName)
{
    mLogVaribleVec.push_back( ZenomVariableData(mLogVariableCurrentName, pVariable) );
    mLogVariableCurrentName++;

}

void ArduinoManagerImp::registerControlVariable(double *pVariable, const std::string& pName)
{
    mControlvariableVec.push_back( ZenomVariableData(mControlVariableCurrentName, pVariable) );
    mControlVariableCurrentName++;
}


void ArduinoManagerImp::updateValue(QString &pMes)
{
    QStringList list = pMes.split(" : ");
    QString variable = list.at(0);
    QString value = list.at(1);
    variable.remove(' ');

    mLogVaribleFileValueMap[variable.at(0).toAscii()] = value.toDouble();
}

void ArduinoManagerImp::doLoopPreProcess()
{
    std::cout << "Do loop pre process" << std::endl;
    if(!mIsArduinoConnected)
    {
        std::cout << "do loop pre process not connected" << std::endl;
        return;
    }

    std::map<char, double>::iterator valueIter = mLogVaribleFileValueMap.begin();
    for(; valueIter != mLogVaribleFileValueMap.end(); valueIter++)
    {
        for (int i = 0; i < mLogVaribleVec.size(); ++i)
        {
            if (mLogVaribleVec[i].mName == valueIter->first )
            {
                *(mLogVaribleVec[i].mValue) =  valueIter->second;
                std::cout << "Key : " << valueIter->first << " : Value : " << valueIter->second << std::endl;
                break;
            }
        }
    }
}

void ArduinoManagerImp::doLoopPostProcess()
{
    for (int i = 0; i < mControlvariableVec.size(); ++i)
    {
        mControlVaribleFileValueMap[mControlvariableVec[i].mName] = *(mControlvariableVec[i].mValue);
    }
}

void ArduinoManagerImp::start()
{
    if (!mIsArduinoConnected)
    {
        return;
    }

    std::cout << "Arduino start" << std::endl;
    mFileReaderTask = new ArduinoFileReaderTask(this);
    mFileReaderTask->create( "Arduino File Reader Task" );
    mFileReaderTask->start();
}


void ArduinoManagerImp::stop()
{
    if (!mIsArduinoConnected)
    {
        return;
    }

    std::cout << "Arduino stop" << std::endl;
    mContiuneReading = false;
    mFileReaderTask->join();
    delete mFileReaderTask;
}

