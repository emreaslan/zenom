/* 
 * File:   ZPointSet.h
 * Author: root
 *
 * Created on April 29, 2010, 2:01 AM
 */

#ifndef _ZPOINTSET_H
#define	_ZPOINTSET_H

#include "Array.h"
#include "utils.h"
#include "ZGeometry.h"
#include "ZColorNode.h"
#include "ZCoordinate.h"

class ZPointSet : public ZGeometry
{
public:
    ZPointSet(const char* = NULL);

    ZPointSet(const ZPointSet& pRight);

    ZPointSet& operator=(const ZPointSet& pRight);

    ~ZPointSet();

    virtual ZVrmlNode* clone();

    virtual void addChild(ZVrmlNode*);

    virtual void setField(const char*, ZAttribute &) { }

    virtual void action();

    virtual void addToBrowser(Browser* browser, Group* parent);

    virtual void print();

private:
    ZColorNode* color;
    
    ZCoordinate* coord;
};

#endif	/* _ZPOINTSET_H */

