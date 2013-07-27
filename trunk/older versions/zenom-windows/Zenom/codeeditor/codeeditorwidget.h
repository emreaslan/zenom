#ifndef CODE_EDITOR_WIDGET_H
#define CODE_EDITOR_WIDGET_H

#include <QPlainTextEdit>
#include <QObject>
#include "highlighter.h"

QT_BEGIN_NAMESPACE
class QPaintEvent;
class QResizeEvent;
class QSize;
class QWidget;
QT_END_NAMESPACE

class LineNumberArea;


class CodeEditorWidget : public QPlainTextEdit
{
	Q_OBJECT

public:
	CodeEditorWidget(QWidget *parent = 0);

	void lineNumberAreaPaintEvent(QPaintEvent *event);
	int lineNumberAreaWidth();

	bool saveFile( const QString& pFileName );

	void loadFile( const QString& pFileName );

protected:
	void resizeEvent(QResizeEvent *event);

	private slots:
		void updateLineNumberAreaWidth(int newBlockCount);
		void highlightCurrentLine();
		void updateLineNumberArea(const QRect &, int);

private:
	QWidget *mLineNumberArea;
	Highlighter *mHighlighter;
};


class LineNumberArea : public QWidget
{
public:
	LineNumberArea(CodeEditorWidget *editor) : QWidget(editor) {
		mCodeEditor = editor;
	}

	QSize sizeHint() const {
		return QSize(mCodeEditor->lineNumberAreaWidth(), 0);
	}

protected:
	void paintEvent(QPaintEvent *event) {
		mCodeEditor->lineNumberAreaPaintEvent(event);
	}

private:
	CodeEditorWidget *mCodeEditor;
};

#endif // CODE_EDITOR_WIDGET_H
