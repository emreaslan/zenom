/* 
 * File:   utils.h
 * Author: CuneyT
 *
 * Created on March 21, 2010, 2:08 PM
 */

#ifndef _ZUTILS_H
#define	_ZUTILS_H

#include "ZParameter.h"
#include "Array.h"
#include <string>
# include <openvrml/vrml97_grammar.h>

#include <fltk/Group.h>
#include <fltk/Browser.h>

using namespace fltk;
using namespace openvrml;


#define PI 3.14159265
#define RAD2DEG(x) (x*180/PI) 
#define DEG2RAD(x) (x*PI/180)

struct ZColor 
{
    ZColor(double pR = 0, double pG = 0, double pB = 0)
    {
        rgb[0] = pR;
        rgb[1] = pG;
        rgb[2] = pB;

        zbp_R.type = Z_DOUBLE;
        zbp_R.variable = &rgb[0];
        zbp_G.type = Z_DOUBLE;
        zbp_G.variable = &rgb[1];
        zbp_B.type = Z_DOUBLE;
        zbp_B.variable = &rgb[2];
    }


    ZColor(openvrml::color pColor)
    {
        rgb[0] = pColor.r();
        rgb[1] = pColor.g();
        rgb[2] = pColor.b();

        zbp_R.type = Z_DOUBLE;
        zbp_R.variable = &rgb[0];
        zbp_G.type = Z_DOUBLE;
        zbp_G.variable = &rgb[1];
        zbp_B.type = Z_DOUBLE;
        zbp_B.variable = &rgb[2];
    }

    ZColor(const ZColor& pColor)
    {
        rgb[0] = pColor.rgb[0];
        rgb[1] = pColor.rgb[1];
        rgb[2] = pColor.rgb[2];

        zbp_R.type = Z_DOUBLE;
        zbp_R.variable = &rgb[0];
        zbp_G.type = Z_DOUBLE;
        zbp_G.variable = &rgb[1];
        zbp_B.type = Z_DOUBLE;
        zbp_B.variable = &rgb[2];
    }

    ZColor& operator=(const ZColor& pColor)
    {
        rgb[0] = pColor.rgb[0];
        rgb[1] = pColor.rgb[1];
        rgb[2] = pColor.rgb[2];

        zbp_R.type = Z_DOUBLE;
        zbp_R.variable = &rgb[0];
        zbp_G.type = Z_DOUBLE;
        zbp_G.variable = &rgb[1];
        zbp_B.type = Z_DOUBLE;
        zbp_B.variable = &rgb[2];
        return *this;
    }

    ~ZColor() {}

    double* getColor() { return rgb; }

    double getR() { return rgb[0]; }
    void setR(double pR) { rgb[0] = pR; }

    double getG() { return rgb[1]; }
    void setG(double pG) { rgb[1] = pG; }

    double getB() { return rgb[2]; }
    void setB(double pB) { rgb[2] = pB; }

    void print() {  printf("r:%f g:%f b:%f", rgb[0], rgb[1], rgb[2]);  }

    // fltk scene select window icin listeyi doldurur.
    void addToBrowser(Browser* browser, Group* parent)
    {
        browser->add_leaf ("r", parent, &zbp_R);
        browser->add_leaf ("g", parent, &zbp_G);
        browser->add_leaf ("b", parent, &zbp_B);
    }

    double rgb[3];
    ZParameter zbp_R, zbp_G, zbp_B;
};




struct ZVector3D
{
    ZVector3D(double pX = 0, double pY = 0, double pZ = 0)
    {
        vec[0] = pX;
        vec[1] = pY;
        vec[2] = pZ;

        zbp_X.type = Z_DOUBLE;
        zbp_X.variable = &vec[0];
        zbp_Y.type = Z_DOUBLE;
        zbp_Y.variable = &vec[1];
        zbp_Z.type = Z_DOUBLE;
        zbp_Z.variable = &vec[2];
    }

    ZVector3D(openvrml::vec3f pVec3f)
    {
        vec[0] = pVec3f.x();
        vec[1] = pVec3f.y();
        vec[2] = pVec3f.z();

        zbp_X.type = Z_DOUBLE;
        zbp_X.variable = &vec[0];
        zbp_Y.type = Z_DOUBLE;
        zbp_Y.variable = &vec[1];
        zbp_Z.type = Z_DOUBLE;
        zbp_Z.variable = &vec[2];
    }

