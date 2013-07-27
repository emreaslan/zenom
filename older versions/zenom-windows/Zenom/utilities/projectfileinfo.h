#ifndef PROJECTFILEINFO_H
#define PROJECTFILEINFO_H

#include <QFileInfo>
#include <QDir>

class ProjectFileInfo : public QFileInfo
{	
public:
	ProjectFileInfo( const QString & pProjectConfigFile = "" );

	~ProjectFileInfo();

	QString configFile();

	QString projectName();

	QString cppFile();

	QString makefile();

private:
	
};

#endif // PROJECTFILEINFO_H
