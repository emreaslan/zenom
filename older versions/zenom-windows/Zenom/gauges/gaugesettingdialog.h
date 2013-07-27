#ifndef GAUGESETTINGDIALOG_H
#define GAUGESETTINGDIALOG_H

#include <QDialog>
#include "ui_gaugesettingdialog.h"

#include "gaugewidget.h"
#include "abstractgaugesetting.h"

class GaugeWidget;

class GaugeSettingDialog : public QDialog
{
	Q_OBJECT

public:
	GaugeSettingDialog(QWidget *parent = 0);

	~GaugeSettingDialog();

	void setGaugeWidget( GaugeWidget* pGauge );

	void setGaugeSetting( AbstractGaugeSetting* pSetting );
	
protected:
	void showEvent(QShowEvent *pEvent);

private slots:
	void okClickedSlot();

private:
	Ui::GaugeSettingDialog ui;

	GaugeWidget* mGaugeWidget;
	AbstractGaugeSetting* mGaugeSetting;
};

#endif // GAUGESETTINGDIALOG_H
