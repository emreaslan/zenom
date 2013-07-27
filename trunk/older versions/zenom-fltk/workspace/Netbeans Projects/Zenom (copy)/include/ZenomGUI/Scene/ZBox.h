/* 
 * File:   ZBox.h
 * Author: root
 *
 * Created on April 9, 2010, 12:10 AM
 */

#ifndef _ZBOX_H
#define	_ZBOX_H

#include "Array.h"
#include "utils.h"
#include "ZGeometry.h"

class ZBox : public ZGeometry
{
public:
    ZBox(double = 2, double = 2, double = 2, const char* = NULL);
    
    ZBox(ZVector3D, const char* = NULL);

    ZBox(const ZBox& pRight);

    ZBox& operator=(const ZBox& pRight);

    ZVector3D getSize() { return size; }
    
    void setSize(ZVector3D pSize) { size = pSize; }

    virtual ZVrmlNode* clone();

    virtual void setField(const char*, ZAttribute &);
    
    virtual void action();

    virtual void addToBrowser(Browser* browser, Group* parent);

    virtual void print();
    
private:
    ZVector3D size;
};


#endif	/* _ZBOX_H */

