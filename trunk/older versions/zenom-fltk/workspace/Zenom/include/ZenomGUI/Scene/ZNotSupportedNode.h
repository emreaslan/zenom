/* 
 * File:   ZNoSupport.h
 * Author: root
 *
 * Created on April 1, 2010, 1:08 AM
 */

#ifndef _ZNOSUPPORT_H
#define	_ZNOSUPPORT_H

#include "ZVrmlNode.h"
#include "utils.h"

class ZNotSupportedNode : public ZVrmlNode
{
public:
    ZNotSupportedNode(const char*);

    ZNotSupportedNode(const ZNotSupportedNode& pRight);

    ~ZNotSupportedNode();

    ZNotSupportedNode& operator=(const ZNotSupportedNode& pRight);

    const char* getNodeType() { return nodeType.c_str(); }

    void setNodeType(const char*);

    virtual ZVrmlNode* clone();

    virtual void setField(const char*, ZAttribute &);

    virtual void action();

    virtual void addToBrowser(Browser* browser, Group* parent) { }

    virtual void print();
    
private:

    ZString nodeType;

};

#endif	/* _ZNOSUPPORT_H */

