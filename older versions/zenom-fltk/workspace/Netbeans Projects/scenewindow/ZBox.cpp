/* 
 * File:   ZBox.cpp
 * Author: root
 * 
 * Created on April 9, 2010, 12:10 AM
 */

#include "ZBox.h"

ZBox::ZBox(double pX, double pY, double pZ, const char* pName)
: ZGeometry(pName, NODE_GEOMETRY_BOX)
{
    size.setX(pX);
    size.setY(pY);
    size.setZ(pZ);
}


ZBox::ZBox(ZVector3D pVec3D, const char* pName)
: ZGeometry(pName, NODE_GEOMETRY_BOX)
{
    size = pVec3D;
}

ZBox::ZBox(const ZBox& pRight) : ZGeometry(NULL, NODE_GEOMETRY_BOX)
{
    *this = pRight;
}

ZBox& ZBox::operator=(const ZBox& pRight)
{
    if( this != &pRight )
    {
        setName(pRight.getName());
        size = pRight.size;
    }
    return *this;
}

ZVrmlNode* ZBox::clone()
{
    ZBox* clone = new ZBox(*this);

    return dynamic_cast<ZVrmlNode*>(clone);
}

void ZBox::setField(const char* fieldName, ZAttribute& value)
{
    if( !strcmp(fieldName, "size") )
        setSize(value.vZVector3D);
}

void ZBox::action()
{
    glPushAttrib(GL_ENABLE_BIT);
    glShadeModel(GL_FLAT);

    glBegin(GL_QUADS);

    // front
    glNormal3f( 0.0f, 0.0f, 1.0f);
    glVertex3f(-size.getX()/2, -size.getY()/2, size.getZ()/2);
    glVertex3f( size.getX()/2, -size.getY()/2, size.getZ()/2);
    glVertex3f( size.getX()/2,  size.getY()/2, size.getZ()/2);
    glVertex3f(-size.getX()/2,  size.getY()/2, size.getZ()/2);

    // back
    glNormal3f( 0.0f, 0.0f, -1.0f);
    glVertex3f(-size.getX()/2, -size.getY()/2, -size.getZ()/2);
    glVertex3f(-size.getX()/2,  size.getY()/2, -size.getZ()/2);
    glVertex3f( size.getX()/2,  size.getY()/2, -size.getZ()/2);
    glVertex3f( size.getX()/2, -size.getY()/2, -size.getZ()/2);

    // top
    glNormal3f( 0.0f, 1.0f, 0.0f);
    glVertex3f(-size.getX()/2, size.getY()/2, -size.getZ()/2);
    glVertex3f(-size.getX()/2, size.getY()/2,  size.getZ()/2);
    glVertex3f( size.getX()/2, size.getY()/2,  size.getZ()/2);
    glVertex3f( size.getX()/2, size.getY()/2, -size.getZ()/2);

    // bottom
    glNormal3f( 0.0f,-1.0f, 0.0f);
    glVertex3f(-size.getX()/2, -size.getY()/2, -size.getZ()/2);
    glVertex3f( size.getX()/2, -size.getY()/2, -size.getZ()/2);
    glVertex3f( size.getX()/2, -size.getY()/2,  size.getZ()/2);
    glVertex3f(-size.getX()/2, -size.getY()/2,  size.getZ()/2);

    // right
    glNormal3f( 1.0f, 0.0f, 0.0f);
    glVertex3f( size.getX()/2,  size.getY()/2,  size.getZ()/2);
    glVertex3f( size.getX()/2, -size.getY()/2,  size.getZ()/2);
    glVertex3f( size.getX()/2, -size.getY()/2, -size.getZ()/2);
    glVertex3f( size.getX()/2,  size.getY()/2, -size.getZ()/2);

    // left
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(-size.getX()/2,  size.getY()/2, -size.getZ()/2);
    glVertex3f(-size.getX()/2, -size.getY()/2, -size.getZ()/2);
    glVertex3f(-size.getX()/2, -size.getY()/2,  size.getZ()/2);
    glVertex3f(-size.getX()/2,  size.getY()/2,  size.getZ()/2);

    glEnd();

    glShadeModel(GL_SMOOTH);
    glPopAttrib();
}

void ZBox::addToBrowser(Browser* browser, Group* parent)
{
    Group* g, *root;    
    
    if(getName())
    {
        char name[256];
        snprintf(name,256,"Box (%s)", getName());
        root = browser->add_group (name, parent, NULL);
    }
    else
    {
        root = browser->add_group ("Box", parent, NULL);
        root->deactivate();
    }
    g = browser->add_group ("size", root, &ZVector3DSize);
    size.addToBrowser(browser, g);
}

void ZBox::print()
{
    printf("ZBOX: %s\n", getName());
    printf("size %f %f %f\n", size.getX(), size.getY(), size.getZ());
}
