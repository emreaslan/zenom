#ifndef ZENOM_H
#define ZENOM_H

#include <QMainWindow>
#include <QProcess>
#include <QWaitCondition>
#include <QMutex>
#include <QTimer>

#include <datarepository.h>
#include <MessageQueueXn.h>

#include "messagelistenertask.h"
class MessageListenerTask;

#include "widget/statusbar.h"
#include "controlvariableswidget.h"
#include "logvariableswidget.h"
#include "gauge/gaugemanager.h"
#include "plot/plotmanager.h"
#include "scene/scenemanager.h"
#include "aboutdialog.h"


namespace Ui {
class Zenom;
}

class Zenom : public QMainWindow
{
    Q_OBJECT
    friend class MessageListenerTask;
    
public:
    explicit Zenom(QWidget *parent = 0);

    ~Zenom();

private slots:

    // File Menu
    void on_actionOpen_Project_triggered();
    void on_actionSave_Project_triggered();
    void on_actionReload_triggered();
    void openRecentFile();
    void on_actionExit_triggered();

    // View Menu
    void on_actionWatch_triggered();
    void on_actionPlot_triggered();
    void on_actionScene_triggered();

    void on_startButton_clicked();
    void on_stopButton_clicked();

    void on_frequency_editingFinished();
    void on_duration_editingFinished();

    /**
     * Arayuzleri gunceller.
     * Plot, scene ve gauge arayüzlerindeki log-variable gösterimleri
     * bu fonksiyon cagrilarak guncellenir.
     */
    void doloop();

    /**
     * Control-Base process'te bir hata olustugunda cagrilir.
     */
    void controlBaseProcessError( QProcess::ProcessError pError );

    /**
     * Kullanici tarafindan girilen standart mesajlarini alir.
     * Control-Base tarafindan cout kullanilarak
     * yazilan mesajlar ele alinir.
     */
    void controlBaseReadyReadStandardOutput();

    /**
     * Kullanici tarafindan girilen hata mesajlarini alir.
     * Control-Base tarafindan cerr kullanilarak
     * yazilan mesajlar ele alinir.
     */
    void controlBaseReadyReadStandardError();

    void on_action_About_zenom_triggered();

private:
    Ui::Zenom *ui;
    StatusBar* mStatusBar;
    QString mProjectPath;

    // File Menu
    void openProject(const QString& pProjectName);
    void loadSettings(const QString& pProjectName);
    void terminateProject();

    ControlVariablesWidget* mControlVariablesWidget;
    LogVariablesWidget* mLogVariablesWidget;    
    GaugeManager* mGaugeManager;
    PlotManager* mPlotManager;
    SceneManager* mSceneManager;

    QProcess mControlBaseProcess;

    MessageListenerTask* mMessageListenerTask;
    QWaitCondition mWaitCondition;
    QMutex mMutex;

    State simulationState();
    void setSimulationState( State pState );
    State mSimState;

    DataRepository* mDataRepository;

    void setFrequency(double pFrequency);
    void setDuration(double pDuration);
    QTimer mTimer;

    // the most recent files loaded by user.
    void createRecentFileActions();
    void updateRecentFileActions();
    void insertRecentFileList( const QString& pProjectPath );
    enum { MaxRecentFiles = 5 };
    QAction *recentFileActs[MaxRecentFiles];
    QAction *separatorAct;

    // About Dialog
    AboutDialog* mAboutDialog;
};

#endif // ZENOM_H
