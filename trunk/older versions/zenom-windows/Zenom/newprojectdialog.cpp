#include "newprojectdialog.h"

NewProjectDialog::NewProjectDialog(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	connect( ui.browse, SIGNAL(clicked()), SLOT(browseClickedSlot()) );
	connect( ui.ok, SIGNAL(clicked()), SLOT(okClickedSlot()) );
	connect( ui.cancel, SIGNAL(clicked()), SLOT(hide()) );

	// Check OK
	connect( ui.name, SIGNAL(textChanged(const QString&)), SLOT(enableOKButton()) );
	connect( ui.location, SIGNAL(editTextChanged(const QString&)), SLOT(enableOKButton()) );

	ui.location->addItem( QDir::currentPath() );
	ui.location->setCurrentIndex( ui.location->findText(QDir::currentPath()) );
}

NewProjectDialog::~NewProjectDialog()
{

}

void NewProjectDialog::showEvent( QShowEvent *pEvent )
{
	ui.name->setFocus();
	ui.name->clear();
	ui.ok->setEnabled(false);	
	QDialog::showEvent( pEvent );
}

void NewProjectDialog::browseClickedSlot()
{
	QString directory = QFileDialog::getExistingDirectory(this,
		tr("Project Location"), QDir::currentPath());

	if ( !directory.isEmpty() )
	{
		if ( ui.location->findText(directory) == -1 )
			ui.location->addItem(directory);
		ui.location->setCurrentIndex( ui.location->findText(directory) );
	}
}

void NewProjectDialog::okClickedSlot()
{
	QString location = ui.location->currentText();
	QString name = ui.name->text();

	if ( QDir( location ).exists( name ) )
	{
		QMessageBox::warning(this, tr("Zenom"),
			tr("The project cannot be created because another project already exist in the folder:\n'%2'.")
			.arg( location));
	}
	else
	{
		emit newProjectRequest( name, location );
		hide();
	}
}

void NewProjectDialog::enableOKButton()
{
	// TODO classname, regular exp.
	QString location = ui.location->currentText();
	bool isDirExist = location.isEmpty() ? false : QDir( location ).exists();

	ui.ok->setEnabled( isDirExist && !ui.name->text().isEmpty() );
}
