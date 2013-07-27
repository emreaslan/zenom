#include "gaugesettingdialog.h"

GaugeSettingDialog::GaugeSettingDialog(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	setModal(true);
	
	connect( ui.ok, SIGNAL(clicked()), SLOT(okClickedSlot()) );
	connect( ui.cancel, SIGNAL(clicked()), SLOT(hide()) );
}

GaugeSettingDialog::~GaugeSettingDialog()
{

}

void GaugeSettingDialog::setGaugeWidget( GaugeWidget* pGaugeWidget )
{
	mGaugeWidget = pGaugeWidget;
}

void GaugeSettingDialog::setGaugeSetting( AbstractGaugeSetting* pSetting )
{
	mGaugeSetting = pSetting;
	pSetting->setParent(this);
	pSetting->move(180, 10);
}

void GaugeSettingDialog::showEvent( QShowEvent *pEvent )
{
	mGaugeSetting->initFrom( mGaugeWidget->gauge() );
	ui.logVariableList->setCurrentItem( mGaugeWidget->logVariableItem() );
	QDialog::showEvent(pEvent);
}

void GaugeSettingDialog::okClickedSlot()
{
	mGaugeSetting->initGauge( mGaugeWidget->gauge() );
	mGaugeWidget->setLogVariableItem( ui.logVariableList->currentLogVariableItem() );
	hide();
}

