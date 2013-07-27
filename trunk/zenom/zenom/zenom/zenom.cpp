#include "zenom.h"
#include "ui_zenom.h"

#include <QFileDialog>
#include <unistd.h>

#include <iostream>
#include <string>

#include <QFileInfo>
#include <QTime>

Zenom::Zenom(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Zenom)
{
    ui->setupUi(this);
    createRecentFileActions();
    updateRecentFileActions();
    ui->output->setReadOnly(true);
    ui->statusBar->addPermanentWidget( mStatusBar = new StatusBar() );

    mDataRepository = DataRepository::instance();

    mControlVariablesWidget = new ControlVariablesWidget(this);
    ui->menu_View->addAction( mControlVariablesWidget->toggleViewAction() );

    mLogVariablesWidget = new LogVariablesWidget(this);
    ui->menu_View->addAction( mLogVariablesWidget->toggleViewAction() );

    mGaugeManager = new GaugeManager(this);
    mPlotManager = new PlotManager(this);
    mSceneManager = new SceneManager(this);
    connect( mSceneManager, SIGNAL(warningMessage(const QString&)), ui->output, SLOT(appendWarningMessage(const QString&)) );


    mMessageListenerTask = new MessageListenerTask(this);

    connect( &mControlBaseProcess, SIGNAL( error(QProcess::ProcessError) ), SLOT( controlBaseProcessError(QProcess::ProcessError) ));

    setSimulationState( TERMINATED );

    connect(&mTimer, SIGNAL(timeout()), SLOT(doloop()));
}

Zenom::~Zenom()
{
    terminateProject();
    delete mMessageListenerTask;
    delete ui;
}

void Zenom::on_startButton_clicked()
{
    if( simulationState() == STOPPED )	// Start
    {
        setSimulationState( RUNNING );

        mDataRepository->deleteLogVariablesHeap();
        mDataRepository->createLogVariablesHeap();
        mDataRepository->sendStateRequest( R_START );

        ui->output->appendMessage( QString("Simulation started.") );
    }
    else if( simulationState() == RUNNING )	// Pause
    {
        setSimulationState( PAUSED );
        mDataRepository->sendStateRequest( R_PAUSE );

        ui->output->appendMessage( QString("Simulation paused.") );
    }
    else if( simulationState() == PAUSED )	// Resume
    {
        setSimulationState( RUNNING );
        mDataRepository->sendStateRequest( R_RESUME );

        ui->output->appendMessage( QString("Simulation resumed.") );
    }
}

void Zenom::on_stopButton_clicked()
{
    setSimulationState( STOPPED );
    mDataRepository->sendStateRequest( R_STOP );

    ui->output->appendMessage( QString("Simulation stopped.") );
}

void Zenom::on_actionWatch_triggered()
{
    mGaugeManager->showGaugeListDialog();
}

void Zenom::on_actionPlot_triggered()
{
    mPlotManager->createPlot();
}

void Zenom::on_actionScene_triggered()
{
    mSceneManager->createScene();
}

void Zenom::controlBaseProcessError( QProcess::ProcessError pError )
{
    if( pError == QProcess::FailedToStart )
    {
        ui->output->appendErrorMessage( "Error: Failed opening project: The program does not exist." );
    }
    else if( pError == QProcess::Crashed )
    {
        ui->output->appendErrorMessage( "Error: The program has unexpectedly finished. Please, reload the project to start." );
    }
    else
    {
        ui->output->appendErrorMessage( "Error: An unknown error occurred. Please, reload the project to start." );
    }

    setSimulationState( CRASHED );
}

void Zenom::doloop()
{
    mStatusBar->setElapsedTime( mDataRepository->elapsedTimeSecond() );
    mStatusBar->setOverruns( mDataRepository->overruns() );
    mGaugeManager->tick();
    mPlotManager->tick();
    mSceneManager->tick();
}

State Zenom::simulationState()
{
    return mSimState;
}

void Zenom::setSimulationState(State pState)
{
    mSimState = pState;

    // File Menu
    ui->actionSave_Project->setEnabled( pState != TERMINATED );
    ui->actionReload->setEnabled( pState != TERMINATED );

    // View Menu
    ui->actionWatch->setEnabled( pState != TERMINATED );
    ui->actionPlot->setEnabled( pState != TERMINATED );
    ui->actionScene->setEnabled( pState != TERMINATED );
    mLogVariablesWidget->toggleViewAction()->setEnabled( pState != TERMINATED );
    mControlVariablesWidget->toggleViewAction()->setEnabled( pState != TERMINATED );

    // Zenom
    ui->frequency->setEnabled( pState == STOPPED );
    ui->duration->setEnabled( pState == STOPPED );

    ui->startButton->setIcon( style()->standardIcon( pState == RUNNING ? QStyle::SP_MediaPause : QStyle::SP_MediaPlay ) );
    ui->startButton->setEnabled( pState != TERMINATED && pState != CRASHED );
    ui->stopButton->setIcon( style()->standardIcon(QStyle::SP_MediaStop) );
    ui->stopButton->setEnabled( pState == RUNNING || pState == PAUSED );

    mStatusBar->setVisible( pState != TERMINATED );

    // Log Variable Widget
    mLogVariablesWidget->setDisabled( pState == RUNNING || pState == PAUSED );
}

