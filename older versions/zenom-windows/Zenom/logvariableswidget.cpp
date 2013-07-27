#include "logvariableswidget.h"

LogVariablesWidget::LogVariablesWidget(QWidget *parent)
	: QDockWidget(parent)
{
	ui.setupUi(this);
}

LogVariablesWidget::~LogVariablesWidget()
{

}

void LogVariablesWidget::setLogVariableList( const LogVariableList& pLogVariableList )
{
	ui.logVariableTable->setRowCount( pLogVariableList.size() );

	LogVariable* logVariable;

	for ( size_t i = 0; i < pLogVariableList.size(); ++i )
	{
		logVariable = pLogVariableList[i];

		QTableWidgetItem* name = new QTableWidgetItem( QString::fromStdString(logVariable->name()) );
		name->setFlags( Qt::ItemIsEnabled );
		//name->setTextAlignment( Qt::AlignHCenter | Qt::AlignVCenter );
		ui.logVariableTable->setItem(i, 0, name);

		QTableWidgetItem* frequency = new QTableWidgetItem( QString::number(logVariable->frequency()) );
		ui.logVariableTable->setItem(i, 1, frequency);

		QTableWidgetItem* startTime = new QTableWidgetItem( QString::number(logVariable->startTime()) );
		ui.logVariableTable->setItem(i, 2, startTime);

		QTableWidgetItem* duration = new QTableWidgetItem( QString::number(logVariable->duration()) );
		ui.logVariableTable->setItem(i, 3, duration);
	}
}

void LogVariablesWidget::clear()
{
	ui.logVariableTable->clearContents();
	ui.logVariableTable->setRowCount(0);
}
