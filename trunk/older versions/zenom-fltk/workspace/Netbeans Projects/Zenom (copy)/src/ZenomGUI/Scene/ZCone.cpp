/* 
 * File:   Zcone.cpp
 * Author: root
 * 
 * Created on April 9, 2010, 12:09 AM
 */

#include "ZCone.h"

ZCone::ZCone(double pBottomRadius, double pHeight, char* pName)
: ZGeometry(pName, NODE_GEOMETRY_CONE), bottomRadius(pBottomRadius), height(pHeight)
{
    side = true;
    bottom = true;

    zbp_bottomRadius.type = Z_DOUBLE;
    zbp_bottomRadius.variable = &bottomRadius;
    zbp_height.type = Z_DOUBLE;
    zbp_height.variable = &height;
    zbp_side.type = Z_BOOLEAN;
    zbp_side.variable = &side;
    zbp_bottom.type = Z_BOOLEAN;
    zbp_bottom.variable = &bottom;
}

ZCone::ZCone(const ZCone& pRight) : ZGeometry(NULL, NODE_GEOMETRY_CONE)
{
    *this = pRight;
}

ZCone& ZCone::operator=(const ZCone& pRight)
{
    if( this != &pRight )
    {
        setName(pRight.getName());
        bottomRadius = pRight.bottomRadius;
        height = pRight.height;
        side = pRight.side;
        bottom = pRight.bottom;

        zbp_bottomRadius.type = Z_DOUBLE;
        zbp_bottomRadius.variable = &bottomRadius;
        zbp_height.type = Z_DOUBLE;
        zbp_height.variable = &height;
        zbp_side.type = Z_BOOLEAN;
        zbp_side.variable = &side;
        zbp_bottom.type = Z_BOOLEAN;
        zbp_bottom.variable = &bottom;
    }
    return *this;
}

ZVrmlNode* ZCone::clone()
{
    ZCone* clone = new ZCone(*this);

    return dynamic_cast<ZVrmlNode*>(clone);
}


void ZCone::setField(const char* fieldName, ZAttribute& value)
{
    if( !strcmp(fieldName, "bottomRadius") )
        setBottomRadius(value.vFloat);
    else if( !strcmp(fieldName, "height") )
        setHeight(value.vFloat);
    else if( !strcmp(fieldName, "side") )
        setSide(value.vBool);
    else if( !strcmp(fieldName, "bottom") )
        setBottom(value.vBool);
}

void ZCone::action()
{
    glPushAttrib(GL_ENABLE_BIT);
    glShadeModel(GL_SMOOTH);
    
    if (side)
    {
        glBegin(GL_QUAD_STRIP);
        for (int i = 0; i <= 360; i += 12)
        {
            float x = cos(DEG2RAD(i)) * bottomRadius;
            float y = sin(DEG2RAD(i)) * bottomRadius;
            glNormal3f(x, bottomRadius * bottomRadius / height, y);
            glVertex3f(x, -height/2, y);
            glVertex3f(0, height/2, 0);
        }
        glEnd();
    }

    if (bottom) 
    {
        glBegin(GL_TRIANGLE_FAN);
        glNormal3f(0.0, -1.0, 0.0);
        for (int i = 0; i <= 360; i += 12)
        {
            glVertex3f(cos(DEG2RAD(i)) * bottomRadius, -height/2, sin(DEG2RAD(i)) * bottomRadius);
        }
        glEnd();
    }

    glPopAttrib();
}

void ZCone::addToBrowser(Browser* browser, Group* parent)
{
    Group *root;
    if(getName())
    {
        char name[256];
        snprintf(name,256,"Cone (%s)", getName());
        root = browser->add_group (name, parent, NULL);
    }
    else
    {
        root = browser->add_group ("Cone", parent, NULL);
        root->deactivate();
    }
    browser->add_leaf ("bottomRadius", root, &zbp_bottomRadius);
    browser->add_leaf ("height", root, &zbp_height);
    browser->add_leaf ("side", root, &zbp_side);
    browser->add_leaf ("bottom", root, &zbp_bottom);
}

void ZCone::print()
{
    printf("ZCone: %s\n", getName());
    printf("bottomRadius %f\n", bottomRadius);
    printf("height %f\n", height);
    printf("side %d\n", side);
    printf("bottom %d\n", bottom);
}
