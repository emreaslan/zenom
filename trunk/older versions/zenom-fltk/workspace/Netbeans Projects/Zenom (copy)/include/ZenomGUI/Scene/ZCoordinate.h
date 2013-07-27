/* 
 * File:   ZCoordinate.h
 * Author: root
 *
 * Created on April 1, 2010, 2:15 AM
 */

#ifndef _ZCOORDINATE_H
#define	_ZCOORDINATE_H

#include "ZVrmlNode.h"
#include "Array.h"

#include "utils.h"

class ZCoordinate : public ZVrmlNode
{
public:
    ZCoordinate(char* = NULL);

    ZCoordinate(const ZCoordinate& pRight);

    ZCoordinate& operator=(const ZCoordinate& pRight);

    ~ZCoordinate();

    // Be careful ZCoordinate class responsible for deleteing points array
    void setPoint(Array<ZVector3D>* pPoint);

    Array<ZVector3D>* getPoint() { return point; }

    ZVector3D getPoint(int index) { return point->getElement(index); }

    int getSize() { return point->getNumElements(); }

    ZVrmlNode* clone();

    virtual void setField(const char*, ZAttribute &);

    virtual void action() {}

    virtual void print();

    virtual void addToBrowser(Browser* browser, Group* parent);
    
private:
    Array<ZVector3D>* point;
    int size;
};

#endif	/* _ZCOORDINATE_H */

