/* 
 * File:   ZSphere.h
 * Author: root
 *
 * Created on May 2, 2010, 11:39 PM
 */

#ifndef _ZSPHERE_H
#define	_ZSPHERE_H

#include "Array.h"
#include "utils.h"
#include "ZGeometry.h"

class ZSphere : public ZGeometry
{
public:
    ZSphere(double = 1, const char* = NULL);

    ZSphere(const ZSphere& pRight);

    ZSphere& operator=(const ZSphere& pRight);

    double getRadius() { return radius; }

    void setRadius(double pRadius) { radius = pRadius; }

    virtual ZVrmlNode* clone();

    virtual void setField(const char*, ZAttribute &);

    virtual void action();

    virtual void addToBrowser(Browser* browser, Group* parent);

    virtual void print();

private:
    double radius;
    ZParameter zbp_radius;
};

#endif	/* _ZSPHERE_H */

