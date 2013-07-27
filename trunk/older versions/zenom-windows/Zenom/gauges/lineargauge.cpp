#include "lineargauge.h"

LinearGauge::LinearGauge(QWidget *pParent)
	: AbstractGauge(pParent)
{
	resize(200, 200);	

	insertColorScale( Qt::green, 0, 70 );
	insertColorScale( Qt::yellow, 70, 90 );
	insertColorScale( Qt::red, 90, 100 );

	setOrientation( Qt::Vertical );
	setTickPosition( QSlider::TicksLeft );
}

LinearGauge::~LinearGauge()
{
	
}

void LinearGauge::saveSettings( QSettings& pSettings )
{
	pSettings.setValue("orientation", orientation());
	pSettings.setValue("tickPosition", tickPosition());
	AbstractGauge::saveSettings(pSettings);
}

void LinearGauge::loadSettings( QSettings& pSettings )
{
	setOrientation( (Qt::Orientation)(pSettings.value("orientation", Qt::Vertical).toInt()) );
	setTickPosition( (QSlider::TickPosition)(pSettings.value("tickPosition", QSlider::TicksLeft).toInt()) );
	AbstractGauge::loadSettings( pSettings );
}

void LinearGauge::setOrientation( Qt::Orientation pOrientation )
{
	mOrientation = pOrientation;
	if ( pOrientation == Qt::Vertical )
	{
		mBoundingRect = QRectF(-90 / 2.0, -190 / 2.0, 90, 190);
		mBar = mBoundingRect.adjusted( 15, 30, -15, -30 );
		
	} 
	else if ( pOrientation == Qt::Horizontal )
	{
		mBoundingRect = QRectF(-190 / 2.0, -90 / 2.0, 190, 90);
		mBar = mBoundingRect.adjusted( 30, 15, -30, -15 );
	}
	
	update();
}

void LinearGauge::setTickPosition( QSlider::TickPosition pPosition )
{
	mTickPosition = pPosition;
	update();
}

QRectF LinearGauge::boundingRect() const
{
	return mBoundingRect;
}

void LinearGauge::paintEvent( QPaintEvent * pEvent )
{
	QPainter painter( this );
	painter.setClipRegion( pEvent->region() );
	painter.setRenderHint( QPainter::Antialiasing, true );

	int side = mOrientation == Qt::Vertical ? qMin(width()*2, height()) : qMin(width(), height()*2);
	painter.translate( width() / 2.0, height() / 2.0 );
	painter.scale(side / 200.0, side / 200.0);

	painter.save();
	drawFrame( &painter );
	painter.restore();

	painter.save();
	drawCaption( &painter );
	painter.restore();

	// draw color scale
	painter.save();
	drawColorScale( &painter );
	painter.restore();

	painter.save();
	drawScale( &painter );
	painter.restore();

	painter.save();
	drawNeedle( &painter );
	painter.restore();
}

void LinearGauge::drawFrame( QPainter *painter )
{
	const QRectF br = boundingRect();
	QLinearGradient gradient( br.topLeft(), br.bottomRight() );
	gradient.setColorAt( 0.0, palette().color( QPalette::Light ) );
	gradient.setColorAt( 1.0, palette().color( QPalette::Dark ) );

	painter->setPen( QPen( gradient, borderWidth() ) );
	painter->setBrush( palette().brush( QPalette::Base ) );
	painter->drawRoundRect( br, 10, 10 );	

	QRectF innerBr = innerBoundingRect();
	gradient.setStart( innerBr.bottomRight() );
	gradient.setFinalStop(innerBr.topLeft() );

	painter->setPen( QPen( gradient, borderWidth() ) );
	painter->setBrush( Qt::NoBrush );
	painter->drawRoundRect( innerBr, 10, 10 );	
}

