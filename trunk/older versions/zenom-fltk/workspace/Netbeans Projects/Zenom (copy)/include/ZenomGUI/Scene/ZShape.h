/* 
 * File:   ZShape.h
 * Author: CuneyT
 *
 * Created on March 21, 2010, 2:47 PM
 */

#ifndef _ZSHAPE_H
#define	_ZSHAPE_H

#include <string.h>

#include "ZVrmlNode.h"
#include "ZGeometry.h"
#include "ZAppearance.h"

#include "ZBox.h"
#include "ZCone.h"
#include "ZCylinder.h"
#include "ZSphere.h"
#include "ZPointSet.h"
#include "ZIndexedLineSet.h"
#include "ZIndexedFaceSet.h"
#include "ZElevationGrid.h"


class ZShape : public ZVrmlNode
{
public:
    ZShape(char* = NULL);

    ZShape(const ZShape& pRight);
    
    ~ZShape();

    ZShape& operator=(const ZShape& pRight);

    virtual void addChild(ZVrmlNode*);

    virtual ZVrmlNode* clone();

    virtual void setField(const char*, ZAttribute &);

    virtual void print();

    virtual void action();

    virtual void addToBrowser(Browser* browser, Group* parent);
    
private:    
    ZGeometry* geometry;
    ZAppearance* appearance;
};

#endif	/* _ZSHAPE_H */

