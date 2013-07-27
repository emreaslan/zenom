/* 
 * File:   ZCoordinate.h
 * Author: root
 *
 * Created on April 1, 2010, 2:15 AM
 */

#ifndef _ZNORMAL_H
#define	_ZNORMAL_H

#include "ZVrmlNode.h"
#include "Array.h"

#include "utils.h"

class ZNormal : public ZVrmlNode
{
public:
    ZNormal(char* = NULL);

    ZNormal(const ZNormal& pRight);

    ~ZNormal();

    ZNormal& operator=(const ZNormal& pRight);

    void setVector(const Array<ZVector3D>& pVector);

    Array<ZVector3D>& getVector() { return vector; }

    ZVector3D getVector(int index);

    int getSize() { return vector.getNumElements(); }

    virtual ZVrmlNode* clone();

    virtual void setField(const char*, ZAttribute &);

    virtual void action() {}

    virtual void print();

    virtual void addToBrowser(Browser* browser, Group* parent);
    
private:
    Array<ZVector3D> vector;
    int size;
};

#endif	/* _ZNORMAL_H */

