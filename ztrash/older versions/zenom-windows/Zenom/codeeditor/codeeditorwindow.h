#ifndef CODE_EDITOR_WINDOW_H
#define CODE_EDITOR_WINDOW_H

#include <QMainWindow>
#include "codeeditorwidget.h"


class CodeEditorWindow : public QMainWindow
{
	Q_OBJECT

public:
	CodeEditorWindow(QWidget *parent = 0);

public slots:
	void newFile();
	void openFile(const QString &path = QString());
	bool saveFile( const QString& pFileName );
	void loadFile( const QString& pFileName );

private:
	void setupEditor();
	void setupFileMenu();
	QString mFilePath;

	CodeEditorWidget* mCodeEditorWidget;

};

#endif