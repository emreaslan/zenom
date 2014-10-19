#include "VectorRotater.h"


VectorRotater::VectorRotater()
{
	isInitialized = false;
}

VectorRotater::VectorRotater(Vector3D& pLineBegin, Vector3D& pLineDir, double pDegree)
{
	setRotationValues(pLineBegin, pLineDir, pDegree);
}

void VectorRotater::setRotationValues(Vector3D& pLineBegin, Vector3D& pLineDir, double pDegree)
{
	double dirX2, dirY2, dirZ2, cosDegree, sinDegree, len2, len;

	dirX2 = pLineDir.X * pLineDir.X;
	dirY2 = pLineDir.Y * pLineDir.Y;
	dirZ2 = pLineDir.Z * pLineDir.Z;
	cosDegree = cos(pDegree);
	sinDegree = sin(pDegree);
	len2 = dirX2 + dirY2 + dirZ2;
	len =  sqrt(len2);

	if(len2 < 0.000000001) {
		printf("direction vector error!");
		return;            
	}
	isInitialized = true;

	m00 = (dirX2 + (dirY2 + dirZ2) * cosDegree)/len2;
	m01 = (pLineDir.X*pLineDir.Y * (1 - cosDegree) - pLineDir.Z*len*sinDegree)/len2;
	m02 = (pLineDir.X*pLineDir.Z * (1 - cosDegree) + pLineDir.Y*len*sinDegree)/len2;
	m03 = (pLineBegin.X*(dirY2 + dirZ2) - pLineDir.X*(pLineBegin.Y*pLineDir.Y + pLineBegin.Z*pLineDir.Z) 
		+ (pLineDir.X*(pLineBegin.Y*pLineDir.Y + pLineBegin.Z*pLineDir.Z) - pLineBegin.X*(dirY2 + dirZ2))*cosDegree + (pLineBegin.Y*pLineDir.Z - pLineBegin.Z*pLineDir.Y)*len*sinDegree)/len2;

	m10 = (pLineDir.X*pLineDir.Y * (1 - cosDegree) + pLineDir.Z*len*sinDegree)/len2;
	m11 = (dirY2 + (dirX2 + dirZ2) * cosDegree)/len2;
	m12 = (pLineDir.Y*pLineDir.Z * (1 - cosDegree) - pLineDir.X*len*sinDegree)/len2;
	m13 = (pLineBegin.Y*(dirX2 + dirZ2) - pLineDir.Y*(pLineBegin.X*pLineDir.X + pLineBegin.Z*pLineDir.Z) 
		+ (pLineDir.Y*(pLineBegin.X*pLineDir.X + pLineBegin.Z*pLineDir.Z) - pLineBegin.Y*(dirX2 + dirZ2))*cosDegree + (pLineBegin.Z*pLineDir.X - pLineBegin.X*pLineDir.Z)*len*sinDegree)/len2;

	m20 = (pLineDir.X*pLineDir.Z * (1 - cosDegree) - pLineDir.Y*len*sinDegree)/len2;
	m21 = (pLineDir.Y*pLineDir.Z * (1 - cosDegree) + pLineDir.X*len*sinDegree)/len2;
	m22 = (dirZ2 + (dirX2 + dirY2) * cosDegree)/len2;
	m23 = (pLineBegin.Z*(dirX2 + dirY2) - pLineDir.Z*(pLineBegin.X*pLineDir.X + pLineBegin.Y*pLineDir.Y) 
		+ (pLineDir.Z*(pLineBegin.X*pLineDir.X + pLineBegin.Y*pLineDir.Y) - pLineBegin.Z*(dirX2 + dirY2))*cosDegree + (pLineBegin.X*pLineDir.Y - pLineBegin.Y*pLineDir.X)*len*sinDegree)/len2;

}

Vector3D VectorRotater::rotate(Vector3D &pVec)
{
	if (!isInitialized)
	{
		printf("Vector rotater not initialized\n");
		return Vector3D();
	}
	Vector3D result;
	result.X = m00 * pVec.X + m01 * pVec.Y + m02 * pVec.Z + m03;
	result.Y = m10 * pVec.X + m11 * pVec.Y + m12 * pVec.Z + m13;
	result.Z = m20 * pVec.X + m21 * pVec.Y + m22 * pVec.Z + m23;
	return result;
}