/* 
 * File:   ZPointSet.cpp
 * Author: root
 * 
 * Created on April 29, 2010, 2:01 AM
 */

#include "ZPointSet.h"

ZPointSet::ZPointSet(const char* pName)
: ZGeometry(pName, NODE_POINT_SET)
{
    color = NULL;
    coord = NULL;
}

ZPointSet::ZPointSet(const ZPointSet& pRight) : ZGeometry(pRight.getName(), NODE_POINT_SET)
{
    if(pRight.color)
        color = new ZColorNode(*pRight.color);
    else
        color = NULL;

    if(pRight.coord)
        coord = new ZCoordinate(*pRight.coord);
    else
        coord = NULL;
}

ZPointSet::~ZPointSet()
{
    delete coord;
    delete color;
}

ZPointSet& ZPointSet::operator=(const ZPointSet& pRight)
{
    if( this != &pRight )
    {
        setName(pRight.getName());
        if(pRight.color)
            color = new ZColorNode(*pRight.color);
        else
            color = NULL;

        if(pRight.coord)
            coord = new ZCoordinate(*pRight.coord);
        else
            coord = NULL;
    }
    return *this;
}

ZVrmlNode* ZPointSet::clone()
{
    ZPointSet* clone = new ZPointSet(*this);

    return dynamic_cast<ZVrmlNode*>(clone);
}

void ZPointSet::action()
{
    glPushAttrib(GL_ENABLE_BIT);

    if(color)
        glDisable(GL_LIGHTING);

    if(coord)
    {
        glBegin(GL_POINTS);
        for (int i = 0; i < coord->getSize(); ++i)
        {
            if (color && i < color->getSize())
            {
                glColor3f(color->getColor(i).getR(), color->getColor(i).getG(), color->getColor(i).getB());
            }
            glVertex3f(coord->getPoint(i).getX(), coord->getPoint(i).getY(), coord->getPoint(i).getZ());
        }
        glEnd();
    }

    glPopAttrib();
   
}

void ZPointSet::addToBrowser(Browser* browser, Group* parent)
{
    Group *root;
    if(getName())
    {
        char name[256];
        snprintf(name,256,"PointSet (%s)", getName());
        root = browser->add_group (name, parent, NULL);
    }
    else
    {
        root = browser->add_group ("PointSet", parent, NULL);
        root->deactivate();
    }
    if(color)
        color->addToBrowser(browser, root);

    if(coord)
        coord->addToBrowser(browser, root);
}

void ZPointSet::addChild(ZVrmlNode* pChild)
{
    ZCoordinate* coordChild = dynamic_cast< ZCoordinate* >(pChild);
    if(coordChild != NULL)
        coord = coordChild;
    else
    {
        ZColorNode* colorChild = dynamic_cast< ZColorNode* >(pChild);
        if(colorChild != NULL)
            color = colorChild;
        else
            pChild->print();
    }
}

void ZPointSet::print()
{
    printf("ZPointSet: %s\n", getName());
    printf("coord :");
    if(coord)
        coord->print();
    printf("color :");
    if(color)
        color->print();
}

