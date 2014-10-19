#include "codewidget.h"
#include <QTextEdit>

CodeWidget::CodeWidget(QWidget *parent)
	: QTextEdit(parent)
{
	//ui.setupUi(this);
	//setWidget(new QTextEdit() );
}

CodeWidget::~CodeWidget()
{

}

bool CodeWidget::saveFile( const QString& pFileName )
{
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

	return true;
}

void CodeWidget::loadFile( const QString& pFileName )
{
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
}
