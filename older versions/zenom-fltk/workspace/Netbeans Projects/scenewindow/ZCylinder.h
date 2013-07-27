/* 
 * File:   ZCylinder.h
 * Author: root
 *
 * Created on April 9, 2010, 12:09 AM
 */

#ifndef _ZCYLINDER_H
#define	_ZCYLINDER_H

#include "Array.h"
#include "utils.h"
#include "ZGeometry.h"

class ZCylinder : public ZGeometry
{
public:
    ZCylinder(double = 1, double = 2, char* = NULL);

    ZCylinder(const ZCylinder& pRight);

    ZCylinder& operator=(const ZCylinder& pRight);

    double getBottomRadius(){ return bottomRadius; }
    void setBottomRadius(double pBottomRadius){ bottomRadius = pBottomRadius; }

    double getHeight(){ return height; }
    void setHeight(double pHeight){ height = pHeight; }

    bool getSide(){ return side; }
    void setSide(bool pSide){ height = pSide; }

    bool getBottom(){ return bottom; }
    void setBottom(bool pBottom){ bottom = pBottom; }

    bool getTop(){ return top; }
    void setTop(bool pTop){ top = pTop; }

    virtual ZVrmlNode* clone();

    virtual void setField(const char*, ZAttribute &);

    virtual void action();

    virtual void addToBrowser(Browser* browser, Group* parent);

    void print();
    
private:
    double bottomRadius;
    double height;
    bool side;
    bool bottom;
    bool top;

    ZParameter zbp_bottomRadius, zbp_height, zbp_side, zbp_bottom, zbp_top;
};

#endif	/* _ZCONE_H */

