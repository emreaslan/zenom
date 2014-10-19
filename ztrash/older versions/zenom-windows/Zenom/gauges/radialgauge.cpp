#include "radialgauge.h"

RadialGauge::RadialGauge(QWidget *pParent)
	: AbstractGauge(pParent)
{
	resize(200, 200);
	setScaleArc(225, -45);
	setCaptionYPos(-0.35);

	insertColorScale( Qt::yellow, 70, 90 );
	insertColorScale( Qt::red, 90, 100 );
}

RadialGauge::~RadialGauge()
{

}

void RadialGauge::saveSettings( QSettings& pSettings )
{
	pSettings.setValue("mStartAngle", startScaleArc());
	pSettings.setValue("mEndAngle", endScaleArc());
	AbstractGauge::saveSettings(pSettings);
}

void RadialGauge::loadSettings( QSettings& pSettings )
{
	setStartScaleArc( pSettings.value("mStartAngle", 225.0).toDouble() );
	setEndScaleArc( pSettings.value("mEndAngle", -45.0).toDouble() );
	AbstractGauge::loadSettings( pSettings );
}

void RadialGauge::setScaleArc( double pStart, double pEnd )
{
	mStartAngle = pStart;
	mEndAngle = pEnd;
	update();
}

void RadialGauge::setStartScaleArc( double pStartAngle )
{
	mStartAngle = pStartAngle;
	update();
}

void RadialGauge::setEndScaleArc( double pEndAngle )
{
	mEndAngle = pEndAngle;
	update();
}

QSize RadialGauge::sizeHint() const
{
	return QSize(200, 200);
}

QRectF RadialGauge::boundingRect() const
{
	return QRectF(-190 / 2.0, -190 / 2.0, 190, 190);
}

void RadialGauge::paintEvent( QPaintEvent * pEvent )
{
	QPainter painter( this );
	painter.setClipRegion( pEvent->region() );
	painter.setRenderHint( QPainter::Antialiasing, true );
	
	int side = qMin(width(), height());
	painter.translate( width() / 2.0, height() / 2.0 );
	painter.scale(side / 200.0, side / 200.0);

	// draw background and frame
	painter.save();
	drawFrame( &painter );
	painter.restore();

	// draw caption
	painter.save();
	drawCaption( &painter );
	painter.restore();

	// draw scale
	painter.save();
	drawScale( &painter );
	painter.restore();
	
	// draw color scale
	painter.save();
	drawColorScale( &painter );
	painter.restore();

	// draw needle
	painter.save();
	drawNeedle( &painter );
	painter.restore();
}

void RadialGauge::drawFrame( QPainter *painter )
{
	const QRectF br = boundingRect();
	QLinearGradient gradient( br.topLeft(), br.bottomRight() );
	gradient.setColorAt( 0.0, palette().color( QPalette::Light ) );
	gradient.setColorAt( 1.0, palette().color( QPalette::Dark ) );

	painter->setPen( QPen( gradient, borderWidth() ) );
	painter->setBrush( palette().brush( QPalette::Base ) );
	painter->drawEllipse( br );	

	QRectF innerBr = innerBoundingRect();
	gradient.setStart( innerBr.bottomRight() );
	gradient.setFinalStop(innerBr.topLeft() );
				
	painter->setPen( QPen( gradient, borderWidth() ) );
	painter->setBrush( Qt::NoBrush );
	painter->drawEllipse( innerBr );
}

void RadialGauge::drawScale( QPainter *painter )
{
	const double textSpace = 5;
	const double r = radius();
	const double stepAngle = (mEndAngle - mStartAngle) / ticks();
	
	QPen pen(palette().color( QPalette::Text ));
	painter->setPen(pen);
	for (int i = 0; i <= ticks(); i++)
	{
		const double arc = (mStartAngle + i * stepAngle) * M_PI / 180.0;
		const double sinArc = qSin( arc );
		const double cosArc = qCos( arc );
		double len;

		if ( i % zminorTicks() )
		{
			pen.setWidth(minorTickWidth());
			len = minorTickLength();
		} 
		else
		{
			pen.setWidth(majorTickWidth());
			len = majorTickLength();

			// Draw Label
			QString val = QString("%1").arg(startValue() + i * (endValue() - startValue()) / ticks() );
			QSize labelSize = painter->fontMetrics().size(Qt::TextSingleLine, val);

			const double cxText = (textSpace + majorTickLength() + r + labelSize.width() / 2.0 ) * cosArc;
			const double cyText = -(textSpace + majorTickLength() + r + labelSize.height() / 2.0 ) * sinArc;

			const QRectF rect( cxText - labelSize.width() / 2, cyText - labelSize.height() / 2, labelSize.width(), labelSize.height() );
			painter->drawText( rect, val );
		}

		painter->setPen( pen );		

		const double x1 = r * cosArc;
		const double x2 = ( r + len ) * cosArc;
		const double y1 = - r * sinArc;
		const double y2 = - ( r + len ) * sinArc;

		painter->drawLine( QPointF(x1, y1), QPointF(x2, y2) );
	}	
}

