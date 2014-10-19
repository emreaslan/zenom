#pragma once


#include <iostream>
#include <fltk/gl.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "VectorRotater.h"

#define PI (3.14159265)


class Camera
{
public:
	Camera(void);
	Camera(const Vector3D &pEye,const Vector3D &pLook,const Vector3D &pUp);
	void setInitialParams(const Vector3D &pEye,const Vector3D &pLook,const Vector3D &pUp);
	void gotoInitialPos();
	void render();
	void moveEyeUpDown(const double pAmount = 1);
	void moveEyeLeftRight(const double pAmount = 1);
	void zoomIn(const double pAmount = 1);
	void zoomOut(const double pAmount = 1);
	void moveCameraUpDown(const double pAmount = 1);
	void moveCameraLeftRight(const double pAmount = 1);
	void moveCameraFortBack(const double pAmount = 1);
	void changeCameraType();
	void setIsArcCamera(bool pIsArc);
	void getKeyboardInput(const char pKey);

private:
	Vector3D mUp, mLook, mEye;
	VectorRotater mRotater, mXRotater;
	Vector3D mInitialUp, mInitialLook, mInitialEye;
	bool mIsArcCamera;
};

