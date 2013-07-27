#ifndef GAUGEMANAGER_H
#define GAUGEMANAGER_H

#include <QObject>
#include <QSettings>
#include "gaugelistdialog.h"

class GaugeManager : public QObject
{
	Q_OBJECT

public:
	GaugeManager(QWidget *pParent);

	~GaugeManager();
	
	void saveSettings( QSettings& pSettings );

	void loadSettings( QSettings& pSettings );

	void tick();

	void clear();

public slots:
	void showGaugeListDialog();

private slots:
	void gaugeWidgetCreated( GaugeWidget* pGaugeWidget );

	void gaugeWidgetDestroyed( QObject* pGaugeWidget );

private:
	QVector<GaugeWidget*> mGaugeList;	
};

#endif // GAUGEMANAGER_H
