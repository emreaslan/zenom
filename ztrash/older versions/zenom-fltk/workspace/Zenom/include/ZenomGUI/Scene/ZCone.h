/* 
 * File:   Zcone.h
 * Author: root
 *
 * Created on April 9, 2010, 12:09 AM
 */

#ifndef _ZCONE_H
#define	_ZCONE_H

#include "Array.h"
#include "utils.h"
#include "ZGeometry.h"

class ZCone : public ZGeometry
{
public:
    ZCone(double = 1, double = 2, char* = NULL);

    ZCone(const ZCone& pRight);

    ZCone& operator=(const ZCone& pRight);

    double getBottomRadius(){ return bottomRadius; }
    void setBottomRadius(double pBottomRadius){ bottomRadius = pBottomRadius; }

    double getHeight(){ return height; }
    void setHeight(double pHeight){ height = pHeight; }

    bool getSide(){ return side; }
    void setSide(bool pSide){ height = pSide; }

    bool getBottom(){ return bottom; }
    void setBottom(bool pBottom){ bottom = pBottom; }

    virtual ZVrmlNode* clone();    
   
    virtual void setField(const char*, ZAttribute &);

    virtual void action();

    virtual void addToBrowser(Browser* browser, Group* parent);

    virtual void print();

private:
    double bottomRadius;
    double height;
    bool side;
    bool bottom;

    ZParameter zbp_bottomRadius, zbp_height, zbp_side, zbp_bottom;
};

#endif	/* _ZCONE_H */

