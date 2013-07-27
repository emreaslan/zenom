#ifndef NUMERICGAUGESETTING_H
#define NUMERICGAUGESETTING_H

#include "abstractgaugesetting.h"
#include "ui_numericgaugesetting.h"

#include "numericgauge.h"

class NumericGaugeSetting : public AbstractGaugeSetting
{
	Q_OBJECT

public:
	NumericGaugeSetting(QWidget *parent = 0);

	~NumericGaugeSetting();

	virtual AbstractGauge* createGauge(QWidget* pParent);

	virtual void initFrom( AbstractGauge* pGauge );

	virtual void initGauge( AbstractGauge* pGauge );

	virtual AbstractGaugeSetting* clone() { return new NumericGaugeSetting(); }

private:
	Ui::NumericGaugeSetting ui;
	NumericGauge* mNumericGauge;
};

#endif // NUMERICGAUGESETTING_H
