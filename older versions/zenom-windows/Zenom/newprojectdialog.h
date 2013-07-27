#ifndef NEWPROJECTDIALOG_H
#define NEWPROJECTDIALOG_H

#include <QDialog>
#include <QFileDialog>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include "ui_newprojectdialog.h"

class NewProjectDialog : public QDialog
{
	Q_OBJECT

public:
	NewProjectDialog(QWidget *parent = 0);
	~NewProjectDialog();

signals:
	void newProjectRequest(const QString pName, const QString pLocation);

protected:
	void showEvent(QShowEvent *pEvent);

private slots:
	void browseClickedSlot();
	void okClickedSlot();
	void enableOKButton();

private:
	Ui::NewProjectDialog ui;
};

#endif // NEWPROJECTDIALOG_H
