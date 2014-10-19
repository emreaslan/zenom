#include "outputwidget.h"

QSize OutputText::sizeHint() const
{
	return QSize(250, 120);
}

OutputWidget::OutputWidget(QWidget *parent)
	: QDockWidget(parent)
{
	ui.setupUi(this);
	
	mOutputText = new OutputText();
	mOutputText->setReadOnly(true);

	setWidget( mOutputText );
}

OutputWidget::~OutputWidget()
{

}


