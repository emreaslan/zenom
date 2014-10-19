#ifndef LOGVARIABLETREEWIDGET_H
#define LOGVARIABLETREEWIDGET_H

#include <QTreeWidget>
#include "datarepository.h"
#include "logvariableitem.h"

class LogVariableTreeWidget : public QTreeWidget
{
	Q_OBJECT

public:
	LogVariableTreeWidget(QWidget *pParent);

	~LogVariableTreeWidget();

	/*
	Returns the current log variable item in the tree widget.
	*/
	LogVariableItem currentLogVariableItem() const;

	/*
	Returns a list of all selected non-hidden log variable items.
	*/
	QList<LogVariableItem> selectedLogVariableItems() const;

	/*
	Sets the current log variable item in the tree widget.
	*/
	void setCurrentItem( LogVariableItem pLogVariableItem );

protected:
	void showEvent(QShowEvent * pEvent);

private:
	
};

#endif // LOGVARIABLETREEWIDGET_H
