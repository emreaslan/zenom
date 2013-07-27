#ifndef LINEARGAUGE_H
#define LINEARGAUGE_H

#include "abstractgauge.h"
#include <QSlider>
#include "qslider.h"

class LinearGauge : public AbstractGauge
{
	Q_OBJECT

public:
	LinearGauge(QWidget *pParent = 0);

	~LinearGauge();

	virtual void saveSettings( QSettings& pSettings );

	virtual void loadSettings( QSettings& pSettings );

	virtual Type type() { return LINEAR; }

	Qt::Orientation	orientation () const { return mOrientation; }

	QSlider::TickPosition tickPosition () const { return mTickPosition; }

public slots:
	void setOrientation( Qt::Orientation pOrientation );

	void setTickPosition( QSlider::TickPosition pPosition );

protected:
	virtual QRectF boundingRect() const;

	virtual void paintEvent(QPaintEvent * pEvent);

	virtual void drawFrame( QPainter *painter );

	virtual void drawScale( QPainter *painter );

	virtual void drawNeedle( QPainter *painter );

	virtual void drawCaption( QPainter *painter );
	
	virtual void drawColorScale( QPainter *painter );

private:
	QRectF  mBar;
	QRectF mBoundingRect;
	Qt::Orientation mOrientation;
	QSlider::TickPosition mTickPosition;
};

#endif // LINEARGAUGE_H
