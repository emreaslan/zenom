#include "zenom.h"


Zenom::Zenom(QWidget *parent, Qt::WFlags flags)
	: QMainWindow(parent, flags)
{
	ui.setupUi(this);

	ui.simulationToolBar->layout()->setSpacing(6);
	ui.fileToolBar->layout()->setSpacing(6);

	//ui.simulationToolBar->addWidget( new QLabel(" Frequency ") );
	mFrequency = new QDoubleSpinBox();
	mFrequency->setDecimals(3);
	mFrequency->setMinimum(1);
	mFrequency->setMaximum(999999999);
	mFrequency->setValue(1);
	mFrequency->setSuffix(" Hz");
	mFrequency->setToolTip("Frequency");
	ui.simulationToolBar->addWidget(mFrequency);

	mDuration = new QSpinBox();
	mDuration->setMinimum(1);
	mDuration->setMaximum(999999999);
	mDuration->setValue(10);
	mDuration->setSuffix(" sec");
	mDuration->setToolTip("Duration");
	mDuration->setContentsMargins(20, mDuration->contentsMargins().top(), mDuration->contentsMargins().right(),mDuration->contentsMargins().bottom());
	ui.simulationToolBar->addWidget(mDuration);

	ui.menuView->addSeparator();

	mCodeWidget = new CodeEditorWidget();	
	mCodeDockWidget = new QDockWidget( "CodeEditorDockWidget" );
	mCodeDockWidget->setObjectName("CodeEditorDockWidget");
	mCodeDockWidget->setWidget( mCodeWidget );
	addDockWidget(Qt::LeftDockWidgetArea, mCodeDockWidget);	
	ui.menuView->addAction( mCodeDockWidget->toggleViewAction() );

	mLogVariablesWidget = new LogVariablesWidget();
	addDockWidget(Qt::RightDockWidgetArea, mLogVariablesWidget, Qt::Horizontal);
	ui.menuView->addAction( mLogVariablesWidget->toggleViewAction() );

	mControlVariablesWidget = new ControlVariablesWidget();
	tabifyDockWidget(mLogVariablesWidget, mControlVariablesWidget);
	ui.menuView->addAction( mControlVariablesWidget->toggleViewAction() );
	mLogVariablesWidget->raise();

	ui.menuView->addSeparator();

	mOutputWidget = new OutputWidget();
	addDockWidget(Qt::BottomDockWidgetArea, mOutputWidget);
	ui.menuView->addAction( mOutputWidget->toggleViewAction() );

	// connections
	//connect(ui.actionNew, SIGNAL(triggered()), SLOT(newProjectSlot()) );
	connect(ui.actionOpen, SIGNAL(triggered()), SLOT(openProjectSlot()) );
	connect(ui.actionSave, SIGNAL(triggered()), SLOT(saveProjectSlot()) );
	connect(ui.actionClose, SIGNAL(triggered()), SLOT(closeProjectSlot()));

	mNewProjectDialog = new NewProjectDialog(this);
	connect( ui.actionNew, SIGNAL(triggered()), mNewProjectDialog, SLOT(show()) );
	connect( mNewProjectDialog, SIGNAL(newProjectRequest(const QString, const QString)), SLOT(newProjectRequestSlot(const QString, const QString)) );
	
	
	mGaugeManager = new GaugeManager(this);
	connect( ui.actionWatch, SIGNAL(triggered()), mGaugeManager, SLOT(showGaugeListDialog()) );

	closeProjectSlot();

	mLogVariablesWidget->setLogVariableList( DataRepository::instance()->mLogVariableList );
	mControlVariablesWidget->setControlVariableList( DataRepository::instance()->mControlVariableList );

	loadProject("../test/test.znm");

	QTimer *timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(tick()));
	timer->start(50);
}

Zenom::~Zenom()
{

}

void Zenom::newProjectRequestSlot(const QString pName, const QString pLocation)
{
	if ( closeProjectSlot() )
	{
		// create the project folder and files
		if ( ProjectCreator::create(this, pName, pLocation) )
		{
			// load new project
			loadProject( QDir(pLocation).filePath( pName + QDir::separator() + pName + ".znm") );
		}
	}
}

