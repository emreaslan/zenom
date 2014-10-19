/* 
 * File:   ZVrmlNode.h
 * Author: CuneyT
 *
 * Created on March 21, 2010, 2:35 PM
 */

#ifndef _ZVRMLNODE_H
#define	_ZVRMLNODE_H

#include "Array.h"
#include "utils.h"
#include <string.h>
#include <fltk/Group.h>

enum ZVrmlNodeType{ NODE_TRANSFORM,
                    NODE_SHAPE,
                    NODE_APPEARANCE,
                    NODE_MATERIAL,
                    NODE_GEOMETRY,
                    NODE_GEOMETRY_BOX,            
                    NODE_GEOMETRY_CONE,
                    NODE_GEOMETRY_CYLINDER,
                    NODE_GEOMETRY_SPHERE,
                    NODE_GROUP,
                    NODE_NO_SUPPORT,
                    NODE_COORDINATE,
                    NODE_NORMAL,
                    NODE_POINT_SET,
                    NODE_INDEXED_LINE_SET,
                    NODE_INDEXED_FACE_SET,
                    NODE_ELEVATION_GRID,
                    NODE_COLOR,
                    NODE_VIEWPOINT,
                    NODE_NAVIGATION_INFO,
                    NODE_DIRECTIONAL_LIGHT,
                    NODE_POINT_LIGHT,
                    NODE_SPOT_LIGHT
                    };

class ZVrmlNode
{
public:
    ZVrmlNode(const char*, ZVrmlNodeType);
    
    virtual ~ZVrmlNode();

    const char* getName() const { return name; }
    void setName(const char*);

    int getType() { return type; }

    virtual ZVrmlNode* clone() = 0;

    virtual void addChild(ZVrmlNode*) {}

    virtual void setField(const char*, ZAttribute &) = 0;

    // gl cizimleri
    virtual void action() = 0;

    // fltk scene select window icin listeyi doldurur.
    virtual void addToBrowser(Browser* browser, Group* parent) = 0;

    virtual void print() = 0;
    
private:
    char* name;
    ZVrmlNodeType type;
};

#endif	/* _ZVRMLNODE_H */

