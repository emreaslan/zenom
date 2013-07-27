#include "gaugemanager.h"

GaugeManager::GaugeManager(QWidget *pParent)
	: QObject(pParent)
{

}

GaugeManager::~GaugeManager()
{

}

void GaugeManager::saveSettings( QSettings& pSettings )
{
	pSettings.beginGroup("Gauges");
	pSettings.setValue("size", mGaugeList.size());
	for ( int i = 0; i < mGaugeList.size(); ++i )
	{
		pSettings.beginGroup( QString("Gauge") + QString::number(i) );
		mGaugeList[i]->setObjectName( QString("Gauge") + QString::number(i) );
		mGaugeList[i]->saveSettings(pSettings);
		pSettings.endGroup();
	}
	pSettings.endGroup();
}

void GaugeManager::loadSettings( QSettings& pSettings )
{
	pSettings.beginGroup("Gauges");
	int size = pSettings.value("size", 0).toInt();
	for ( int i = 0; i < size; ++i )
	{
		pSettings.beginGroup( QString("Gauge") + QString::number(i) );
		GaugeWidget* gaugeWidget = new GaugeWidget( static_cast<QWidget*>(parent()) );
		gaugeWidget->setObjectName( QString("Gauge") + QString::number(i) );
		gaugeWidget->loadSettings(pSettings);
		gaugeWidgetCreated(gaugeWidget);
		pSettings.endGroup();
	}
	pSettings.endGroup();
}

void GaugeManager::tick()
{
	for ( int i = 0; i < mGaugeList.size(); ++i )
	{
		mGaugeList[i]->tick();
	}
}

void GaugeManager::clear()
{
	for ( int i = 0; i < mGaugeList.size(); ++i )
	{
		mGaugeList[i]->disconnect();	// do not call gaugeWidgetDestroyed
		delete mGaugeList[i];
	}
	mGaugeList.clear();
}

void GaugeManager::showGaugeListDialog()
{
	GaugeListDialog gaugeListDialog( static_cast<QWidget*>(parent()) );
	connect( &gaugeListDialog, SIGNAL(gaugeWidgetCreated(GaugeWidget*)), SLOT(gaugeWidgetCreated(GaugeWidget*)) );
	gaugeListDialog.exec();
}

void GaugeManager::gaugeWidgetCreated( GaugeWidget* pGaugeWidget )
{
	connect( pGaugeWidget, SIGNAL(destroyed(QObject*)), SLOT(gaugeWidgetDestroyed(QObject*)) );
	mGaugeList.push_back( pGaugeWidget );
}

void GaugeManager::gaugeWidgetDestroyed( QObject* pGaugeWidget )
{
	GaugeWidget* gaugeWidget = static_cast<GaugeWidget*>(pGaugeWidget);
	mGaugeList.remove( mGaugeList.indexOf(gaugeWidget) );
}
