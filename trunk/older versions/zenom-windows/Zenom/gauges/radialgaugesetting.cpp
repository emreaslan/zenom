#include "radialgaugesetting.h"

RadialGaugeSetting::RadialGaugeSetting(QWidget *parent)
	: AbstractGaugeSetting(parent)
{
	ui.setupUi(this);
	mGauge = mRadialGauge = new RadialGauge( ui.previewGroupBox );
	mRadialGauge->move(10, 10);

	initFrom( mGauge );

	// Scale
	connect( ui.startRange, SIGNAL(valueChanged(double)), mRadialGauge, SLOT(setStartValue(double)) );
	connect( ui.endRange, SIGNAL(valueChanged(double)), mRadialGauge, SLOT(setEndValue(double)) );	
	connect( ui.majorTick, SIGNAL(valueChanged(int)), mRadialGauge, SLOT(zsetMajorTicks(int)) );	
	connect( ui.minorTick, SIGNAL(valueChanged(int)), mRadialGauge, SLOT(zsetMinorTicks(int)) );	
	connect( ui.startAngle, SIGNAL(valueChanged(double)), mRadialGauge, SLOT(setStartScaleArc(double)) );	
	connect( ui.endAngle, SIGNAL(valueChanged(double)), mRadialGauge, SLOT(setEndScaleArc(double)) );

	// Caption
	connect( ui.caption, SIGNAL(textChanged(const QString&)), mRadialGauge, SLOT(setCaption(const QString&)) );
	connect( ui.captionXPos, SIGNAL(valueChanged(int)), SLOT(captionPosChangedSlot(int)) );
	connect( ui.captionYPos, SIGNAL(valueChanged(int)), SLOT(captionPosChangedSlot(int)) );

	// Color Scale
	connect( ui.greenStart, SIGNAL(textChanged(const QString&)), SLOT(greenColorScaleChangedSlot(const QString&)) );
	connect( ui.greenEnd, SIGNAL(textChanged(const QString&)), SLOT(greenColorScaleChangedSlot(const QString&)) );
	
	connect( ui.yellowStart, SIGNAL(textChanged(const QString&)), SLOT(yellowColorScaleChangedSlot(const QString&)) );
	connect( ui.yellowEnd, SIGNAL(textChanged(const QString&)), SLOT(yellowColorScaleChangedSlot(const QString&)) );
	
	connect( ui.redStart, SIGNAL(textChanged(const QString&)), SLOT(redColorScaleChangedSlot(const QString&)) );
	connect( ui.redEnd, SIGNAL(textChanged(const QString&)), SLOT(redColorScaleChangedSlot(const QString&)) );
}

RadialGaugeSetting::~RadialGaugeSetting()
{

}

void RadialGaugeSetting::captionPosChangedSlot(int pValue)
{
	QObject* slider = sender();
	if ( slider == ui.captionXPos )
	{
		mGauge->setCaptionXPos( pValue / 100.0 );
	}
	else if ( slider == ui.captionYPos )
	{
		mGauge->setCaptionYPos( pValue / 100.0 );
	}
}

AbstractGauge* RadialGaugeSetting::createGauge( QWidget* pParent )
{
	RadialGauge* gauge = new RadialGauge( pParent );
	initGauge(gauge);
	return gauge;
}

void RadialGaugeSetting::initFrom( AbstractGauge* pGauge )
{
	RadialGauge* gauge = static_cast<RadialGauge*>( pGauge );

	// Scale
	ui.startRange->setValue( gauge->startValue() );
	ui.endRange->setValue( gauge->endValue() );
	ui.majorTick->setValue( gauge->zmajorTicks() );
	ui.minorTick->setValue( gauge->zminorTicks() );
	ui.startAngle->setValue( gauge->startScaleArc() );
	ui.endAngle->setValue( gauge->endScaleArc() );

	// Caption
	ui.caption->setText( gauge->caption() );
	ui.captionXPos->setValue( gauge->captionXPos() * 100 );
	ui.captionYPos->setValue( gauge->captionYPos() * 100 );
	
	// Color Scale
	foreach (const ColorScale &colorScale, gauge->colorScaleSet()  )
	{
		if ( colorScale.color() == Qt::green )
		{
			ui.greenStart->setText( QString::number( colorScale.start() ) );
			ui.greenEnd->setText( QString::number( colorScale.end() ) );
		}
		else if ( colorScale.color() == Qt::yellow )
		{
			ui.yellowStart->setText( QString::number( colorScale.start() ) );
			ui.yellowEnd->setText( QString::number( colorScale.end() ) );
		}
		else if ( colorScale.color() == Qt::red )
		{
			ui.redStart->setText( QString::number( colorScale.start() ) );
			ui.redEnd->setText( QString::number( colorScale.end() ) );
		}
	}
}

void RadialGaugeSetting::initGauge( AbstractGauge* pGauge )
{
	RadialGauge* gauge = static_cast<RadialGauge*>( pGauge );

	// Scale
	gauge->setStartValue( ui.startRange->value() );
	gauge->setEndValue( ui.endRange->value() );
	gauge->zsetMajorTicks( ui.majorTick->value() );
	gauge->zsetMinorTicks( ui.minorTick->value() );
	gauge->setStartScaleArc( ui.startAngle->value() );
	gauge->setEndScaleArc( ui.endAngle->value() );

	// Caption
	gauge->setCaption( ui.caption->text() );
	gauge->setCaptionXPos( ui.captionXPos->value() / 100.0 );
	gauge->setCaptionYPos( ui.captionYPos->value() / 100.0 );

	// Color Scale
	gauge->clearColorScale();
	insertRemoveColorScale( gauge, Qt::green, ui.greenStart->text(), ui.greenEnd->text() );
	insertRemoveColorScale( gauge, Qt::yellow, ui.yellowStart->text(), ui.yellowEnd->text() );
	insertRemoveColorScale( gauge, Qt::red, ui.redStart->text(), ui.redEnd->text() );
}

void RadialGaugeSetting::greenColorScaleChangedSlot( const QString& pValue )
{
	insertRemoveColorScale( mGauge, Qt::green, ui.greenStart->text(), ui.greenEnd->text() );
}

void RadialGaugeSetting::yellowColorScaleChangedSlot( const QString& pValue )
{
	insertRemoveColorScale( mGauge, Qt::yellow, ui.yellowStart->text(), ui.yellowEnd->text() );
}

void RadialGaugeSetting::redColorScaleChangedSlot( const QString& pValue )
{
	insertRemoveColorScale( mGauge, Qt::red, ui.redStart->text(), ui.redEnd->text() );
}

void RadialGaugeSetting::insertRemoveColorScale(AbstractGauge* pGauge, const QColor& pColor, const QString& pStart, const QString& pEnd )
{
	bool validStart, validEnd;
	double start, end;

	start = pStart.toDouble( &validStart );
	end = pEnd.toDouble( &validEnd );

	if ( validStart && validEnd )
	{
		pGauge->insertColorScale( pColor, start, end );
	} 
	else
	{
		pGauge->removeColorScale( pColor );
	}
}