void Zenom::openProjectSlot()
{
	QString fileName = QFileDialog::getOpenFileName(this, tr("Open Project"),
                                                 "",
                                                 tr("Project Files (*.znm)"));
	if ( !fileName.isEmpty() )
	{
		if ( closeProjectSlot() )
		{
			loadProject( fileName );
		}
	}
}

void Zenom::loadProject(const QString pConfigPath)
{
	DataRepository::instance()->mProjectFileInfo.setFile( pConfigPath );
	
	QApplication::setOverrideCursor(Qt::WaitCursor);

	// load cpp file
	mCodeWidget->loadFile( DataRepository::instance()->mProjectFileInfo.cppFile() );
	mCodeDockWidget->setWindowTitle( DataRepository::instance()->mProjectFileInfo.projectName() + ".cpp" );

	// load widgets
	QSettings settings(DataRepository::instance()->mProjectFileInfo.configFile(),  QSettings::IniFormat);

	settings.beginGroup("zenom");
	mGaugeManager->loadSettings( settings );	// Load Gauges
												// TODO H plot
	restoreGeometry( settings.value("geometry").toByteArray() );
	restoreState( settings.value("state").toByteArray() );
	settings.endGroup();
	
	QApplication::restoreOverrideCursor();
	
	enableWidgets( true );	
	statusBar()->showMessage(tr("Project loaded"), 2000);
}

void Zenom::saveProjectSlot()
{	
	QApplication::setOverrideCursor(Qt::WaitCursor);

	// TODO dock olmayan widget kayitlari sorunlu.
	// bir kere dock olup cikarilinca cozuluyor.
	// save cpp file
	mCodeWidget->saveFile( DataRepository::instance()->mProjectFileInfo.cppFile() );
	
	// save widgets
	QSettings settings(DataRepository::instance()->mProjectFileInfo.configFile(),  QSettings::IniFormat);
	settings.clear();

	settings.beginGroup("zenom");
	mGaugeManager->saveSettings( settings );		// Save Gauges
													// TODO H load plot
	settings.setValue("geometry", saveGeometry());
	settings.setValue("state", saveState());
	settings.endGroup();

	QApplication::restoreOverrideCursor();
	
	statusBar()->showMessage(tr("Project saved"), 2000);
}

bool Zenom::closeProjectSlot()
{	
	bool closeProject = maybeSave();
	if ( closeProject )
	{
		enableWidgets( false );
		mGaugeManager->clear();
		mControlVariablesWidget->clear();
		mLogVariablesWidget->clear();
		// TODO H plot
	}

	return closeProject;
}

bool Zenom::maybeSave()
{	
	if ( mCodeWidget->document()->isModified() )
	{
		QMessageBox::StandardButton ret;
		ret = QMessageBox::warning(this, tr("Zenom"),
			tr("The current project will be closed.\n"
			"Do you want to save your changes?"),
			QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);

		if (ret == QMessageBox::Yes)
		{
			saveProjectSlot();
			return true;
		}
		else if (ret == QMessageBox::Cancel)
			return false;
	}

	return true;
}

void Zenom::enableWidgets( bool pEnable )
{
	centralWidget()->setVisible( !pEnable );

	mControlVariablesWidget->widget()->setEnabled( pEnable );
	mLogVariablesWidget->widget()->setEnabled( pEnable );

	mCodeDockWidget->toggleViewAction()->setEnabled( pEnable );
	mCodeDockWidget->setVisible( pEnable );
	mCodeWidget->setEnabled( pEnable );

	ui.actionSave->setEnabled( pEnable );
	ui.actionBuild->setEnabled( pEnable );
	ui.actionStart->setEnabled( pEnable );
	ui.actionStop->setEnabled( pEnable );
	mFrequency->setEnabled( pEnable );
	mDuration->setEnabled( pEnable );

	ui.actionWatch->setEnabled( pEnable );
	ui.actionPlot->setEnabled( pEnable );
	ui.actionPlotXY->setEnabled( pEnable );
	ui.actionScene->setEnabled( pEnable );
}

void Zenom::tick()
{
	DataRepository::instance()->tick();
	mGaugeManager->tick();
}
