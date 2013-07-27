#ifndef NUMERICGAUGE_H
#define NUMERICGAUGE_H

#include "abstractgauge.h"
#include <QLCDNumber>
#include <QPainter>
#include <QSizePolicy>


class NumericGauge : public AbstractGauge
{
	Q_OBJECT

public:
	NumericGauge(QWidget *pParent = 0);

	~NumericGauge();

	virtual void saveSettings( QSettings& pSettings );

	virtual void loadSettings( QSettings& pSettings );
	
	virtual void setValue( double pValue );

	int precision() { return mPrecision; }

	virtual Type type() { return NUMERIC; }

	virtual QSize sizeHint() const;

public slots:
	void setPrecision( int pPrecision );

protected:
	virtual void paintEvent(QPaintEvent * pEvent);

	virtual void drawFrame( QPainter *painter );

private:
	QLCDNumber* mLCDNumber;
	int mPrecision;	
};

#endif // NUMERICGAUGE_H