    ZVector3D(const ZVector3D& pVec3f)
    {
        vec[0] = pVec3f.vec[0];
        vec[1] = pVec3f.vec[1];
        vec[2] = pVec3f.vec[2];
        
        zbp_X.type = Z_DOUBLE;
        zbp_X.variable = &vec[0];
        zbp_Y.type = Z_DOUBLE;
        zbp_Y.variable = &vec[1];
        zbp_Z.type = Z_DOUBLE;
        zbp_Z.variable = &vec[2];
    }

    ZVector3D& operator=(const ZVector3D& pVec3f)
    {
        vec[0] = pVec3f.vec[0];
        vec[1] = pVec3f.vec[1];
        vec[2] = pVec3f.vec[2];
        

        zbp_X.type = Z_DOUBLE;
        zbp_X.variable = &vec[0];
        zbp_Y.type = Z_DOUBLE;
        zbp_Y.variable = &vec[1];
        zbp_Z.type = Z_DOUBLE;
        zbp_Z.variable = &vec[2];
        return *this;
    }

    ZVector3D operator-(const ZVector3D& pVec3f)
    {
        return ZVector3D(vec[0] - pVec3f.vec[0], vec[1] - pVec3f.vec[1], vec[2] - pVec3f.vec[2]);
    }

    ZVector3D operator+(const ZVector3D& pVec3f)
    {
        return ZVector3D(vec[0] + pVec3f.vec[0], vec[1] + pVec3f.vec[1], vec[2] + pVec3f.vec[2]);
    }

    ZVector3D operator-()
    {
        return ZVector3D(-vec[0], -vec[1], -vec[2]);
    }

    ZVector3D operator*(const ZVector3D& pVec3f)
    {
        return ZVector3D(vec[1]*pVec3f.vec[2] - vec[2]*pVec3f.vec[1],
                         vec[2]*pVec3f.vec[0] - vec[0]*pVec3f.vec[2],
                         vec[0]*pVec3f.vec[1] - vec[1]*pVec3f.vec[0]);
    }

    ZVector3D normalize()
    {
        double length = sqrt(vec[0]*vec[0] + vec[1]*vec[1] + vec[2]*vec[2]);
        return ZVector3D(vec[0]/length, vec[1]/length, vec[2]/length);
    }
    
    ~ZVector3D() {}

    double* getVec() { return vec; }

    double getX() { return vec[0]; }
    void setX(double pX) { vec[0] = pX; }

    double getY() { return vec[1]; }
    void setY(double pY) { vec[1] = pY; }
    
    double getZ() { return vec[2]; }
    void setZ(double pZ) { vec[2] = pZ; }

    void print() const { printf("x::%f y:%f z:%f\n", vec[0], vec[1], vec[2]); }

    // fltk scene select window icin listeyi doldurur.
    void addToBrowser(Browser* browser, Group* parent)
    {
        browser->add_leaf ("x", parent, &zbp_X);
        browser->add_leaf ("y", parent, &zbp_Y);
        browser->add_leaf ("z", parent, &zbp_Z);
    }

    double vec[3];
    ZParameter zbp_X, zbp_Y, zbp_Z;
  
};

struct ZVector2D
{
    ZVector2D(double pX = 0, double pY = 0) : x(pX), y(pY)
    {
        zbp_X.type = Z_DOUBLE;
        zbp_X.variable = &x;
        zbp_Y.type = Z_DOUBLE;
        zbp_Y.variable = &y;
    }
    
    ZVector2D(openvrml::vec2f pVec2f) : x(pVec2f.x()), y(pVec2f.y())
    {
        zbp_X.type = Z_DOUBLE;
        zbp_X.variable = &x;
        zbp_Y.type = Z_DOUBLE;
        zbp_Y.variable = &y;
    }
    
    ZVector2D(const ZVector2D& pVec2f) : x(pVec2f.x), y(pVec2f.y)
    {
        zbp_X.type = Z_DOUBLE;
        zbp_X.variable = &x;
        zbp_Y.type = Z_DOUBLE;
        zbp_Y.variable = &y;
    }

    ZVector2D& operator=(const ZVector2D& pVec2f)
    {
        x = pVec2f.x;
        y = pVec2f.y;
        zbp_X.type = Z_DOUBLE;
        zbp_X.variable = &x;
        zbp_Y.type = Z_DOUBLE;
        zbp_Y.variable = &y;
        return *this;
    }

    ~ZVector2D() {}

    double getX() { return x; }
    void setX(double pX) { x = pX; }

    double getY() { return y; }
    void setY(double pY) { y = pY; }