void RadialGauge::drawColorScale( QPainter *painter )
{
	// Color Scale
	double barWidth = 4.0;

	const double r = radius();
	QRectF rec(-r, -r, 2 * r, 2 * r);
	rec.adjust( barWidth, barWidth, -barWidth, -barWidth);

	foreach (const ColorScale &colorScale, colorScaleSet())
	{
		painter->save();

		QPen pen( colorScale.color(), barWidth, Qt::SolidLine, Qt::FlatCap );
		painter->setPen( pen );
		painter->setBrush( Qt::NoBrush );

		const double stepAngle = (mEndAngle - mStartAngle) / (endValue() - startValue());
		double a = ( dvalue(colorScale.start()) - startValue() ) * stepAngle + mStartAngle;
		double b = ( dvalue(colorScale.end()) - startValue() ) * stepAngle + mStartAngle;

		int startAngle = a * 16;
		int spanAngle = (b-a) * 16;
		
		painter->drawArc( rec, startAngle, spanAngle);

		painter->restore();
	}
}

void RadialGauge::drawNeedle( QPainter *painter )
{
	double length = innerBoundingRect().width() / 2.0 - maxLabelWidth() - 10;
	
	QPainterPath path;
	path.moveTo( 0.0, 3.0 );
	path.lineTo( length, 0.6 );
	path.lineTo( length, -0.6 );
	path.lineTo( 0.0, -3.0 );
	path.closeSubpath();

	QRectF br = path.boundingRect();
	QColor needleColor( Qt::red );

	QLinearGradient gradient( br.topLeft(), br.bottomLeft() );
	gradient.setColorAt( 0.0, needleColor.light() );
	gradient.setColorAt( 0.5, needleColor.light() );
	gradient.setColorAt( 0.5001, needleColor.dark() );
	gradient.setColorAt( 1.0, needleColor.dark() );

	// draw needle	
	painter->save();
	painter->setPen( QPen( gradient, 1 ) );
	painter->setBrush( needleColor );
	const double stepAngle = (mEndAngle - mStartAngle) / (endValue() - startValue());
	painter->rotate( -((dvalue( value() ) - startValue()) * stepAngle + mStartAngle) );
	painter->drawPath( path );
	painter->restore();

	double needleRadius = 8;
	QRectF needleCircle(-needleRadius, -needleRadius, 2*needleRadius, 2*needleRadius);

	QLinearGradient gradient1( needleCircle.topLeft(), needleCircle.bottomRight() );
	gradient1.setColorAt( 0.0, palette().color( QPalette::Light ) );
	gradient1.setColorAt( 1.0, palette().color( QPalette::Dark ) );

	painter->setPen(  QPen( gradient1, 2 ) );
	painter->setBrush( palette().color( QPalette::Base ) );	
	painter->drawEllipse(needleCircle);
}

void RadialGauge::drawCaption( QPainter *painter )
{
	QRectF innerBr = innerBoundingRect();
	QString text;
	text.sprintf( caption().toStdString().c_str(), value() );

	QSize labelSize = painter->fontMetrics().size(Qt::TextSingleLine, text);
	double x = innerBr.width() / 2.0 * captionXPos() + innerBr.center().x() - labelSize.width() / 2.0;
	double y = innerBr.height() / 2.0 * captionYPos() + innerBr.center().y() + labelSize.height() / 2.0;
	
	painter->save();
	painter->setPen(  Qt::white );
	painter->drawText( x, y, text );
	painter->restore();
}

double RadialGauge::radius()
{
	double textSpace = 5;
	double radius = innerBoundingRect().width() / 2.0 - maxLabelWidth() - textSpace - majorTickLength() - 5;
	return radius;
}