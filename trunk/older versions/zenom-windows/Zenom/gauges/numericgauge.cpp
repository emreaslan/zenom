#include "numericgauge.h"

#include <QGridLayout>

NumericGauge::NumericGauge(QWidget *pParent)
	: AbstractGauge(pParent)
{
	// LCD
	mLCDNumber = new QLCDNumber();
	mLCDNumber->setFrameShadow( QFrame::Plain );
	mLCDNumber->setSegmentStyle( QLCDNumber::Flat );
	mLCDNumber->setLineWidth(0);

	QPalette p = mLCDNumber->palette();
	p.setColor(QPalette::All, QPalette::Window, QColor(150, 220, 120));
	p.setColor(QPalette::All, QPalette::WindowText, QColor(0, 0, 0));
	mLCDNumber->setPalette( p );
	mLCDNumber->setAutoFillBackground( true );

	QGridLayout* gridLayout = new QGridLayout( this );
	gridLayout->addWidget( mLCDNumber, 0 , 0);
	setLayout( gridLayout );

	mPrecision = 1;
	setValue( 0 );

	resize(150, 50);
}

NumericGauge::~NumericGauge()
{

}

void NumericGauge::saveSettings( QSettings& pSettings )
{
	pSettings.setValue("precision", precision());
}

void NumericGauge::loadSettings( QSettings& pSettings )
{
	setPrecision( pSettings.value("precision", 1).toInt() );
}

void NumericGauge::paintEvent( QPaintEvent *pEvent )
{
	QPainter painter( this );
	painter.setClipRegion( pEvent->region() );
	painter.setRenderHint( QPainter::Antialiasing, true );

	painter.save();
	drawFrame( &painter );
	painter.restore();
}

void NumericGauge::setValue( double pValue )
{
	AbstractGauge::setValue(pValue);
	QString str =  QString::number(value(), 'f', precision());
	mLCDNumber->setDigitCount( str.length() );
	mLCDNumber->display( str );
}

void NumericGauge::setPrecision( int pPrecision )
{
	mPrecision = pPrecision;
	setValue( value() );
}

void NumericGauge::drawFrame( QPainter *painter )
{
	const QRectF br(5, 5, width()-10, height()-10);
	QLinearGradient gradient( br.topLeft(), br.bottomRight() );
	gradient.setColorAt( 0.0, palette().color( QPalette::Light ) );
	gradient.setColorAt( 1.0, palette().color( QPalette::Dark ) );

	painter->setPen( QPen( gradient, borderWidth() ) );
	painter->setBrush( palette().brush( QPalette::Base ) );
	painter->drawRoundRect( br, 5, 5 );
}

QSize NumericGauge::sizeHint() const
{
	return QSize(150, 50);
}

