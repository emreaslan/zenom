#ifndef ZENOM_H
#define ZENOM_H

#include <QDoubleSpinBox>
#include <QSpinBox>

#include <QTimer>

#include <QtGui/QMainWindow>
#include <QXmlStreamReader>
#include "ui_zenom.h"

#include "newprojectdialog.h"
#include "gauges/gaugemanager.h"

#include "logvariableswidget.h"
#include "controlvariableswidget.h"
#include "outputwidget.h"
#include "codeeditorwindow.h"

#include "datarepository.h"

#include "utilities/projectcreator.h"

class Zenom : public QMainWindow
{
	Q_OBJECT

public:
	Zenom(QWidget *parent = 0, Qt::WFlags flags = 0);
	~Zenom();

private slots:
	void newProjectRequestSlot(const QString pName, const QString pLocation);
	void openProjectSlot();
	void saveProjectSlot();
	bool closeProjectSlot();

	void tick();

private:
	void enableWidgets(bool pEnable);
	bool maybeSave();
	void loadProject(const QString pConfigPath);

	Ui::ZenomClass ui;

	LogVariablesWidget* mLogVariablesWidget;
	ControlVariablesWidget* mControlVariablesWidget;
	OutputWidget* mOutputWidget;
	CodeEditorWidget* mCodeWidget;
	QDockWidget* mCodeDockWidget;

	QDoubleSpinBox* mFrequency;
	QSpinBox* mDuration;

	// Dialogs
	NewProjectDialog* mNewProjectDialog;
	
	// Manager Class
	GaugeManager* mGaugeManager;
};

#endif // ZENOM_H
