#include <QtCore/QCoreApplication>







#include <iostream>
#include <unistd.h>

QString getexepath();
void createFile(const QString pTemplate, const QString pDestination, const QString pClassName, const QString pParentName = QString("ControlBase"), const QString pHeaderName = QString("controlbase.h"));


int main(int argc, char *argv[])
{
    if ( argc < 2 || argc > 3)
    {
        /* display usage on error stream */
        fprintf(stderr, "usage: znm-project project_name\n\n");
        exit(1);  /* exit status of the program : non-zero for errors */
    }

    if ( QString("--help") == argv[1] )
    {
        printf ("usage: znm-project project_name --arduino (optional, creates arduino project)\nCreates a zenom project.\n\n");
        exit(0);  /* exit status of the program : non-zero for errors */
    }

    QDir projectDir;
    if ( projectDir.exists( argv[1] ) )
    {
        fprintf(stderr, "The project cannot be created because '%s' folder already exists.\n", argv[1]);
        exit(1);  /* exit status of the program : non-zero for errors */
    }

    projectDir.mkpath( argv[1] );
    projectDir.cd( argv[1] );

    QFileInfo programFileInfo( getexepath() );
    QString projectName( QFileInfo(argv[1]).fileName() );

    if (argc == 3 && argv[2] == QString("--arduino"))
    {
        createFile( programFileInfo.dir().filePath("znm-project-main.template"), projectDir.filePath("main.cpp"), projectName, "ControlBaseArduino", "controlbasearduino.h" );
    }
    else
    {
        createFile( programFileInfo.dir().filePath("znm-project-main.template"), projectDir.filePath("main.cpp"), projectName);
    }
    createFile( programFileInfo.dir().filePath("znm-project-makefile.template"), projectDir.filePath("Makefile"), projectName );

    // Open project file to write
    QFile configFile( projectDir.filePath(QString("%1.znm").arg(projectName)) );
    if ( !configFile.open(QFile::WriteOnly | QFile::Text) )
    {
        fprintf(stderr, "The project cannot be created because the file '%s' could not be opened.\n", configFile.fileName().toAscii().data());
        exit(1);  /* exit status of the program : non-zero for errors */
    }
    configFile.close();

    return 0;
}

QString getexepath()
{
    char result[ PATH_MAX ];
    ssize_t count = readlink( "/proc/self/exe", result, PATH_MAX );
    return QString::fromStdString( std::string( result, (count > 0) ? count : 0 ) );
}

void createFile(const QString pTemplate, const QString pDestination, const QString pClassName, const QString pParentName, const QString pHeaderName)
{
    // Open template file to read.
    QFile templateFile( pTemplate );
    if ( !templateFile.open(QFile::ReadOnly | QFile::Text) )
    {
        fprintf(stderr, "The project cannot be created because the template file '%s' could not be found.\n", pTemplate.toAscii().data());
        exit(1);  /* exit status of the program : non-zero for errors */
    }

    // Open project file to write
    QFile destinationFile( pDestination );
    if ( !destinationFile.open(QFile::WriteOnly | QFile::Text) )
    {
        fprintf(stderr, "The project cannot be created because the file '%s' could not be opened.\n", pDestination.toAscii().data());
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
