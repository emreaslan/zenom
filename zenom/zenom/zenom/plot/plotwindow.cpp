#include "plotwindow.h"
#include "ui_plotwindow.h"

#include <QGridLayout>
#include <QInputDialog>
#include "attachlogvariabledialog.h"

PlotWindow::PlotWindow(QWidget *parent) :
    QMainWindow(parent), ui(new Ui::PlotWindow)
{
    ui->setupUi(this);

    connect( ui->plot, SIGNAL(autoscaleOff()), this, SLOT(autoscaleOffSlot()) );
}

PlotWindow::~PlotWindow()
{
    delete ui;
}

void PlotWindow::tick()
{
    ui->plot->tick();
}

void PlotWindow::saveSettings(QSettings &pSettings)
{
    pSettings.setValue("geometry", saveGeometry());
    ui->plot->saveSettings( pSettings );
}

void PlotWindow::loadSettings(QSettings &pSettings)
{
    restoreGeometry( pSettings.value("geometry").toByteArray() );
    ui->plot->loadSettings( pSettings );
}

void PlotWindow::closeEvent(QCloseEvent *pEvent)
{
    emit closed( this );
    QWidget::closeEvent( pEvent );
}

void PlotWindow::on_actionAttach_Log_Variable_triggered()
{
    AttachLogVariableDialog attachLogVariableDialog(this);
    int res = attachLogVariableDialog.exec();
    if ( res == QDialog::Accepted )
    {
        ui->plot->attactLogVariableItems( attachLogVariableDialog.selectedLogVariableItems() );
    }
}

void PlotWindow::on_actionSet_Time_Interval_triggered()
{
    bool isAccepted;
    int newInterval = QInputDialog::getInt ( this, "Set Time Interval", "Time Interval", ui->plot->timeInterval(), 1, 2147483647, 1, &isAccepted );
    if (isAccepted)
    {
        ui->plot->setTimeInterval( newInterval );
    }
}


void PlotWindow::on_actionAutoscale_triggered(bool pChecked)
{
    ui->plot->setAutoscale(pChecked);
}

void PlotWindow::autoscaleOffSlot()
{
    ui->actionAutoscale->setChecked( false );
}
