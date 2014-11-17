#ifndef SETPOINT_H
#define SETPOINT_H

#include "squarewavegenerator.h"
#include "ColumnVector.hpp"


/**
 * Generates Square Wave form.
 */
class SetPoint
{
public:
    SetPoint();

    void reset();

	ColumnVector<5> wd( double pTime, double pSamplingPeriod ); 

private:
	ColumnVector<5> linear_interpolator(ColumnVector<5>& final, 
		ColumnVector<5>& current, ColumnVector<5>& speed, double sample_time);

	ColumnVector<5> wd_0;
	ColumnVector<5> toSI;
	ColumnVector<5> v_lim;
	ColumnVector<5> current;

	SquareWaveGenerator squareWave_x;	
	SquareWaveGenerator squareWave_y;
	SquareWaveGenerator squareWave_z;
	SquareWaveGenerator squareWave_yaw;
	SquareWaveGenerator squareWave_roll;

};

#endif // SQUAREWAVEGENERATOR_H
