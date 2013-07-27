#ifndef _GL_CAMERA_H
#define	_GL_CAMERA_H


#include <iostream>
#include <fltk/gl.h>
#include <fltk/GlWindow.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "VectorRotater.h"
#include "Vector3D.h"

class GLCamera
{
public:
	GLCamera(void);
	GLCamera(const Vector3D &pEye,const Vector3D &pLook,const Vector3D &pUp);
	void setInitialParams(const Vector3D &pEye,const Vector3D &pLook,const Vector3D &pUp);
	void gotoInitialPos();
	void render();

        void setRadiusPercent(const double pPerc);

        // yukarı asagı donme
	void moveEyeUpDown(const double pAmount = 1);

        // saga sola donme
	void moveEyeLeftRight(const double pAmount = 1);

	void zoomIn(const double pAmount = 1);
	void zoomOut(const double pAmount = 1);

        // y ekseni
	void moveCameraUpDown(const double pAmount = 1);

        // x ekseni
	void moveCameraLeftRight(const double pAmount = 1);

        // ileri
	void moveCameraFortBack(const double pAmount = 1);

	void changeCameraType();
	void setIsArcCamera(bool pIsArc);
	void getKeyboardInput(const char pKey);

private:
	Vector3D mUp, mLook, mEye;
	VectorRotater mRotater, mXRotater;
	Vector3D mInitialUp, mInitialLook, mInitialEye;
	bool mIsArcCamera;

        Vector3D preEye,preLook,preUp;
        double mSensivity;
};

#endif
