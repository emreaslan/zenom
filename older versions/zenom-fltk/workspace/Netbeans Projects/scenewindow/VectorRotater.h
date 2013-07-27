#ifndef _VECTOR_ROTATER_H
#define	_VECTOR_ROTATER_H

#include <iostream>
#include <math.h>
#include "Vector3D.h"


class VectorRotater
{
public:

    VectorRotater();
    VectorRotater(Vector3D& pLineBegin, Vector3D& pLineDir, double pDegree);
    void setRotationValues(Vector3D& pLineBegin, Vector3D& pLineDir, double pDegree);
    Vector3D rotate(Vector3D& pVec);
	
private:

    bool isInitialized;
    double m00, m01, m02, m03;
    double m10, m11, m12, m13;
    double m20, m21, m22, m23;
};

#endif