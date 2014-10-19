#ifndef ABSTRACTGAUGESETTING_H
#define ABSTRACTGAUGESETTING_H

#include <QWidget>
#include "abstractgauge.h"

class AbstractGaugeSetting : public QWidget
{
	Q_OBJECT

public:
	AbstractGaugeSetting(QWidget *pParent = 0);

	~AbstractGaugeSetting();

	virtual AbstractGauge* createGauge(QWidget* pParent = NULL) = 0;

	virtual void initFrom( AbstractGauge* pGauge ) = 0;

	virtual void initGauge( AbstractGauge* pGauge ) = 0;
	
	virtual AbstractGaugeSetting* clone() = 0;

protected:
	AbstractGauge* mGauge;
};

#endif // ABSTRACTGAUGESETTING_H
