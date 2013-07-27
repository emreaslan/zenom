#include "projectfileinfo.h"

ProjectFileInfo::ProjectFileInfo( const QString & pProjectConfigFile )
	: QFileInfo(pProjectConfigFile)
{

}

ProjectFileInfo::~ProjectFileInfo()
{

}

QString ProjectFileInfo::configFile()
{
	return absoluteFilePath();
}

QString ProjectFileInfo::projectName()
{
	return baseName();
}

QString ProjectFileInfo::cppFile()
{
	return absoluteDir().filePath( projectName() + ".cpp" );
}

QString ProjectFileInfo::makefile()
{
	return absoluteDir().filePath( "Makefile" );
}