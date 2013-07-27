#include "numericgaugesetting.h"

NumericGaugeSetting::NumericGaugeSetting(QWidget *parent)
	: AbstractGaugeSetting(parent)
{
	ui.setupUi(this);
	mGauge = mNumericGauge = new NumericGauge( ui.previewGroupBox );
	mGauge->move(35, 80);

	initFrom( mGauge );

	connect( ui.precision, SIGNAL(valueChanged(int)), mNumericGauge, SLOT(setPrecision(int)) );	
}

NumericGaugeSetting::~NumericGaugeSetting()
{

}

AbstractGauge* NumericGaugeSetting::createGauge( QWidget* pParent )
{
	NumericGauge* gauge = new NumericGauge( pParent );
	initGauge(gauge);
	return gauge;
}

void NumericGaugeSetting::initFrom( AbstractGauge* pGauge )
{
	NumericGauge* gauge = static_cast<NumericGauge*>( pGauge );
	ui.precision->setValue( gauge->precision() );
}

void NumericGaugeSetting::initGauge( AbstractGauge* pGauge )
{
	NumericGauge* gauge = static_cast<NumericGauge*>( pGauge );
	gauge->setPrecision( ui.precision->value() );
}
