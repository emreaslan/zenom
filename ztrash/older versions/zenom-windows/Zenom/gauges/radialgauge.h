#ifndef RADIALGAUGE_H
#define RADIALGAUGE_H

#include "abstractgauge.h"

class RadialGauge : public AbstractGauge
{
	Q_OBJECT

public:
	RadialGauge(QWidget *pParent = 0);

	~RadialGauge();

	virtual void saveSettings( QSettings& pSettings );

	virtual void loadSettings( QSettings& pSettings );

	void setScaleArc(double pStart, double pEnd);

	double startScaleArc() { return mStartAngle; }

	double endScaleArc() { return mEndAngle; }
	
	virtual Type type() { return RADIAL; }

	virtual QSize sizeHint() const;

public slots:
	void setStartScaleArc(double pStartAngle);

	void setEndScaleArc(double pEndAngle);

protected:
	virtual QRectF boundingRect() const;

	virtual void paintEvent(QPaintEvent * pEvent);

	virtual void drawFrame( QPainter *painter );

	virtual void drawScale( QPainter *painter );
	
	virtual void drawNeedle( QPainter *painter );

	virtual void drawCaption( QPainter *painter );

	virtual void drawColorScale( QPainter *painter );

	double radius();

private:
	double mStartAngle;
	double mEndAngle;		
};

#endif // RADIALGAUGE_H
