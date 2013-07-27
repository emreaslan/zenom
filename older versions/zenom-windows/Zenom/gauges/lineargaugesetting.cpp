#include "lineargaugesetting.h"

LinearGaugeSetting::LinearGaugeSetting(QWidget *pParent)
	: AbstractGaugeSetting(pParent)
{
	ui.setupUi(this);
	mGauge = mLinearGauge = new LinearGauge( ui.previewGroupBox );
	mGauge->move(10, 10);

	ui.orientation->clear();
	ui.orientation->addItem("Vertical", Qt::Vertical);
	ui.orientation->addItem("Horizontal", Qt::Horizontal);

	initFrom( mGauge );

	// Scale
	connect( ui.startRange, SIGNAL(valueChanged(double)), mGauge, SLOT(setStartValue(double)) );
	connect( ui.endRange, SIGNAL(valueChanged(double)), mGauge, SLOT(setEndValue(double)) );	
	connect( ui.majorTick, SIGNAL(valueChanged(int)), mGauge, SLOT(zsetMajorTicks(int)) );	
	connect( ui.minorTick, SIGNAL(valueChanged(int)), mGauge, SLOT(zsetMinorTicks(int)) );
	connect( ui.orientation, SIGNAL(currentIndexChanged(int)), SLOT(orientationChangedSlot(int)) );
	connect( ui.tickPosition, SIGNAL(currentIndexChanged(int)), SLOT(tickPositionChangedSlot(int)) );

	// Caption
	connect( ui.caption, SIGNAL(textChanged(const QString&)), mGauge, SLOT(setCaption(const QString&)) );
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

LinearGaugeSetting::~LinearGaugeSetting()
{

}

void LinearGaugeSetting::orientationChangedSlot( int pIndex )
{
	mLinearGauge->setOrientation( (Qt::Orientation)(ui.orientation->itemData( pIndex ).toInt()) ); 
	updateTickPositionComboBox( (Qt::Orientation)(ui.orientation->itemData( pIndex ).toInt()) );
	mLinearGauge->setTickPosition( (QSlider::TickPosition)(ui.tickPosition->itemData( ui.tickPosition->currentIndex() ).toInt()) ); 
}

void LinearGaugeSetting::tickPositionChangedSlot( int pIndex )
{
	mLinearGauge->setTickPosition( (QSlider::TickPosition)(ui.tickPosition->itemData( pIndex ).toInt()) ); 
}

void LinearGaugeSetting::captionPosChangedSlot(int pValue)
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

AbstractGauge* LinearGaugeSetting::createGauge( QWidget* pParent )
{
	LinearGauge* gauge = new LinearGauge( pParent );
	initGauge(gauge);
	return gauge;
}

void LinearGaugeSetting::initFrom( AbstractGauge* pGauge )
{
	LinearGauge* gauge = static_cast<LinearGauge*>( pGauge );

	// Scale
	ui.startRange->setValue( gauge->startValue() );
	ui.endRange->setValue( gauge->endValue() );
	ui.majorTick->setValue( gauge->zmajorTicks() );
	ui.minorTick->setValue( gauge->zminorTicks() );
	ui.orientation->setCurrentIndex( ui.orientation->findData( gauge->orientation() ) );
	updateTickPositionComboBox( gauge->orientation() );
	ui.tickPosition->setCurrentIndex( ui.tickPosition->findData( gauge->tickPosition() ) );

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

void LinearGaugeSetting::initGauge( AbstractGauge* pGauge )
{
	LinearGauge* gauge = static_cast<LinearGauge*>( pGauge );

	// Scale
	gauge->setStartValue( ui.startRange->value() );
	gauge->setEndValue( ui.endRange->value() );
	gauge->zsetMajorTicks( ui.majorTick->value() );
	gauge->zsetMinorTicks( ui.minorTick->value() );
	gauge->setOrientation( (Qt::Orientation)(ui.orientation->itemData( ui.orientation->currentIndex() ).toInt()) ); 
	gauge->setTickPosition( (QSlider::TickPosition)(ui.tickPosition->itemData( ui.tickPosition->currentIndex() ).toInt()) ); 

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

void LinearGaugeSetting::greenColorScaleChangedSlot( const QString& pValue )
{
	insertRemoveColorScale( mGauge, Qt::green, ui.greenStart->text(), ui.greenEnd->text() );
}

void LinearGaugeSetting::yellowColorScaleChangedSlot( const QString& pValue )
{
	insertRemoveColorScale( mGauge, Qt::yellow, ui.yellowStart->text(), ui.yellowEnd->text() );
}

void LinearGaugeSetting::redColorScaleChangedSlot( const QString& pValue )
{
	insertRemoveColorScale( mGauge, Qt::red, ui.redStart->text(), ui.redEnd->text() );
}

void LinearGaugeSetting::insertRemoveColorScale(AbstractGauge* pGauge, const QColor& pColor, const QString& pStart, const QString& pEnd )
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

void LinearGaugeSetting::updateTickPositionComboBox( Qt::Orientation pValue )
{
	// update tick position combo box
	ui.tickPosition->clear();
	if ( pValue == Qt::Horizontal )
	{
		ui.tickPosition->addItem("Above", QSlider::TicksAbove);
		ui.tickPosition->addItem("Below", QSlider::TicksBelow);
	} 
	else if ( pValue == Qt::Vertical )
	{
		ui.tickPosition->addItem("Left", QSlider::TicksLeft);
		ui.tickPosition->addItem("Right", QSlider::TicksRight);
	}	
}