/* 
 * File:   utils.h
 * Author: CuneyT
 *
 * Created on March 21, 2010, 2:08 PM
 */

#ifndef _ZUTILS_H
#define	_ZUTILS_H

#include "Array.h"
#include <string>
# include <openvrml/vrml97_grammar.h>

#include <fltk/Group.h>
#include <fltk/Browser.h>

using namespace fltk;
using namespace openvrml;


struct ZColor 
{
    ZColor(double pR = 0, double pG = 0, double pB = 0)
    {
        rgb[0] = pR;
        rgb[1] = pG;
        rgb[2] = pB;
        rgb[3] = 1;
    }


    ZColor(openvrml::color pColor)
    {
        rgb[0] = pColor.r();
        rgb[1] = pColor.g();
        rgb[2] = pColor.b();
        rgb[3] = 1;
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
        browser->add_leaf ("r", parent, &rgb[0]);
        browser->add_leaf ("g", parent, &rgb[1]);
        browser->add_leaf ("b", parent, &rgb[2]);
    }

    double rgb[4];
};

struct ZVector3D
{
    ZVector3D(double pX = 0, double pY = 0, double pZ = 0) : x(pX), y(pY), z(pZ){}

    ZVector3D(openvrml::vec3f pVec3f) : x(pVec3f.x()), y(pVec3f.y()), z(pVec3f.z()){}

    ~ZVector3D() {}

    double getX() { return x; }
    void setX(double pX) { x = pX; }

    double getY() { return y; }
    void setY(double pY) { y = pY; }
    
    double getZ() { return z; }
    void setZ(double pZ) { z = pZ; }

    void print(){ printf("x:%f y:%f z:%f", x, y, z); }

    // fltk scene select window icin listeyi doldurur.
    void addToBrowser(Browser* browser, Group* parent)
    {
        browser->add_leaf ("x", parent, &x);
        browser->add_leaf ("y", parent, &y);
        browser->add_leaf ("z", parent, &z);
    }

    
    double x,y,z;
};

struct ZVector2D
{
    ZVector2D(double pX = 0, double pY = 0) : x(pX), y(pY){}
    
    ZVector2D(openvrml::vec2f pVec2f) : x(pVec2f.x()), y(pVec2f.y()){}
    
    ~ZVector2D() {}

    double getX() { return x; }
    void setX(double pX) { x = pX; }

    double getY() { return y; }
    void setY(double pY) { y = pY; }

    void print(){ printf("x:%f y:%f", x, y); }

    // fltk scene select window icin listeyi doldurur.
    void addToBrowser(Browser* browser, Group* parent)
    {
        browser->add_leaf ("x", parent, &x);
        browser->add_leaf ("y", parent, &y);
    }

    double x,y;
};

struct ZRotation
{
    ZRotation(double pX = 0, double pY = 0, double pZ = 1, double pAngle = 0)
    : x(pX), y(pY), z(pZ), angle(pAngle){}
    
    ZRotation(openvrml::rotation pRotation)
    : x(pRotation.x()), y(pRotation.y()), z(pRotation.z()), angle(pRotation.angle()){}

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
        browser->add_leaf ("x", parent, &x);
        browser->add_leaf ("y", parent, &y);
        browser->add_leaf ("z", parent, &z);
        browser->add_leaf ("angle", parent, &angle);
    }

    double x,y,z;
    double angle;
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
    ZVector2D vZVector2D;
    std::string vString;
    Array<ZColor>* vZColors;
    Array<float>* vFloats;
    Array<int>* vIntegers;
    Array<ZRotation>* vZRotations;
    //Array<char*> VStrings;
    Array<double>* vDoubles;
    Array<ZVector2D>* vZVector2Ds;
    Array<ZVector3D>* vZVector3Ds;    
};





#endif	/* _UTILS_H */