    void print(){ printf("x:%f y:%f", x, y); }

    // fltk scene select window icin listeyi doldurur.
    void addToBrowser(Browser* browser, Group* parent)
    {
        browser->add_leaf ("x", parent, &zbp_X);
        browser->add_leaf ("y", parent, &zbp_Y);
    }

    double x,y;
    ZParameter zbp_X, zbp_Y;
};

struct ZRotation
{
    ZRotation(double pX = 0, double pY = 0, double pZ = 1, double pAngle = 0)
    : x(pX), y(pY), z(pZ), angle(pAngle)
    {
        zbp_X.type = Z_DOUBLE;
        zbp_X.variable = &x;
        zbp_Y.type = Z_DOUBLE;
        zbp_Y.variable = &y;
        zbp_Z.type = Z_DOUBLE;
        zbp_Z.variable = &z;
        zbp_Angle.type = Z_DOUBLE;
        zbp_Angle.variable = &angle;
    }
    
    ZRotation(openvrml::rotation pRotation)
    : x(pRotation.x()), y(pRotation.y()), z(pRotation.z()), angle(RAD2DEG(pRotation.angle()))
    {
        zbp_X.type = Z_DOUBLE;
        zbp_X.variable = &x;
        zbp_Y.type = Z_DOUBLE;
        zbp_Y.variable = &y;
        zbp_Z.type = Z_DOUBLE;
        zbp_Z.variable = &z;
        zbp_Angle.type = Z_DOUBLE;
        zbp_Angle.variable = &angle;
    }

    ZRotation(const ZRotation& pRotation) : x(pRotation.x), y(pRotation.y), z(pRotation.z), angle(pRotation.angle)
    {
        zbp_X.type = Z_DOUBLE;
        zbp_X.variable = &x;
        zbp_Y.type = Z_DOUBLE;
        zbp_Y.variable = &y;
        zbp_Z.type = Z_DOUBLE;
        zbp_Z.variable = &z;
        zbp_Angle.type = Z_DOUBLE;
        zbp_Angle.variable = &angle;
    }

    ZRotation& operator=(const ZRotation& pRotation)
    {
        x = pRotation.x;
        y = pRotation.y;
        z = pRotation.z;
        angle = pRotation.angle;
        zbp_X.type = Z_DOUBLE;
        zbp_X.variable = &x;
        zbp_Y.type = Z_DOUBLE;
        zbp_Y.variable = &y;
        zbp_Z.type = Z_DOUBLE;
        zbp_Z.variable = &z;
        zbp_Angle.type = Z_DOUBLE;
        zbp_Angle.variable = &angle;
        return *this;
    }

    ZRotation operator+(const ZRotation& pRotationf)
    {
        return ZRotation(x + pRotationf.x, y + pRotationf.y, z + pRotationf.z, angle + pRotationf.angle);
    }

    ~ZRotation() {}

    double getX() { return x; }
    void setX(double pX) { x = pX; }

    double getY() { return y; }
    void setY(double pY) { y = pY; }

    double getZ() { return z; }
    void setZ(double pZ) { z = pZ; }

    double getAngle() { return angle; }
    void setAngle(double pAngle) { angle = pAngle; }

    void print(){ printf("x:%f y:%f z:%f angle:%f", x, y, z, angle); }

    // fltk scene select window icin listeyi doldurur.
    void addToBrowser(Browser* browser, Group* parent)
    {
        browser->add_leaf ("x", parent, &zbp_X);
        browser->add_leaf ("y", parent, &zbp_Y);
        browser->add_leaf ("z", parent, &zbp_Z);
        browser->add_leaf ("angle", parent, &zbp_Angle);
    }

    double x,y,z;
    double angle;
    ZParameter zbp_X, zbp_Y, zbp_Z, zbp_Angle;
};

struct ZAttribute
{
    float vFloat;
    bool vBool;
    int vInt;
    ZRotation vZRotation;
    double vDouble;
    ZColor vZColor;
    ZVector3D vZVector3D;
    void* data;
    ZVector2D vZVector2D;
    std::string vString;
    Array<ZColor> vZColors;
    Array<int> vIntegers;
    Array<ZRotation> vZRotations;
    //Array<char*> VStrings;
    Array<double> vDoubles;
    Array<ZVector2D> vZVector2Ds;
    Array<ZVector3D> vZVector3Ds;
};

static int ZColorSize = 3;
static int ZVector3DSize = 3;
static int ZVector2DSize = 2;
static int ZRotationSize = 4;
#endif	/* _UTILS_H */

