#ifndef CONTROLVARIABLESWIDGET_H
#define CONTROLVARIABLESWIDGET_H

#include <QDockWidget>
#include "ui_controlvariableswidget.h"

#include "datarepository.h"

class ControlVariablesWidget : public QDockWidget
{
	Q_OBJECT

public:
	ControlVariablesWidget(QWidget *parent = 0);

	~ControlVariablesWidget();

	void setControlVariableList( const ControlVariableList& pControlVariableList );

	void clear();

private slots:
	void applyPressedSlot();
	void cancelPressedSlot();
	void itemChangedSlot(QTableWidgetItem* pItem);

private:
	void enableButtons(bool pEnable);

	Ui::ControlVariablesWidget ui;
};

#endif // CONTROLVARIABLESWIDGET_H
