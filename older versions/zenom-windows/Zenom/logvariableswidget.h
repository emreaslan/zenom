#ifndef LOGVARIABLESWIDGET_H
#define LOGVARIABLESWIDGET_H

#include <QDockWidget>
#include "ui_logvariableswidget.h"

#include "datarepository.h"

class LogVariablesWidget : public QDockWidget
{
	Q_OBJECT

public:
	LogVariablesWidget(QWidget *parent = 0);

	~LogVariablesWidget();

	void setLogVariableList( const LogVariableList& pLogVariableList );

	void clear();

private:
	Ui::LogVariablesWidget ui;
};

#endif // LOGVARIABLESWIDGET_H
