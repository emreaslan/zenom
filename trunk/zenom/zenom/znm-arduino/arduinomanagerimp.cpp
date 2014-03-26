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

    std::map<std::string, double*>::iterator iterLog = mLogVaribleMap.begin();
    for (; iterLog != mLogVaribleMap.end(); iterLog++)
    {
        delete iterLog->second;
    }

    std::map<std::string, double*>::iterator iterControl = mControlvariableMap.begin();
    for (; iterControl != mLogVaribleMap.end(); iterControl++)
    {
        delete iterControl->second;
    }

}

void ArduinoManagerImp::initArduino(const std::string &pFile)
{
    mArduinoFilePath = pFile.c_str();
    parseArduinoFile();

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

int ArduinoManagerImp::parseArduinoFile()
{
    mLogVaribleMap["Distance"] = new double;

    mLogVaribleMap["test"] = new double;
    *(mLogVaribleMap["test"]) = 123;
    return 0;
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
    QString filePath = QString("/dev/") + pFileName;
   /* Open the file descriptor in non-blocking mode */
    mArduinoFileID = open(filePath.toStdString().c_str(), O_RDWR | O_NOCTTY);

    if (mArduinoFileID == -1)
    {
        return false;
    }

   /* Set up the control structure */
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

const std::map<std::string, double*>& ArduinoManagerImp::getLogVaribleMap()
{
    return mLogVaribleMap;
}

const std::map<std::string, double*>& ArduinoManagerImp::getControlVaribleMap()
{
    return mControlvariableMap;
}

void ArduinoManagerImp::updateValue(QString &pMes)
{
    QStringList list = pMes.split(" : ");
    QString variable = list.at(0);
    QString value = list.at(1);

    mLogVaribleFileValueMap[variable.toStdString()] = value.toDouble();
}

void ArduinoManagerImp::doLoopPreProcess()
{
    std::cout << "Do loop pre process" << std::endl;
    if(!mIsArduinoConnected)
    {
        std::cout << "do loop pre process not connected" << std::endl;
        return;
    }

    QMap<std::string, double>::iterator valueIter = mLogVaribleFileValueMap.begin();
    for(; valueIter != mLogVaribleFileValueMap.end(); valueIter++)
    {
        std::cout << "Key : " << valueIter.key() << " : Value : " << valueIter.value() << std::endl;
        *(mLogVaribleMap[valueIter.key()]) = valueIter.value();
    }
}

void ArduinoManagerImp::doLoopPostProcess()
{

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

