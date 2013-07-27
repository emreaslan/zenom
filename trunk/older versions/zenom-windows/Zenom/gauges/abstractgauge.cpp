#include "abstractgauge.h"

AbstractGauge::AbstractGauge(QWidget * pParent)
	: QWidget(pParent)
{
	QColor base = QColor( Qt::darkGray ).dark( 150 );
	QPalette palette;
	palette.setColor( QPalette::Base, base );
	palette.setColor( QPalette::Mid, base.dark( 110 ) );
	palette.setColor( QPalette::Light, base.light( 170 ) );
	palette.setColor( QPalette::Dark, base.dark( 170 ) );
	palette.setColor( QPalette::Text, base.dark( 200 ).light( 800 ) );
	palette.setColor( QPalette::WindowText, base.dark( 200 ) );
	setPalette(palette);

	// Scale
	zsetMajorTicks(6);
	setMajorTickLength( 8 );
	setMajorTickWidth( 2 );
	zsetMinorTicks(4);
	setMinorTickLength( 5 );
	setMinorTickWidth( 1 );

	setStartValue(0);
	setEndValue(100);	
	setValue(0);

	setBorderWidth( 4 );

	// Caption
	setCaption("%.2f");
	setCaptionXPos(0);
	setCaptionYPos(0);
}

AbstractGauge::~AbstractGauge()
{

}

void AbstractGauge::setValue( double pValue )
{
	mValue = pValue;
	update();
}

void AbstractGauge::calculateMaxLabelSize()
{
	mMaxLabelWidth = -1;
	double val;	
	for ( int i = 0; i < zmajorTicks(); ++i )
	{
		val = startValue() + i * (endValue() - startValue()) / (zmajorTicks() - 1);
		QSize size = fontMetrics().size( Qt::TextSingleLine, QString::number( val ) );
		if ( mMaxLabelWidth < size.width() )
		{
			mMaxLabelWidth = size.width();
		}		
	}
}

QRectF AbstractGauge::boundingRect() const
{
	return QRectF();
}

QRectF AbstractGauge::innerBoundingRect() const
{
	return boundingRect().adjusted( borderWidth(), borderWidth(), -borderWidth(), -borderWidth() );
}

void AbstractGauge::setStartValue( double pStartValue )
{
	mStartValue = pStartValue;
	calculateMaxLabelSize();
	update();
}

void AbstractGauge::setEndValue( double pEndValue )
{
	mEndValue = pEndValue;
	calculateMaxLabelSize();
	update();
}

void AbstractGauge::zsetMinorTicks( int pTicksCount )
{
	mMinorTicks = pTicksCount;
	update();
}

void AbstractGauge::zsetMajorTicks( int pTicksCount )
{
	mMajorTicks = pTicksCount;
	update();
}

void AbstractGauge::saveSettings( QSettings& pSettings )
{
	pSettings.setValue("maximum", endValue());
	pSettings.setValue("minimum", startValue());
	
	pSettings.setValue("majorTicks", zmajorTicks());
	pSettings.setValue("minorTicks", zminorTicks());

	pSettings.setValue("caption", caption());
	pSettings.setValue("captionXPos", captionXPos());
	pSettings.setValue("captionYPos", captionYPos());

	QList<ColorScale> colorScaleList = mColorScaleSet.values();
	pSettings.setValue("colorScaleSize", colorScaleList.size());
	for (int i = 0; i < colorScaleList.size(); ++i )
	{
		pSettings.setValue( QString("color") + QString::number(i), colorScaleList[i].color().rgb() );
		pSettings.setValue( QString("start") + QString::number(i), colorScaleList[i].start() );
		pSettings.setValue( QString("end") + QString::number(i), colorScaleList[i].end() );
	}
}

void AbstractGauge::loadSettings( QSettings& pSettings )
{
	setEndValue( pSettings.value("maximum", 100).toInt() );
	setStartValue( pSettings.value("minimum", 0).toInt() );
	zsetMajorTicks( pSettings.value("majorTicks", 6).toInt() );
	zsetMinorTicks( pSettings.value("minorTicks", 4).toInt() );
	
	setCaption( pSettings.value("caption", "").toString() );
	setCaptionXPos( pSettings.value("captionXPos", 0).toDouble() );
	setCaptionYPos( pSettings.value("captionYPos", 0).toDouble() );

	int colorScaleSize = pSettings.value("colorScaleSize", 0).toInt();
	for (int i = 0; i < colorScaleSize; ++i )
	{
		insertColorScale( pSettings.value( QString("color") + QString::number(i) ).toUInt(),
			pSettings.value( QString("start") + QString::number(i) ).toDouble(),
			pSettings.value( QString("end") + QString::number(i) ).toDouble() );
	}
}

void AbstractGauge::colorScaleSet( const QMap<QRgb, ColorScale>& val )
{
	mColorScaleSet = val;
	update();
}

ColorScale AbstractGauge::colorScale( const QColor& pColor )
{
	return mColorScaleSet.value( pColor.rgb() );
}

bool AbstractGauge::containsColorScale( const QColor& pColor )
{
	return mColorScaleSet.contains( pColor.rgb() );
}

void AbstractGauge::insertColorScale( const QColor& pColor, double pStart, double pEnd )
{
	mColorScaleSet.insert( pColor.rgb(), ColorScale(pColor, pStart, pEnd) );
	update();
}

void AbstractGauge::removeColorScale( const QColor& pColor )
{
	mColorScaleSet.remove( pColor.rgb() );
	update();
}

void AbstractGauge::clearColorScale()
{
	mColorScaleSet.clear();
	update();
}

double AbstractGauge::dvalue( double pVal )
{
	if ( endValue() > startValue() )
	{
		return qMax( qMin(pVal, endValue()), startValue() );
	} 
	else
	{
		return qMax( qMin(pVal, startValue()), endValue() );
	}	
}


