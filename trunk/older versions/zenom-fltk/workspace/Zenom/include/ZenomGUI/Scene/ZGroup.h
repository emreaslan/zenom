/* 
 * File:   ZGroup.h
 * Author: root
 *
 * Created on May 3, 2010, 1:04 AM
 */

#ifndef _ZGROUP_H
#define	_ZGROUP_H

#include <fltk/gl.h>

#include "utils.h"
#include "Array.h"
#include "ZVrmlNode.h"

class ZGroup : public ZVrmlNode
{
public:
    ZGroup(const char* = NULL);

    ZGroup(const ZGroup& pRight);

    ~ZGroup();

    ZGroup& operator=(const ZGroup& pRight);

    void setBBoxCenter(ZVector3D& pBBoxCenter) { bboxCenter = pBBoxCenter; }
    ZVector3D getBBoxCenter() { return bboxCenter; }

    void setBBoxSize(ZVector3D& pBBoxSize) { bboxSize = pBBoxSize; }
    ZVector3D getBBoxSize() { return bboxSize; }

    virtual void addChild(ZVrmlNode* child) { children.appendElement(child); }

    virtual ZVrmlNode* clone();

    virtual void setField(const char*, ZAttribute&);

    virtual void action();

    virtual void addToBrowser(Browser* browser, Group* parent);

    virtual void print();

private:

    Array<ZVrmlNode*> children;
    ZVector3D bboxCenter;
    ZVector3D bboxSize;
};

#endif	/* _ZGROUP_H */

