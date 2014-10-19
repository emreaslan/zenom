#ifndef RADIALGAUGESETTING_H
#define RADIALGAUGESETTING_H

#include "abstractgaugesetting.h"
#include "ui_radialgaugesetting.h"

#include "radialgauge.h"

class RadialGaugeSetting : public AbstractGaugeSetting
{
	Q_OBJECT

public:
	RadialGaugeSetting(QWidget *parent = 0);
	~RadialGaugeSetting();

	virtual AbstractGauge* createGauge(QWidget* pParent);

	virtual void initFrom( AbstractGauge* pGauge );

	virtual void initGauge( AbstractGauge* pGauge );

	virtual AbstractGaugeSetting* clone() { return new RadialGaugeSetting(); }

private slots:
	void captionPosChangedSlot(int pValue);
	void greenColorScaleChangedSlot(const QString& pValue);
	void yellowColorScaleChangedSlot(const QString& pValue);
	void redColorScaleChangedSlot(const QString& pValue);

private:
	void insertRemoveColorScale(AbstractGauge* pGauge, const QColor& pColor, const QString& pStart, const QString& pEnd);

	Ui::RadialGaugeSetting ui;
	RadialGauge* mRadialGauge;
};

#endif // RADIALGAUGESETTING_H
