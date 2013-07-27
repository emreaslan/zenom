#include "Vector3D.h"


Vector3D::Vector3D()
{
	X = Y = Z = 0;
}

Vector3D::Vector3D(const double pX, const double pY, const double pZ)
{
	X = pX; Y = pY; Z = pZ; 
}


Vector3D::~Vector3D()
{
}

Vector3D Vector3D::add(const Vector3D &pLeft)
{
	Vector3D temp = *this;
	temp.X += pLeft.X;
	temp.Y += pLeft.Y;
	temp.Z += pLeft.Z;
	return temp;
}

Vector3D Vector3D::subtraction(const Vector3D &pLeft)
{
	Vector3D temp = *this;
	temp.X -= pLeft.X;
	temp.Y -= pLeft.Y;
	temp.Z -= pLeft.Z;
	return temp;
}

double Vector3D::length()
{
	return sqrt(X*X + Y*Y + Z*Z);
}

Vector3D Vector3D::normalize()
{
	Vector3D temp = *this;
	double len = length();
	temp.X = X / len;
	temp.Y = Y / len;
	temp.Z = Z / len;
	return temp;
}

Vector3D Vector3D::multiply(const double pMul)
{
	Vector3D temp = *this;
	temp.X = X * pMul;
	temp.Y = Y * pMul;
	temp.Z = Z * pMul;
	return temp;
}

Vector3D Vector3D::cross(const Vector3D &pLeft)
{
	Vector3D temp;
	temp.X = Y*pLeft.Z - Z*pLeft.Y;
	temp.Y = Z*pLeft.X - X*pLeft.Z;
	temp.Z = X*pLeft.Y - Y*pLeft.X;
	return temp;
}

double Vector3D::dot(const Vector3D &pLeft)
{
	return X*pLeft.X + Y*pLeft.Y + Z*pLeft.Z;
}

Vector3D Vector3D::operator+(const Vector3D& pLeft)
{
	return add(pLeft);
}

Vector3D Vector3D::operator-(const Vector3D& pLeft)
{
	return subtraction(pLeft);
}

Vector3D Vector3D::operator*(const double p)
{
	return multiply(p);
}

bool Vector3D::operator==(const Vector3D& pLeft)
{
    if (X != pLeft.X)
        return false;
    if (Y != pLeft.Y)
        return false;
    if (Z !=  pLeft.Z)
        return false;
    return true;
}

bool Vector3D::operator!=(const Vector3D& pLeft)
{
    return !(*this == pLeft);
}