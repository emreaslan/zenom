#include "projectcreator.h"

ProjectCreator* ProjectCreator::mInstance = NULL;


ProjectCreator* ProjectCreator::instance()
{
	if ( !ProjectCreator::mInstance )
	{
		ProjectCreator::mInstance = new ProjectCreator();
	}

	return ProjectCreator::mInstance;
}


bool ProjectCreator::create( QWidget *parent, const QString pName, const QString pLocation)
{
	ProjectCreator::instance()->checkTemplateFiles();
	
	// Create project folder
	QDir locationDir( pLocation );
	locationDir.mkdir( pName );
	locationDir.setPath(  locationDir.filePath( pName ) );

	const QString className = pName.simplified().replace( " ", "" );

	bool ret;
	// Create cpp file
	ret = ProjectCreator::instance()->createFile( parent, QString("template") + QDir::separator() + "source.template", 
		locationDir.filePath( className + ".cpp"), className );		

	// Create Makefile
	ret = ret && ProjectCreator::instance()->createFile( parent, QString("template") + QDir::separator() + "makefile.template", 
		locationDir.filePath( "Makefile"), className );

	return ret;
}

void ProjectCreator::checkTemplateFiles()
{
	QDir dir;
	if ( !dir.exists( "template" ) )
	{
		dir.mkdir( "template" );
	}

	// QFile will not overwrite it.
	QFile::copy(":/Zenom/Resources/source.template", QString("template") + QDir::separator() + "source.template" );
	QFile::copy(":/Zenom/Resources/makefile.template", QString("template") + QDir::separator() + "makefile.template" );
}

bool ProjectCreator::createFile( QWidget *parent, const QString pTemplate, const QString pDestination, const QString pClassName )
{
	// Open template file to read.
	QFile templateFile( pTemplate );
	if ( !templateFile.open(QFile::ReadOnly | QFile::Text) ) 
	{
		// template file was not found.
		QMessageBox::warning(parent, tr("Zenom"),
			tr("Cannot open template file %1:\n%2")
			.arg( templateFile.fileName() )
			.arg( templateFile.errorString() ));
		return false;
	}

	// Open project file to write
	QFile destinationFile( pDestination );
	if ( !destinationFile.open(QFile::WriteOnly | QFile::Text) ) 
	{
		// destination file was not found.
		QMessageBox::warning(parent, tr("Zenom"),
			tr("Cannot open project file %1:\n%2")
			.arg( destinationFile.fileName() )
			.arg( destinationFile.errorString() ));
		return false;
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
		line.replace( "<%=class_name_upcase%>", pClassName.toUpper() );

		out << line << "\n";;
	} while (!line.isNull());

	destinationFile.close();
	templateFile.close();

	return true;
}
