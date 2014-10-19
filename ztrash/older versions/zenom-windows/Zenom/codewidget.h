#ifndef CODEWIDGET_H
#define CODEWIDGET_H

#include <QDockWidget>
#include "ui_codewidget.h"
#include <QTextEdit>
#include <QTextStream>
#include <QFile>
#include <QMessageBox>

class CodeWidget : public QTextEdit
{
	Q_OBJECT
public:
	CodeWidget(QWidget *parent = 0);
	~CodeWidget();

	bool saveFile( const QString& pFileName );

	void loadFile( const QString& pFileName );

private:
	//Ui::CodeWidget ui;
};

#endif // CODEWIDGET_H
