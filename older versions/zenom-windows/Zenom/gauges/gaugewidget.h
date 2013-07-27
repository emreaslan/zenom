#ifndef GAUGEWIDGET_H
#define GAUGEWIDGET_H

#include <QDockWidget>
#include <QSettings>
#include <QMenu>
#include "ui_gaugewidget.h"

#include "gaugesettingdialog.h"
#include "radialgaugesetting.h"
#include "numericgaugesetting.h"
#include "lineargaugesetting.h"

#include "datarepository.h"

#include "logvariableitem.h"

class GaugeSettingDialog;

class GaugeWidget : public QDockWidget
{
	Q_OBJECT

public:
	GaugeWidget(QWidget *parent = 0);

	~GaugeWidget();

	void setGauge( AbstractGauge* pGauge );

	AbstractGauge* gauge() { return mGauge; }

	LogVariableItem logVariableItem() const;

	void setLogVariableItem(LogVariableItem pLogVariableItem);

	void saveSettings( QSettings& pSettings );

	void loadSettings( QSettings& pSettings );



	GaugeSettingDialog* mGaugeSettingDialog;

public slots:
	void tick();

protected:
	virtual void contextMenuEvent(QContextMenuEvent *pEvent);

private:
	Ui::GaugeWidget ui;

	AbstractGauge* mGauge;

	LogVariable* mLogVariable;	
	int mRow;
	int mCol;
	
	QMenu* mMenu;
};

#endif // GAUGEWIDGET_H
