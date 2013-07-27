#include "controlvariableswidget.h"

#include <QLabel>
#include <QTableWidget>

ControlVariablesWidget::ControlVariablesWidget(QWidget *parent)
	: QDockWidget(parent)
{
	ui.setupUi(this);
	connect( ui.apply, SIGNAL(pressed()), SLOT(applyPressedSlot()) );
	connect( ui.cancel, SIGNAL(pressed()), SLOT(cancelPressedSlot()) );
}

ControlVariablesWidget::~ControlVariablesWidget()
{

}

void ControlVariablesWidget::setControlVariableList( const ControlVariableList& pControlVariableList )
{
	ui.controlVariableTable->setRowCount( pControlVariableList.size() );
	
	ControlVariable* controlVariable;
	int maxColSize = 100;

	for ( size_t i = 0; i < pControlVariableList.size(); ++i )
	{
		controlVariable = pControlVariableList[i];

		QTableWidgetItem* name = new QTableWidgetItem( QString::fromStdString(controlVariable->name()) );
		name->setFlags( Qt::ItemIsEnabled );
		ui.controlVariableTable->setItem(i, 0, name);

		// Value Table
		QTableWidget* valueTable = new QTableWidget(controlVariable->row(), controlVariable->col());
		valueTable->horizontalHeader()->setDefaultSectionSize(60);
		valueTable->horizontalHeader()->hide();
		valueTable->verticalHeader()->hide();
		connect(valueTable, SIGNAL(itemChanged(QTableWidgetItem*)), SLOT(itemChangedSlot(QTableWidgetItem*)) );

		for ( size_t k = 0; k < controlVariable->row(); ++k )
		{
			for ( size_t j = 0; j < controlVariable->col(); ++j )
			{
				valueTable->setItem( k, j, new QTableWidgetItem( QString::number(controlVariable->data()[j+k*controlVariable->col()]) ) );
			}
		}

		ui.controlVariableTable->setCellWidget(i, 1, valueTable );
		ui.controlVariableTable->verticalHeader()->resizeSection(i, controlVariable->row() * valueTable->verticalHeader()->defaultSectionSize() + 5 );

		maxColSize = qMax( maxColSize, controlVariable->col() * valueTable->horizontalHeader()->defaultSectionSize() );
	}

	// resize "Value" column
	ui.controlVariableTable->horizontalHeader()->resizeSection( 1, maxColSize + 5 );

	// Disable apply and cancel buttons
	enableButtons(false);
}

void ControlVariablesWidget::clear()
{
	ui.controlVariableTable->clearContents();
	ui.controlVariableTable->setRowCount(0);
}

void ControlVariablesWidget::applyPressedSlot()
{
	enableButtons(false);
}

void ControlVariablesWidget::cancelPressedSlot()
{
	enableButtons(false);
}

void ControlVariablesWidget::itemChangedSlot(QTableWidgetItem* pItem)
{
	enableButtons(true);
}

void ControlVariablesWidget::enableButtons(bool pEnable)
{
	ui.apply->setEnabled(pEnable);
	ui.cancel->setEnabled(pEnable);
}