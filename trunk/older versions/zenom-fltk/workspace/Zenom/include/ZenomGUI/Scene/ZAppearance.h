/* 
 * File:   ZAppearance.h
 * Author: root
 *
 * Created on March 25, 2010, 12:18 AM
 */

#ifndef _ZAPPEARANCE_H
#define	_ZAPPEARANCE_H

#include "ZVrmlNode.h"
#include "Array.h"

#include "ZMaterial.h"

class ZAppearance : public ZVrmlNode
{
public:
    ZAppearance(const char* = NULL);

    ~ZAppearance();

    ZAppearance(const ZAppearance& pRight);

    ZAppearance& operator=(const ZAppearance& pRight);

    virtual ZVrmlNode* clone();

    virtual void addChild(ZVrmlNode*);

    virtual void setField(const char*, ZAttribute &) {}
    
    virtual void action();

    virtual void addToBrowser(Browser* browser, Group* parent);

    void print();

private:
    ZMaterial* material;

};

#endif	/* _ZAPPEARANCE_H */