void Zenom::on_actionOpen_Project_triggered()
{
    QFileDialog dialog( this );
    dialog.setFileMode( QFileDialog::ExistingFile );
    dialog.setNameFilter( "Zenom Files (*.znm)" );
    dialog.setViewMode( QFileDialog::Detail );
    if ( dialog.exec() )
    {
        openProject( dialog.selectedFiles()[0] );
    }
}

void Zenom::openProject(const QString& pProjectPath)
{
    terminateProject();     // close project if already a project was opened.

    // TODO catch blogu ve return kontrol et hersey silindigine emin ol
    try
    {
        QFileInfo fileInfo( pProjectPath );
        if ( !fileInfo.exists() )
        {
            ui->output->appendErrorMessage( QString("Error: Failed opening project: '%1' does not exist.").arg(pProjectPath) );
            return;
        }

        QDir::setCurrent( fileInfo.path() );
        const QString projectName = fileInfo.baseName();
        const QString controlBaseProgram = fileInfo.dir().filePath( fileInfo.baseName() );

        mDataRepository->setProjectName( projectName.toStdString() );

        mDataRepository->createMessageQueues();


        mMessageListenerTask->create( mDataRepository->projectName() + "MessageListenerTask" );
        mMessageListenerTask->start();

        mControlBaseProcess.start( controlBaseProgram, QStringList() << projectName );
        if ( mControlBaseProcess.waitForStarted() )
        {
            // TODO wait condition icin timeout
            // wait olmadan mesaj gelirse
            mMutex.lock();
            if ( !mWaitCondition.wait(&mMutex, 10000) )
            {
                ui->output->appendErrorMessage( QString("Error: Failed connecting program: The program does not implemented specified format.") );
                mMutex.unlock();
                return;
            }
            mMutex.unlock();

            if( !mDataRepository->readVariablesFromFile() )
            {
                ui->output->appendErrorMessage( QString("Error: Failed connecting program: The program does not implemented specified format.") );
                return;
            }

            mDataRepository->createMainControlHeap();

            mControlVariablesWidget->setControlVariableList( mDataRepository->controlVariables() );
            mLogVariablesWidget->setLogVariableList( mDataRepository->logVariables() );
            mGaugeManager->setLogVariableList( mDataRepository->logVariables() );

            loadSettings( pProjectPath );

            setSimulationState( STOPPED );
            mTimer.start(50);

            setWindowTitle( fileInfo.baseName() );

            mProjectPath = pProjectPath;

            insertRecentFileList( pProjectPath );

            ui->output->appendMessage( QString("%1 succesfully loaded.").arg(projectName) );
        }
    }
    catch( ZnmException e )
    {
        // TODO file exist ise ne olacak
        std::cout << "openProject" << std::string( e.what() ) << std::endl;
    }
}

void Zenom::loadSettings(const QString &pProjectName)
{
    QApplication::setOverrideCursor(Qt::WaitCursor);

    // load widgets
    QSettings settings( pProjectName , QSettings::IniFormat);

    settings.beginGroup("zenom");
    setFrequency( settings.value("frequency", 1).toDouble() );
    setDuration( settings.value("duration", 100).toDouble() );
    restoreGeometry( settings.value("geometry").toByteArray() );
    mLogVariablesWidget->loadSettings( settings );      // log variable values
    mControlVariablesWidget->loadSettings( settings );	// control variable values
    mGaugeManager->loadSettings( settings );            // gauges
    mPlotManager->loadSettings( settings );             // plots
    mSceneManager->loadSettings( settings );            // scenes
    settings.endGroup();

    QApplication::restoreOverrideCursor();
}

void Zenom::on_actionSave_Project_triggered()
{
    QApplication::setOverrideCursor(Qt::WaitCursor);

    QSettings settings( mProjectPath, QSettings::IniFormat );
    settings.clear();

    settings.beginGroup("zenom");
    settings.setValue("frequency", ui->frequency->text());
    settings.setValue("duration", ui->duration->text());
    settings.setValue("geometry", saveGeometry());
    mLogVariablesWidget->saveSettings( settings );      // log variable values
    mControlVariablesWidget->saveSettings( settings );  // control variable values
    mGaugeManager->saveSettings( settings );            // gauges
    mPlotManager->saveSettings( settings );             // plots
    mSceneManager->saveSettings( settings );            // scenes
    settings.endGroup();

    QApplication::restoreOverrideCursor();
}

