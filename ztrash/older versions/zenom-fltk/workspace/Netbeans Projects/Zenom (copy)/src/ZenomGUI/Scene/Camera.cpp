#include "Camera.h"
using namespace std;


Camera::Camera(void)
{
	mIsArcCamera = true;
	setInitialParams(Vector3D(0, 0, 25), Vector3D(0, 0, 0), Vector3D(0, 1, 0));
}

Camera::Camera(const Vector3D &pEye,const Vector3D &pLook,const Vector3D &pUp)
{
	mIsArcCamera = true;
	setInitialParams(pEye, pLook, pUp);
}

void Camera::setInitialParams(const Vector3D &pEye, const Vector3D &pLook, const Vector3D &pUp)
{
	mEye = mInitialEye = pEye;
	mLook = mInitialLook = pLook;
	mUp = mInitialUp = pUp;
}


void Camera::gotoInitialPos()
{
	mEye = mInitialEye;
	mLook = mInitialLook;
	mUp = mInitialUp;
}

void Camera::render()
{
	gluLookAt(mEye.X, mEye.Y, mEye.Z,
		mLook.X, mLook.Y, mLook.Z,
		mUp.X, mUp.Y, mUp.Z);
}


void Camera::moveEyeUpDown(const double pAmount /* = 1 */)
{
	if (mIsArcCamera)
	{
		Vector3D circle = mEye - mLook;
		Vector3D perpVec;

		perpVec.X = circle.Z;
		perpVec.Z = -circle.X;

		mRotater.setRotationValues(Vector3D(), perpVec, -pAmount*PI/180);
		Vector3D temp = mRotater.rotate(circle);

		mEye = mLook + temp;
	}
	else
	{
		Vector3D circle = mLook - mEye;
		Vector3D perpVec;

		perpVec.X = circle.Z;
		perpVec.Z = -circle.X;

		mRotater.setRotationValues( Vector3D(), perpVec, pAmount*PI/180);
		Vector3D temp = mRotater.rotate(circle);

		mLook = mEye + temp;
	}

}

void Camera::moveEyeLeftRight(const double pAmount /* = 1 */)
{
	if (mIsArcCamera)
	{
		Vector3D circle = mEye - mLook;
		Vector3D perpVec;
		perpVec.Y = 1;

		mXRotater.setRotationValues(Vector3D(), perpVec, -pAmount*PI/180);
		Vector3D temp = mXRotater.rotate(circle);

		mEye = mLook + temp;
	}
	else
	{
		Vector3D circle = mLook - mEye;
		Vector3D perpVec;
		perpVec.Y = 1;

		mXRotater.setRotationValues( Vector3D(),perpVec, pAmount*PI/180);
		Vector3D temp = mXRotater.rotate(circle);

		mLook = mEye + temp;
	}
}


void Camera::zoomOut(const double pAmount /* = 1 */)
{
	Vector3D temp = mEye - mLook;
	mEye = mEye + (temp * (pAmount/10) );
}

void Camera::zoomIn(const double pAmount /* = 1 */)
{
	Vector3D temp = mEye - mLook;
	mEye = mEye - (temp * (pAmount/10));
}


void Camera::moveCameraFortBack(const double pAmount /* = 1 */)
{
	Vector3D temp = (mEye - mLook) * -pAmount;
	if (mIsArcCamera)
		temp.Y = 0;
	mEye = mEye + temp;
	mLook = mLook + temp;

}

void Camera::moveCameraUpDown(const double pAmount /* = 1 */)
{
	mEye.Y += pAmount;
	mLook.Y += pAmount;
}

void Camera::moveCameraLeftRight(const double pAmount /* = 1 */)
{
	Vector3D temp = (mEye - mLook) * pAmount;
	temp.Y = temp.Z;
	temp.Z = temp.X;
	temp.X = -temp.Y;
	temp.Y = 0;

	mEye = mEye + temp;
	mLook = mLook + temp;
}

void Camera::setIsArcCamera(bool pIsArc)
{
	mIsArcCamera = pIsArc;
}

void Camera::changeCameraType()
{
	mIsArcCamera = !mIsArcCamera;
}

void Camera::getKeyboardInput(const char pKey)
{
	switch(pKey)
	{
	case 'w':
		moveEyeUpDown(1);
		break;
	case 's':
		moveEyeUpDown(-1);
		break;
	case 'a':
		moveEyeLeftRight(1);
		break;
	case 'd':
		moveEyeLeftRight(-1);
		break;
	case '-':
		zoomOut();
		break;
	case '+':
		zoomIn();
		break;
	case '8':
		moveCameraFortBack(0.1);
		break;
	case '2':
		moveCameraFortBack(-0.1);
		break;
	case '4':
		moveCameraLeftRight(0.1);
		break;
	case '6':
		moveCameraLeftRight(-0.1);
		break;
	case '7':
		moveCameraUpDown(1);
		break;
	case '1':
		moveCameraUpDown(-1);
		break;
	case 'c':
	case 'C':
		changeCameraType();
		break;
	default:
		break;
	}
}