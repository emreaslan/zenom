#include "Camera.h"
using namespace std;




GLCamera::GLCamera(void)
{
	mIsArcCamera = false;
	setInitialParams(Vector3D(0, 0, 25), Vector3D(0, 0, 0), Vector3D(0, 1, 0));
}

GLCamera::GLCamera(const Vector3D &pEye,const Vector3D &pLook,const Vector3D &pUp)
{
	mIsArcCamera = false;
	setInitialParams(pEye, pLook, pUp);
}

void GLCamera::setInitialParams(const Vector3D &pEye, const Vector3D &pLook, const Vector3D &pUp)
{
	mEye = mInitialEye = pEye;
	mLook = mInitialLook = pLook;
	mUp = mInitialUp = pUp;
}


void GLCamera::gotoInitialPos()
{
	mEye = mInitialEye;
	mLook = mInitialLook;
	mUp = mInitialUp;
}

void GLCamera::render()
{
    if (preEye != mEye || preLook != mLook  || preUp != mUp)
        printf("Eye : %f - %f - %f\nLook : %f - %f - %f\nUp : %f - %f - %f\n\n",
                mEye.X, mEye.Y, mEye.Z, mLook.X, mLook.Y, mLook.Z, mUp.X, mUp.Y, mUp.Z);
	gluLookAt(mEye.X, mEye.Y, mEye.Z,
		mLook.X, mLook.Y, mLook.Z,
		mUp.X, mUp.Y, mUp.Z);
}


void GLCamera::moveEyeUpDown(const double pAmount /* = 1 */)
{
	if (mIsArcCamera)
	{
		Vector3D circle = mEye - mLook;
		Vector3D perpVec;

		perpVec.X = circle.Z;
		perpVec.Z = -circle.X;

                Vector3D temp;
		mRotater.setRotationValues(temp, perpVec, -pAmount*PI/180);
		temp = mRotater.rotate(circle);

		mEye = mLook + temp;
	}
	else
	{
		Vector3D circle = mLook - mEye;
		Vector3D perpVec;

		perpVec.X = circle.Z;
		perpVec.Z = -circle.X;

                Vector3D temp;
		mRotater.setRotationValues(temp, perpVec, pAmount*PI/180);
		temp = mRotater.rotate(circle);

		mLook = mEye + temp;
	}

}

void GLCamera::moveEyeLeftRight(const double pAmount /* = 1 */)
{
	if (mIsArcCamera)
	{
		Vector3D circle = mEye - mLook;
		Vector3D perpVec;
		perpVec.Y = 1;

                Vector3D temp;
		mXRotater.setRotationValues(temp, perpVec, -pAmount*PI/180);
		temp = mXRotater.rotate(circle);

		mEye = mLook + temp;
	}
	else
	{
		Vector3D circle = mLook - mEye;
		Vector3D perpVec;
		perpVec.Y = 1;

                Vector3D temp;
		mXRotater.setRotationValues(temp,perpVec, pAmount*PI/180);
		temp = mXRotater.rotate(circle);

		mLook = mEye + temp;
	}
}


void GLCamera::zoomOut(const double pAmount /* = 1 */)
{
	//Vector3D temp = mEye - mLook;
	//mEye = mEye + (temp * (pAmount/10) );
}

void GLCamera::zoomIn(const double pAmount /* = 1 */)
{
	//Vector3D temp = mEye - mLook;
	//mEye = mEye - (temp * (pAmount/10));
}


void GLCamera::moveCameraFortBack(const double pAmount /* = 1 */)
{
	Vector3D temp = (mEye - mLook) * -pAmount;
	if (mIsArcCamera)
		temp.Y = 0;
	mEye = mEye + temp;
	mLook = mLook + temp;

}

void GLCamera::moveCameraUpDown(const double pAmount /* = 1 */)
{
	mEye.Y += pAmount;
	mLook.Y += pAmount;
}

void GLCamera::moveCameraLeftRight(const double pAmount /* = 1 */)
{
	Vector3D temp = (mEye - mLook) * pAmount;
	temp.Y = temp.Z;
	temp.Z = temp.X;
	temp.X = -temp.Y;
	temp.Y = 0;

	mEye = mEye + temp;
	mLook = mLook + temp;
}

void GLCamera::setIsArcCamera(bool pIsArc)
{
	mIsArcCamera = pIsArc;
}

void GLCamera::changeCameraType()
{
	mIsArcCamera = !mIsArcCamera;
}

void GLCamera::setRadiusPercent(const double pPerc)
{
    Vector3D temp = mLook - mEye;
    mLook = mEye + (temp * (pPerc/100) );
}

void GLCamera::getKeyboardInput(const char pKey)
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