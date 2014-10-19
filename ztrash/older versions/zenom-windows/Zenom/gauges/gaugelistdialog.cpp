#include "gaugelistdialog.h"

GaugeListDialog::GaugeListDialog(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	setModal(true);

	ui.stackedWidget->addWidget(new RadialGaugeSetting);
	ui.stackedWidget->addWidget(new LinearGaugeSetting);
	ui.stackedWidget->addWidget(new NumericGaugeSetting);

	ui.gaugeList->setCurrentRow(0);

	connect(ui.gaugeList,
		SIGNAL(currentItemChanged(QListWidgetItem*,QListWidgetItem*)),
		this, SLOT(changePage(QListWidgetItem*,QListWidgetItem*)));

	connect( ui.ok, SIGNAL(clicked()), SLOT(okClickedSlot()) );
	connect( ui.cancel, SIGNAL(clicked()), SLOT(hide()) );
}

GaugeListDialog::~GaugeListDialog()
{

}

void GaugeListDialog::changePage(QListWidgetItem *current, QListWidgetItem *previous)
{
	if (!current)
		current = previous;

	ui.stackedWidget->setCurrentIndex(ui.gaugeList->row(current));
}

void GaugeListDialog::okClickedSlot()
{
	AbstractGaugeSetting* gaugeSetting = static_cast<AbstractGaugeSetting*>(ui.stackedWidget->currentWidget());

	// new gauge	
	AbstractGauge* gauge = gaugeSetting->createGauge();
	gaugeSetting = gaugeSetting->clone();

	GaugeWidget* gaugeWidget = new GaugeWidget( parentWidget() );
	gaugeWidget->setGauge( gauge );
	gaugeWidget->setLogVariableItem( ui.logVariableList->currentLogVariableItem() );
	gaugeWidget->mGaugeSettingDialog->setGaugeSetting(gaugeSetting);

	emit gaugeWidgetCreated(gaugeWidget);
	hide();
}
