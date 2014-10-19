#ifndef OUTPUTWIDGET_H
#define OUTPUTWIDGET_H

#include <QDockWidget>
#include <QPlainTextEdit>
#include "ui_outputwidget.h"

class OutputText : public QPlainTextEdit
{
public:
	 virtual QSize sizeHint() const;
};


class OutputWidget : public QDockWidget
{
	Q_OBJECT

public:
	OutputWidget(QWidget *parent = 0);
	~OutputWidget();

private:
	Ui::OutputWidget ui;
	OutputText* mOutputText;

};

#endif // OUTPUTWIDGET_H
