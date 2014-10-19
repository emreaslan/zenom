#ifndef LINEARGAUGESETTING_H
#define LINEARGAUGESETTING_H

#include "abstractgaugesetting.h"
#include "ui_lineargaugesetting.h"

#include "lineargauge.h"

class LinearGaugeSetting : public AbstractGaugeSetting
{
	Q_OBJECT

public:
	LinearGaugeSetting(QWidget *pParent = 0);

	~LinearGaugeSetting();

	virtual AbstractGauge* createGauge(QWidget* pParent);

	virtual void initFrom( AbstractGauge* pGauge );

	virtual void initGauge( AbstractGauge* pGauge );

	virtual AbstractGaugeSetting* clone() { return new LinearGaugeSetting(); }

private slots:
	void orientationChangedSlot( int pIndex );
	void tickPositionChangedSlot( int pIndex );
	void captionPosChangedSlot(int pValue);
	void greenColorScaleChangedSlot(const QString& pValue);
	void yellowColorScaleChangedSlot(const QString& pValue);
	void redColorScaleChangedSlot(const QString& pValue);

private:
	void insertRemoveColorScale(AbstractGauge* pGauge, const QColor& pColor, const QString& pStart, const QString& pEnd);
	void updateTickPositionComboBox( Qt::Orientation pValue );

	Ui::LinearGaugeSetting ui;
	LinearGauge* mLinearGauge;
};

#endif // LINEARGAUGESETTING_H
