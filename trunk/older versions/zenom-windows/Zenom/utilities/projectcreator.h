#ifndef PROJECTCREATOR_H
#define PROJECTCREATOR_H

#include <QObject>
#include <QString>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include "projectfileinfo.h"

class ProjectCreator : public QObject
{
	Q_OBJECT
public:
	
	static bool create( QWidget *parent, const QString pName, const QString pLocation);

private:
	static ProjectCreator* instance();

	static ProjectCreator* mInstance;

	void checkTemplateFiles();

	bool createFile(QWidget *parent, const QString pTemplate, const QString pDestination, const QString pClassName);	
};

#endif // PROJECTCREATOR_H
