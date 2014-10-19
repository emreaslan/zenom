#ifndef ABSTRACTGAUGE_H
#define ABSTRACTGAUGE_H

#include <QWidget>
#include <QString>
#include <QFont>
#include <QPainter>
#include <QPaintEvent>
#include <qmath.h>
#include <QSettings>
#include "colorscale.h"

class AbstractGauge : public QWidget
{
	Q_OBJECT

public:
	AbstractGauge(QWidget * pParent = 0);
	virtual ~AbstractGauge();

	double value() { return mValue; }
	virtual void setValue( double pValue );

	// Scale
	double startValue() { return mStartValue; }
	double endValue() { return mEndValue; }

	// Ticks
	int ticks() { return (zmajorTicks() - 1) * zminorTicks(); } 

	// Major Tick
	int zmajorTicks() { return mMajorTicks; }

	double majorTickLength() const { return mMajorTickLength; }
	void setMajorTickLength(double val) { mMajorTickLength = val; }

	double majorTickWidth() const { return mMajorTickWidth; }
	void setMajorTickWidth(double val) { mMajorTickWidth = val; }

	// Minor Tick
	int zminorTicks() { return mMinorTicks; }	

	double minorTickLength() const { return mMinorTickLength; }
	void setMinorTickLength(double val) { mMinorTickLength = val; }

	double minorTickWidth() const { return mMinorTickWidth; }
	void setMinorTickWidth(double val) { mMinorTickWidth = val; }

	// Caption
	QString caption() { return mCaption; }
	double captionXPos() const { return mCaptionXPos; }
	double captionYPos() const { return mCaptionYPos; }

	// Color Scale
	QMap<QRgb, ColorScale> colorScaleSet() { return mColorScaleSet; }
	void colorScaleSet(const QMap<QRgb, ColorScale>& val);
	ColorScale colorScale( const QColor& pColor );
	bool containsColorScale( const QColor& pColor );
	void insertColorScale( const QColor& pColor, double pStart, double pEnd );
	void removeColorScale( const QColor& pColor );
	void clearColorScale();

	enum Type
	{
		RADIAL = 0,
		LINEAR,
		NUMERIC
	};
	
	virtual void saveSettings( QSettings& pSettings );

	virtual void loadSettings( QSettings& pSettings );

	virtual Type type() = 0;

public slots:
	// Scale
	void setStartValue( double pStartValue );
	void setEndValue( double pEndValue );

	void zsetMinorTicks( int pTicksCount );
	void zsetMajorTicks( int pTicksCount );

	//  Caption
	void setCaption(const QString &pCaption) { mCaption = pCaption; update(); }	
	void setCaptionXPos(double val) { mCaptionXPos = val; update(); }	// Beetween -1.0 and 1.0
	void setCaptionYPos(double val) { mCaptionYPos = val; update(); }	// Beetween -1.0 and 1.0

protected:
	double maxLabelWidth() { return mMaxLabelWidth; }
	void calculateMaxLabelSize();

	double dvalue( double pVal );

	virtual QRectF boundingRect() const;

	QRectF innerBoundingRect() const;

	double borderWidth() const { return mBorderWidth; }
	void setBorderWidth(double val) { mBorderWidth = val; }
	
private:
	double mValue;

	// Scale options
	int mStartValue;
	int mEndValue;

	int mMajorTicks;
	double mMajorTickLength;
	double mMajorTickWidth;

	int mMinorTicks;
	double mMinorTickLength;
	double mMinorTickWidth;
		
	// Caption
	QString mCaption;
	double mCaptionXPos;
	double mCaptionYPos;

	// Color Scale
	QMap<QRgb, ColorScale> mColorScaleSet;

	// Border
	double mBorderWidth;

	// Maximum label width
	double mMaxLabelWidth;
};

#endif // ABSTRACTGAUGE_H
