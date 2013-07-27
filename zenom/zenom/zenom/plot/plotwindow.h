#ifndef PLOTWINDOW_H
#define PLOTWINDOW_H

#include <QMainWindow>
#include <QSettings>

namespace Ui {
class PlotWindow;
}

class PlotWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit PlotWindow(QWidget *parent);

    ~PlotWindow();

    void tick();

    void saveSettings( QSettings& pSettings );

    void loadSettings( QSettings& pSettings );

signals:
    void closed( PlotWindow* ) ;

protected:
    virtual void closeEvent(QCloseEvent *pEvent);

private slots:

    void on_actionAttach_Log_Variable_triggered();
    
    void on_actionSet_Time_Interval_triggered();

    void on_actionAutoscale_triggered(bool pChecked);

    void autoscaleOffSlot();

private:
    Ui::PlotWindow *ui;
};

#endif // PLOTWINDOW_H
