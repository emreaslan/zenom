/* 
 * File:   ZNavigationInfo.h
 * Author: root
 *
 * Created on May 4, 2010, 5:23 AM
 */

#ifndef _ZNAVIGATIONINFO_H
#define	_ZNAVIGATIONINFO_H

#include <fltk/gl.h>

#include "Array.h"
#include "utils.h"
#include "ZVrmlNode.h"

class ZNavigationInfo : public ZVrmlNode
{

public:
    ZNavigationInfo(char* = NULL);

    ZNavigationInfo(const ZNavigationInfo& pRight);

    virtual ~ZNavigationInfo();

    ZNavigationInfo& operator=(const ZNavigationInfo& pRight);

    void setHeadlight(bool pHeadlight) { headlight = pHeadlight; }
    bool getHeadlight() { return headlight; }

    virtual ZVrmlNode* clone();

    virtual void setField(const char*, ZAttribute &);

    virtual void action();

    virtual void addToBrowser(Browser* browser, Group* parent);

    virtual void print();

private:

    bool headlight;
    ZParameter zbp_headlight;

};


#endif	/* _ZNAVIGATIONINFO_H */