void Zenom::on_actionReload_triggered()
{
    terminateProject();
    openProject( mProjectPath );
}

void Zenom::on_actionExit_triggered()
{
    close();
}

void Zenom::on_frequency_editingFinished()
{
    setFrequency( ui->frequency->text().toDouble() );
}

void Zenom::setFrequency(double pFrequency)
{
    if ( pFrequency > 0 )
    {
        mDataRepository->setFrequency( pFrequency );
        ui->frequency->setText( QString::number(pFrequency) );
        mLogVariablesWidget->mainFrequencyChanged( pFrequency );
    }
    else
    {
        ui->frequency->setText( QString::number(mDataRepository->frequency()) );
    }
}

void Zenom::on_duration_editingFinished()
{
    setDuration( ui->duration->text().toDouble() );
}

void Zenom::setDuration(double pDuration)
{
    if ( pDuration > 0 )
    {
        mStatusBar->setDuration( pDuration );
        mDataRepository->setDuration( pDuration );
        ui->duration->setText( QString::number(pDuration) );
        mLogVariablesWidget->mainDurationChanged( pDuration );
    }
    else
    {
        ui->duration->setText( QString::number(mDataRepository->duration()) );
    }
}

void Zenom::terminateProject()
{
    QApplication::setOverrideCursor(Qt::WaitCursor);

    // if the controlbase is running, stop it and then terminate.
    if( simulationState() == RUNNING || simulationState() == PAUSED )
    {
        on_stopButton_clicked();
    }

    mMessageListenerTask->deleteTask();

    if ( mControlBaseProcess.state() != QProcess::NotRunning )
    {
        mDataRepository->sendStateRequest( R_TERMINATE );
        if ( !mControlBaseProcess.waitForFinished() )    // Finish the process
        {
            //appendTextToOutput("Terminating unsuccesful");
            mControlBaseProcess.kill(); // TODO process bir sure sonlanmaz ise kill etsek mi? kill edince crashed oluyor.
        }
    }

    setSimulationState( TERMINATED );

    mTimer.stop();

    mDataRepository->deleteMessageQueues();
    mDataRepository->deleteMainControlHeap();
    mDataRepository->deleteLogVariablesHeap();

    mControlVariablesWidget->clear();
    mLogVariablesWidget->clear();

    mDataRepository->clear();

    mGaugeManager->clear();
    mPlotManager->clear();
    mSceneManager->clear();

    ui->output->clear();

    QApplication::restoreOverrideCursor();
}

void Zenom::createRecentFileActions()
{
    for (int i = 0; i < MaxRecentFiles; ++i)
    {
        recentFileActs[i] = new QAction( QString::number(i), this);
        ui->menu_File->insertAction( ui->actionExit, recentFileActs[i] );
        recentFileActs[i]->setVisible(false);
        connect(recentFileActs[i], SIGNAL(triggered()),
                this, SLOT(openRecentFile()));
    }

    separatorAct = ui->menu_File->insertSeparator( ui->actionExit );
}

void Zenom::updateRecentFileActions()
{
    QSettings settings;
    QStringList files = settings.value("recentFileList").toStringList();

    int numRecentFiles = qMin(files.size(), (int)MaxRecentFiles);

    for (int i = 0; i < numRecentFiles; ++i)
    {
        QString filename = QFileInfo( files[i] ).fileName();
        QString text = tr("&%1 %2").arg(i + 1).arg( filename );
        recentFileActs[i]->setText(text);
        recentFileActs[i]->setData(files[i]);
        recentFileActs[i]->setVisible(true);
    }

    for (int j = numRecentFiles; j < MaxRecentFiles; ++j)
        recentFileActs[j]->setVisible(false);

    separatorAct->setVisible(numRecentFiles > 0);
}

void Zenom::insertRecentFileList(const QString &pProjectPath)
{
    QSettings settings;
    QStringList files = settings.value("recentFileList").toStringList();
    files.removeAll( pProjectPath );
    files.prepend( pProjectPath );
    while (files.size() > MaxRecentFiles)
        files.removeLast();

    settings.setValue("recentFileList", files);

    updateRecentFileActions();
}

void Zenom::openRecentFile()
{
    QAction *action = qobject_cast<QAction *>(sender());
    if (action)
        openProject( action->data().toString() );
}
