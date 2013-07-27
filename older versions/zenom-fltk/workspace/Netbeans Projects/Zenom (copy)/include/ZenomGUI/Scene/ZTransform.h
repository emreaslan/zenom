/* 
 * File:   ZTransform.h
 * Author: CuneyT
 *
 * Created on March 21, 2010, 2:15 PM
 */

#ifndef _ZTRANSFORM_H
#define	_ZTRANSFORM_H

#include <fltk/gl.h>

#include "utils.h"
#include "Array.h"
#include "ZVrmlNode.h"

class ZTransform : public ZVrmlNode
{
public:
    ZTransform(const char* = NULL);

    ZTransform(const ZTransform& pRight);

    ~ZTransform();   

    ZTransform& operator=(const ZTransform& pRight);

    void setCenter(ZVector3D& pCenter) { center = pCenter; }
    ZVector3D getCenter() { return center; }

    void setRotation(ZRotation pRotation) { rotation = pRotation; }
    ZRotation getRotation() { return rotation; }

    void setScale(ZVector3D& pScale) { scale = pScale; }
    ZVector3D getScale() { return scale; }

    void setScaleOrientation(ZRotation pScaleOrientation) { scaleOrientation = pScaleOrientation; }
    ZRotation getScaleOrientation() { return scaleOrientation; }

    void setTranslation(ZVector3D& pTranslation) { translation = pTranslation; }
    ZVector3D getTranslation() { return translation; }

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

    ZVector3D center;
    Array<ZVrmlNode*> children;
    ZRotation rotation;
    ZVector3D scale;
    ZRotation scaleOrientation;
    ZVector3D translation;
    ZVector3D bboxCenter;
    ZVector3D bboxSize;
};

#endif	/* _ZTRANSFORM_H */

