#pragma once

#include <iostream>
#include <math.h>
#include "Vector3D.h"


class VectorRotater
{
public:
	VectorRotater();
        VectorRotater(const Vector3D &pLineBegin, const Vector3D& pLineDir, const double pDegree);
	void setRotationValues(const Vector3D &pLineBegin, const Vector3D& pLineDir, const double pDegree);
	Vector3D rotate(const Vector3D &pVec);
	
private:
	bool isInitialized;
	double m00, m01, m02, m03; 
	double m10, m11, m12, m13; 
	double m20, m21, m22, m23;
};