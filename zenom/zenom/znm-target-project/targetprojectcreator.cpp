#include "targetprojectcreator.h"

#include <QFile>
#include <QDir>
#include <QTextStream>
#include <iostream>
#include <unistd.h>

#define CREATE_PROJECT_PARAMETER (std::string("--createProject"))


TargetProjectCreator::TargetProjectCreator()
{
}


bool TargetProjectCreator::checkParameters(int argc, char *argv[])
{
    if ( argc != 3 || (std::string(argv[1]) != CREATE_PROJECT_PARAMETER && std::string(argv[2]) != CREATE_PROJECT_PARAMETER) )
    {
        return false;
    }
    return true;
}

bool TargetProjectCreator::processParameters(int argc, char *argv[])
{
    if (std::string(argv[1]) == CREATE_PROJECT_PARAMETER )
    {
        return createProject(QString(argv[2]) );
    }
    else
    {
        return createProject(QString(argv[1]) );
    }
}

bool TargetProjectCreator::createProject(QString pProjectName)
{
    QDir projectDir;
    if ( projectDir.exists( pProjectName) )
    {
        fprintf(stderr, "The project cannot be created because '%s' folder already exists.\n", pProjectName.toStdString().c_str() );
        exit(1);  /* exit status of the program : non-zero for errors */
    }

    projectDir.mkpath( pProjectName );
    projectDir.cd( pProjectName );

    QFileInfo programFileInfo( getexepath() );
    QString projectName( QFileInfo(pProjectName).fileName() );

    createFile( programFileInfo.dir().filePath("znm-project-main.template"), projectDir.filePath("main.cpp"), projectName, "ControlBaseArduino", "controlbasearduino.h" );
    createFile( programFileInfo.dir().filePath("znm-project-makefile.template"), projectDir.filePath("Makefile"), projectName, "ControlBaseArduino" );

    // Open project file to write
    QFile configFile( projectDir.filePath(QString("%1.znm").arg(projectName)) );
    if ( !configFile.open(QFile::WriteOnly | QFile::Text) )
    {
        fprintf(stderr, "The project cannot be created because the file '%s' could not be opened.\n", configFile.fileName().toLatin1().data());
        exit(1);  /* exit status of the program : non-zero for errors */
    }
    configFile.close();

    return true;
}


void TargetProjectCreator::printUsage()
{
    printf ("usage: znm-target-project project_name (Target Type)\nCreates a zenom project.\n\n");
}

QString TargetProjectCreator::getexepath()
{
    char result[ PATH_MAX ];
    ssize_t count = readlink( "/proc/self/exe", result, PATH_MAX );
    return QString::fromStdString( std::string( result, (count > 0) ? count : 0 ) );
}

void TargetProjectCreator::createFile(const QString pTemplate, const QString pDestination, const QString pClassName, const QString pParentName, const QString pHeaderName)
{
    // Open template file to read.
    QFile templateFile( pTemplate );
    if ( !templateFile.open(QFile::ReadOnly | QFile::Text) )
    {
        fprintf(stderr, "The project cannot be created because the template file '%s' could not be found.\n", pTemplate.toLatin1().data());
        exit(1);  /* exit status of the program : non-zero for errors */
    }

    // Open project file to write
    QFile destinationFile( pDestination );
    if ( !destinationFile.open(QFile::WriteOnly | QFile::Text) )
    {
        fprintf(stderr, "The project cannot be created because the file '%s' could not be opened.\n", pDestination.toLatin1().data());
        exit(1);  /* exit status of the program : non-zero for errors */
    }

    // Copy from template file to project file
    // Replace magic words
    QTextStream out( &destinationFile );
    QTextStream in( &templateFile );
    QString line;
    do
    {
        line = in.readLine();

        line.replace( "<%=class_name%>", pClassName );

        line.replace( "<%=parent_name%>", pParentName );

        line.replace( "<%=header_name%>", pHeaderName );

        out << line << "\n";;
    } while (!line.isNull());

    destinationFile.close();
    templateFile.close();
}
