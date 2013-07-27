#include <QtGui>

#include "codeeditorwidget.h"

CodeEditorWidget::CodeEditorWidget(QWidget *pParent) : QPlainTextEdit(pParent)
{
	this->setWindowTitle("Code Editor");
	mLineNumberArea = new LineNumberArea(this);

	connect(this, SIGNAL(blockCountChanged(int)), this, SLOT(updateLineNumberAreaWidth(int)));
	connect(this, SIGNAL(updateRequest(QRect,int)), this, SLOT(updateLineNumberArea(QRect,int)));
	connect(this, SIGNAL(cursorPositionChanged()), this, SLOT(highlightCurrentLine()));

	mHighlighter = new Highlighter(document());

	updateLineNumberAreaWidth(0);
	highlightCurrentLine();
}

int CodeEditorWidget::lineNumberAreaWidth()
{
	int digits = 1;
	int max = qMax(1, blockCount());
	while (max >= 10) {
		max /= 10;
		++digits;
	}

	int space = 3 + fontMetrics().width(QLatin1Char('9')) * digits;

	return space;
}



void CodeEditorWidget::updateLineNumberAreaWidth(int pNewBlockCount)
{ 
	setViewportMargins(lineNumberAreaWidth(), 0, 0, 0);
}


void CodeEditorWidget::updateLineNumberArea(const QRect &rect, int dy)
{
	if (dy)
		mLineNumberArea->scroll(0, dy);
	else
		mLineNumberArea->update(0, rect.y(), mLineNumberArea->width(), rect.height());

	if (rect.contains(viewport()->rect()))
		updateLineNumberAreaWidth(0);
}



void CodeEditorWidget::resizeEvent(QResizeEvent *e)
{
	QPlainTextEdit::resizeEvent(e);

	QRect cr = contentsRect();
	mLineNumberArea->setGeometry(QRect(cr.left(), cr.top(), lineNumberAreaWidth(), cr.height()));
}


void CodeEditorWidget::highlightCurrentLine()
{
	QList<QTextEdit::ExtraSelection> extraSelections;

	if (!isReadOnly()) {
		QTextEdit::ExtraSelection selection;

		QColor lineColor = QColor(Qt::yellow).lighter(160);

		selection.format.setBackground(lineColor);
		selection.format.setProperty(QTextFormat::FullWidthSelection, true);
		selection.cursor = textCursor();
		selection.cursor.clearSelection();
		extraSelections.append(selection);
	}

	setExtraSelections(extraSelections);
}


void CodeEditorWidget::lineNumberAreaPaintEvent(QPaintEvent *event)
{
	QPainter painter(mLineNumberArea);
	painter.fillRect(event->rect(), Qt::lightGray);

	QTextBlock block = firstVisibleBlock();
	int blockNumber = block.blockNumber();
	int top = (int) blockBoundingGeometry(block).translated(contentOffset()).top();
	int bottom = top + (int) blockBoundingRect(block).height();

	while (block.isValid() && top <= event->rect().bottom()) {
		if (block.isVisible() && bottom >= event->rect().top()) {
			QString number = QString::number(blockNumber + 1);
			painter.setPen(Qt::black);
			painter.drawText(0, top, mLineNumberArea->width(), fontMetrics().height(),
				Qt::AlignRight, number);
		}

		block = block.next();
		top = bottom;
		bottom = top + (int) blockBoundingRect(block).height();
		++blockNumber;
	}
}

bool CodeEditorWidget::saveFile( const QString& pFileName )
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

void CodeEditorWidget::loadFile( const QString& pFileName )
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


