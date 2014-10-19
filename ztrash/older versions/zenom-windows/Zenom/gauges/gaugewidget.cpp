#include "gaugewidget.h"

GaugeWidget::GaugeWidget(QWidget *parent)
	: QDockWidget(parent), mLogVariable(NULL), mRow(-1), mCol(-1)
{
	ui.setupUi(this);
	setAttribute( Qt::WA_DeleteOnClose );
	setFloating(true);
	setWindowTitle( "Gauge" );
	show();

	mGaugeSettingDialog = new GaugeSettingDialog(this);
	mGaugeSettingDialog->setGaugeWidget( this );

	mMenu = new QMenu(this);
	QAction *action = mMenu->addAction(tr("Settings"));
	connect(action, SIGNAL(triggered()), mGaugeSettingDialog, SLOT(show()));
}

GaugeWidget::~GaugeWidget()
{

}

void GaugeWidget::setGauge( AbstractGauge* pGauge )
{
	setWidget( pGauge );
	//resize( pGauge->sizeHint() );
	mGauge = pGauge;
}

LogVariableItem GaugeWidget::logVariableItem() const
{
	LogVariableItem logVariableItem;
	logVariableItem.mLogVariable = mLogVariable;
	logVariableItem.mRow = mRow;
	logVariableItem.mCol = mCol;

	return logVariableItem;
}

void GaugeWidget::setLogVariableItem( LogVariableItem pLogVariableItem )
{
	mLogVariable = pLogVariableItem.mLogVariable;
	mRow = pLogVariableItem.mRow;
	mCol = pLogVariableItem.mCol;

	if ( mLogVariable )
	{
		if ( mLogVariable->size() > 1 )
		{
			setWindowTitle(  QString("%1[%2][%3]").arg(mLogVariable->name().c_str()).arg(mRow).arg(mCol) );
		} 
		else
		{
			setWindowTitle( mLogVariable->name().c_str() );
		}
	}
}

void GaugeWidget::tick()
{
	if ( mLogVariable && mLogVariable->heapSize() )
	{
		// TODO Heap isbinded || iscreated		
		mGauge->setValue( mLogVariable->lastHeapElement(mRow, mCol) );		
	}
}

void GaugeWidget::saveSettings( QSettings& pSettings )
{	
	// Log Variable settings
	pSettings.setValue("logVariable", mLogVariable ? mLogVariable->name().c_str() : "");
	pSettings.setValue("row", mRow);
	pSettings.setValue("col", mCol);

	// Gauge settings
	pSettings.setValue("type", mGauge->type());
	mGauge->saveSettings(pSettings);
}

void GaugeWidget::loadSettings( QSettings& pSettings )
{
	// Log Variable settings
	LogVariableItem logVariableItem;
	logVariableItem.mLogVariable = DataRepository::instance()->findLogVariable( pSettings.value("logVariable", "").toString() );
	logVariableItem.mRow = pSettings.value("row", -1).toInt();
	logVariableItem.mCol = pSettings.value("col", -1).toInt();
	setLogVariableItem( logVariableItem );

	// Gauge settings
	AbstractGauge::Type gaugeType = (AbstractGauge::Type)pSettings.value("type", AbstractGauge::LINEAR).toInt();
	if ( gaugeType == AbstractGauge::RADIAL )
	{
		mGauge = new RadialGauge();
		mGaugeSettingDialog->setGaugeSetting( new RadialGaugeSetting );
	}
	else if ( gaugeType == AbstractGauge::NUMERIC )
	{
		mGauge = new NumericGauge();
		mGaugeSettingDialog->setGaugeSetting( new NumericGaugeSetting );
	}
	else/* if ( gaugeType == AbstractGauge::LINEAR )*/
	{
		mGauge = new LinearGauge();
		mGaugeSettingDialog->setGaugeSetting( new LinearGaugeSetting );
	}
	setGauge( mGauge );
	mGauge->loadSettings(pSettings);
}

void GaugeWidget::contextMenuEvent( QContextMenuEvent *pEvent )
{
	mMenu->move(pEvent->globalPos());
	mMenu->show();
	pEvent->accept();

	QWidget::contextMenuEvent(pEvent);
}