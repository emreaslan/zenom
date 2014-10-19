/* 
 * File:   ZSphere.cpp
 * Author: root
 * 
 * Created on May 2, 2010, 11:39 PM
 */

#include "ZSphere.h"

ZSphere::ZSphere(double pRadius, const char* pName)
: ZGeometry(pName, NODE_GEOMETRY_SPHERE), radius(pRadius)
{
    zbp_radius.type = Z_DOUBLE;
    zbp_radius.variable = &radius;
}


ZSphere::ZSphere(const ZSphere& pRight) : ZGeometry(NULL, NODE_GEOMETRY_SPHERE)
{
    *this = pRight;
}

ZSphere& ZSphere::operator=(const ZSphere& pRight)
{
    if( this != &pRight )
    {
        setName(pRight.getName());
        radius = pRight.radius;
        zbp_radius.type = Z_DOUBLE;
        zbp_radius.variable = &radius;
    }
    return *this;
}

ZVrmlNode* ZSphere::clone()
{
    ZSphere* clone = new ZSphere(*this);

    return dynamic_cast<ZVrmlNode*>(clone);
}

void ZSphere::setField(const char* fieldName, ZAttribute& value)
{
    if( !strcmp(fieldName, "radius") )
        setRadius(value.vFloat);
}

void ZSphere::action()
{
    glPushAttrib(GL_ENABLE_BIT);
    
    int lats = 10;
    int longs = 10;


    for(int i = 0; i <= lats; i++)
    {
        double lat0 = PI * (-0.5 + (double) (i - 1) / lats);
        double z0  = sin(lat0);
        double zr0 =  cos(lat0);

        double lat1 = PI * (-0.5 + (double) i / lats);
        double z1 = sin(lat1);
        double zr1 = cos(lat1);

        glBegin(GL_QUAD_STRIP);
        for(int j = 0; j <= longs; j++)
        {
            double lng = 2 * PI * (double) (j - 1) / longs;
            double x = cos(lng);
            double y = sin(lng);

            glNormal3f(-x * zr0 * radius, -y * zr0 * radius, -z0 * radius);
            glVertex3f( x * zr0 * radius,  y * zr0 * radius,  z0 * radius);
            glNormal3f(-x * zr1 * radius, -y * zr1 * radius, -z1 * radius);
            glVertex3f( x * zr1 * radius,  y * zr1 * radius,  z1 * radius);

        }
        glEnd();
    }
    glPopAttrib();
}

void ZSphere::addToBrowser(Browser* browser, Group* parent)
{
    Group *root;
    if(getName())
    {
        char name[256];
        snprintf(name,256,"Sphere (%s)", getName());
        root = browser->add_group (name, parent, NULL);
    }
    else
    {
        root = browser->add_group ("Sphere", parent, NULL);
        root->deactivate();
    }
    browser->add_leaf ("radius", root, &zbp_radius);
}

void ZSphere::print()
{
    printf("ZSphere: %s\n", getName());
    printf("radius %f\n", radius);
}

