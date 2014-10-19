#ifndef GAUGELISTDIALOG_H
#define GAUGELISTDIALOG_H

#include <QDialog>
#include "ui_gaugelistdialog.h"

#include "gaugewidget.h"

class GaugeListDialog : public QDialog
{
	Q_OBJECT

public:
	GaugeListDialog(QWidget *parent = 0);

	~GaugeListDialog();

signals:
	void gaugeWidgetCreated( GaugeWidget* );

private slots:
	void changePage(QListWidgetItem *current, QListWidgetItem *previous);
	void okClickedSlot();

private:
	Ui::GaugeListDialog ui;
};

#endif // GAUGELISTDIALOG_H
