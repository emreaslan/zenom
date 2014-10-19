/* 
 * File:   ZGeometry.h
 * Author: CuneyT
 *
 * Created on March 21, 2010, 2:49 PM
 */

#ifndef _ZGEOMETRY_H
#define	_ZGEOMETRY_H

#include "ZVrmlNode.h"
#include "Array.h"
#include <string.h>
#include <fltk/gl.h>

// Base geometry class
class ZGeometry : public ZVrmlNode
{
public:
    ZGeometry(const char* = NULL, ZVrmlNodeType = NODE_GEOMETRY);

    virtual ~ZGeometry();

    virtual void setField(const char*, ZAttribute &) = 0;

    virtual void print() = 0;
    
    virtual void action() = 0;
    
    virtual void addToBrowser(Browser* browser, Group* parent) = 0;
};







/*
class IndexedFaceSet : public ZGeometry
{
public:
    IndexedFaceSet(double = 2, double = 2, double = 2, char* = NULL);
    virtual void draw();
private:
    double x,y,z;
};*/



#endif	/* _ZGEOMETRY_H */

