#include <QtGui>

#include "codeeditorwindow.h"

CodeEditorWindow::CodeEditorWindow(QWidget *parent)
	: QMainWindow(parent)
{
	setupFileMenu();
	setupEditor();

	setCentralWidget(mCodeEditorWidget);
	setWindowTitle(tr("Code Editor"));
}

void CodeEditorWindow::newFile()
{
	mCodeEditorWidget->clear();
}

void CodeEditorWindow::openFile(const QString &path)
{
	QString fileName = path;

	if (fileName.isNull())
		fileName = QFileDialog::getOpenFileName(this,
		tr("Open File"), "", "C++ Files (*.cpp *.h)");

	if (!fileName.isEmpty()) {
		QFile file(fileName);
		if (file.open(QFile::ReadOnly | QFile::Text))
			mCodeEditorWidget->setPlainText(file.readAll());
	}
}

bool CodeEditorWindow::saveFile( const QString& pFileName )
{
	/*
	QFile file( pFileName );
	if ( !file.open(QFile::WriteOnly | QFile::Text) ) 
	{
		QMessageBox::warning(this, tr("Zenom"),
			tr("Cannot write file %1:\n%2.")
			.arg(pFileName)
			.arg(file.errorString()));
		return false;
	}

	QTextStream out(&file);
	out << toPlainText();
	file.close();
*/
	return true;

}

void CodeEditorWindow::loadFile( const QString& pFileName )
{
	/*
	QFile file(pFileName);
	if (!file.open(QFile::ReadOnly | QFile::Text)) {
		QMessageBox::warning(this, tr("Application"),
			tr("Cannot read file %1:\n%2.")
			.arg(pFileName)
			.arg(file.errorString()));
		return;
	}

	QTextStream in(&file);
	setPlainText(in.readAll());

	file.close();
	*/
}


void CodeEditorWindow::setupEditor()
{
	QFont font;
	font.setFamily("Courier");
	font.setFixedPitch(true);
	font.setPointSize(10);

	mCodeEditorWidget = new CodeEditorWidget;
	mCodeEditorWidget->setFont(font);

	QFile file("mainwindow.h");
	if (file.open(QFile::ReadOnly | QFile::Text))
		mCodeEditorWidget->setPlainText(file.readAll());
}

void CodeEditorWindow::setupFileMenu()
{
	QMenu *fileMenu = new QMenu(tr("&File"), this);
	menuBar()->addMenu(fileMenu);

	fileMenu->addAction(tr("&New"), this, SLOT(newFile()),
		QKeySequence::New);

	fileMenu->addAction(tr("&Open..."), this, SLOT(openFile()),
		QKeySequence::Open);

	fileMenu->addAction(tr("&Save"), this, SLOT(saveFile()),
		QKeySequence::Save);

	fileMenu->addAction(tr("Save As..."), this, SLOT(saveAsFile()),
		QKeySequence::SaveAs);

	fileMenu->addAction(tr("E&xit"), qApp, SLOT(quit()),
		QKeySequence::Quit);
}
