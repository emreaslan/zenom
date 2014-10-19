/* 
 * File:   ZColorNode.h
 * Author: root
 *
 * Created on April 1, 2010, 4:38 AM
 */

#ifndef _ZCOLORNODE_H
#define	_ZCOLORNODE_H

#include "ZVrmlNode.h"
#include "Array.h"

#include "utils.h"

class ZColorNode : public ZVrmlNode
{
public:
    ZColorNode(char* = NULL);

    ZColorNode(const ZColorNode& pRight);

    ZColorNode& operator=(const ZColorNode& pRight);

    ~ZColorNode();

    // Be careful ZCoordinate class responsible for deleteing points array
    void setColor(Array<ZColor>* pColor);

    Array<ZColor>* getColor() { return color; }
    ZColor getColor(int index) { return color->getElement(index); }

    int getSize() { return color->getNumElements(); }

    virtual ZVrmlNode* clone();

    virtual void setField(const char*, ZAttribute &);

    virtual void action() {}

    virtual void print();

    virtual void addToBrowser(Browser* browser, Group* parent);

private:
    Array<ZColor>* color;
    int size;
};


#endif	/* _ZCOLORNODE_H */