void LinearGauge::drawScale( QPainter *painter )
{
	QPen pen(palette().color( QPalette::Text ), 0, Qt::SolidLine, Qt::FlatCap );
	painter->setPen(pen);
		
	double len;
	for (int i = 0; i <= ticks(); i++)
	{

		if ( i % zminorTicks() )
		{
			pen.setWidth(minorTickWidth());
			len = minorTickLength();
		} 
		else
		{
			pen.setWidth(majorTickWidth());
			len = majorTickLength();
		}
		painter->setPen( pen );

		QString val = QString("%1").arg(startValue() + i * (endValue() - startValue()) / ticks() );
		QSize labelSize = painter->fontMetrics().size(Qt::TextSingleLine, val);

		double x1, y1, x2, y2;
		double xTextPos, yTextPos;
		if ( mOrientation == Qt::Vertical )
		{
			const double step = mBar.height() / ticks();
			if ( mTickPosition == QSlider::TicksRight )
			{
				x1 = mBar.right() - 8;
				y1 = y2 = mBar.bottom() - i * step;
				x2 = x1 - len;
				xTextPos = x2 - 5 - labelSize.width();
				yTextPos = y1 - labelSize.height()/2.0;
			} 
			else
			{
				x1 = mBar.left() + 8;
				y1 = y2 = mBar.bottom() - i * step;
				x2 = x1 + len;
				xTextPos = x2 + 5;
				yTextPos = y1 - labelSize.height()/2.0;
			}			
		}
		else
		{
			const double step = mBar.width() / ticks();
			if ( mTickPosition == QSlider::TicksAbove )
			{
				x1 = x2 = mBar.left() + i * step;
				y1 = mBar.top() + 8;
				y2 = y1 + len;
				xTextPos = x1 - labelSize.width()/2.0;
				yTextPos = y1 + len;				
			} 
			else
			{
				x1 = x2 = mBar.left() + i * step;
				y1 = mBar.bottom() - 8;
				y2 = y1 - len;
				xTextPos = x1 - labelSize.width()/2.0;
				yTextPos = y1 - len - 15;
			}
		}

		// Draw Line		
		painter->drawLine( x1, y1, x2, y2 );

		// Draw Label
		if ( !(i % zminorTicks()) )
		{			
			painter->drawText( QRectF(xTextPos, yTextPos, labelSize.width(), labelSize.height() ), val );
		} 
	}
}

void LinearGauge::drawNeedle( QPainter *painter )
{
	double length = 30;

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
	if ( mOrientation == Qt::Vertical )
	{
		const double h = ( dvalue(value()) - startValue()) / (endValue() - startValue()) * mBar.height();
		if ( mTickPosition == QSlider::TicksRight )
		{
			painter->translate(mBar.right() + 10, mBar.bottom() - h );
			painter->rotate(180);
		} 
		else
		{
			painter->translate(mBar.left() - 10, mBar.bottom() - h );			
		}		
	}
	else
	{
		const double h = ( dvalue(value()) - startValue()) / (endValue() - startValue()) * mBar.width();
		if ( mTickPosition == QSlider::TicksAbove )
		{
			painter->translate(mBar.left() + h, mBar.top() - 10);
			painter->rotate(180);
		} 
		else
		{
			painter->translate(mBar.left() + h, mBar.bottom() + 10);
		}		
		painter->rotate(-90);
	}

	painter->drawPath( path );
	painter->restore();
}

void LinearGauge::drawCaption( QPainter *painter )
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

void LinearGauge::drawColorScale( QPainter *painter )
{
	// Color Scale
	double barWidth = 4.0;
	foreach (const ColorScale &colorScale, colorScaleSet())
	{
		painter->save();

		painter->setPen( Qt::NoPen );
		painter->setBrush( colorScale.color() );

		if ( mOrientation == Qt::Vertical )
		{
			const double h1 = (dvalue(colorScale.start()) - startValue()) / (endValue() - startValue()) * mBar.height();
			const double h2 = (dvalue(colorScale.end()) - startValue()) / (endValue() - startValue()) * mBar.height();

			if ( mTickPosition == QSlider::TicksRight )
			{
				painter->drawRect( mBar.right() - barWidth, mBar.bottom() - h1, barWidth, -h2 + h1 );
			} 
			else
			{
				painter->drawRect( mBar.left(), mBar.bottom() - h1, barWidth, -h2 + h1 );
			}			
		}
		else
		{
			const double h1 = (dvalue(colorScale.start()) - startValue()) / (endValue() - startValue()) * mBar.width();
			const double h2 = (dvalue(colorScale.end()) - startValue()) / (endValue() - startValue()) * mBar.width();

			if ( mTickPosition == QSlider::TicksAbove )
			{
				painter->drawRect( mBar.left() + h1, mBar.top(), h2 - h1, barWidth );
			} 
			else
			{
				painter->drawRect( mBar.left() + h1, mBar.bottom() - barWidth, h2 - h1, barWidth );
			}			
		}
		painter->restore();
	}
}
