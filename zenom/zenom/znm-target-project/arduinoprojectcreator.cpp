#include "arduinoprojectcreator.h"

#include <QDir>

#define CREATE_ARDUINO_PROJECT_PARAMETER (std::string("--createarduinoproject"))

ArduinoProjectCreator::ArduinoProjectCreator()
{
}

bool ArduinoProjectCreator::checkParameters(int argc, char *argv[])
{
    if ( argc != 3 || (std::string(argv[1]) != CREATE_ARDUINO_PROJECT_PARAMETER && std::string(argv[2]) != CREATE_ARDUINO_PROJECT_PARAMETER) )
    {
        return false;
    }
    return true;
}

bool ArduinoProjectCreator::processParameters(int argc, char *argv[])
{
    if (std::string(argv[1]) == CREATE_ARDUINO_PROJECT_PARAMETER )
    {
        return createProject(QString(argv[2]) );
    }
    else
    {
        return createProject(QString(argv[1]) );
    }
}

bool ArduinoProjectCreator::createProject(QString pProjectName)
{
    QDir projectDir;
    if ( projectDir.exists( pProjectName) )
    {
        fprintf(stderr, "The project cannot be created because '%s' folder already exists.\n", pProjectName.toStdString().c_str() );
        exit(1);  /* exit status of the program : non-zero for errors */
    }

    projectDir.mkpath( pProjectName );
    projectDir.cd( pProjectName );
    projectDir.mkdir("libs");
    projectDir.mkdir("src");

    QFileInfo programFileInfo( getexepath() );
    QString projectName( QFileInfo(pProjectName).fileName() );

    createFile( programFileInfo.dir().filePath("znm-project-main.template"), projectDir.filePath("main.cpp"), projectName, "ControlBaseArduino", "controlbasearduino.h" );
    createFile( programFileInfo.dir().filePath("znm-project-makefile.template"), projectDir.filePath("Makefile"), projectName, "ControlBaseArduino" );

    // Open project file to write
    QFile configFile( projectDir.filePath(QString("%1.znm").arg(projectName)) );
    if ( !configFile.open(QFile::WriteOnly | QFile::Text) )
    {
        fprintf(stderr, "The project cannot be created because the file '%s' could not be opened.\n", configFile.fileName().toAscii().data());
        exit(1);  /* exit status of the program : non-zero for errors */
    }
    configFile.close();

    return true;
}


void ArduinoProjectCreator::printUsage()
{
    printf ("usage: znm-target-project project_name --arduinoproject \nCreates a zenom project.\n\n");
}
