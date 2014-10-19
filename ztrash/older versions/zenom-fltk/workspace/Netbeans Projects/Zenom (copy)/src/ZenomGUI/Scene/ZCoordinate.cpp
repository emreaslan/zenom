/* 
 * File:   ZCoordinate.cpp
 * Author: root
 * 
 * Created on April 1, 2010, 2:15 AM
 */

#include "ZCoordinate.h"

ZCoordinate::ZCoordinate(char* pName)
: ZVrmlNode(pName, NODE_COORDINATE)
{
    point = NULL;
}

ZCoordinate::~ZCoordinate()
{
    delete point;
}

ZCoordinate::ZCoordinate(const ZCoordinate& pRight) : ZVrmlNode(pRight.getName(), NODE_COORDINATE)
{
    point = NULL;
    *this = pRight;
}

ZCoordinate& ZCoordinate::operator=(const ZCoordinate& pRight)
{
    if( this != &pRight )
    {     
        setName(pRight.getName());
        if(pRight.point)
        {
            Array<ZVector3D>* points = new Array<ZVector3D>();
            for(int i = 0; i < pRight.point->getNumElements(); ++i)
                points->appendElement(pRight.point->getElement(i));

            setPoint(points);
        }
        else
            setPoint(NULL);
    }
    return *this;
}

void ZCoordinate::setPoint(Array<ZVector3D>* pPoint)
{
    delete point;
    point = pPoint;
    if(point)
        size = point->getNumElements();
}

ZVrmlNode* ZCoordinate::clone()
{
    ZCoordinate* clone = new ZCoordinate(*this);

    return dynamic_cast<ZVrmlNode*>(clone);
}

void ZCoordinate::setField(const char* fieldName, ZAttribute& value)
{
    if( !strcmp(fieldName, "point") )
        setPoint(value.vZVector3Ds);
}

void ZCoordinate::print()
{
    printf("ZCoordinate: %s\n", getName());
    if(point != NULL)
    {
        for(int i = 0; i < point->getNumElements(); ++i)
            printf("%f %f %f ", point->getElement(i).getX(), point->getElement(i).getY(), point->getElement(i).getZ());
        printf("\n");
    }

}

void ZCoordinate::addToBrowser(Browser* browser, Group* parent)
{
    Group *g, *root;
    char buffer[15];
    if(getName())
    {
        char name[256];
        snprintf(name,256,"coord (%s)", getName());
        root = browser->add_group (name, parent, NULL);
        root = browser->add_group ("point", root, &size);
    }
    else
    {
        root = browser->add_group ("coord", parent, NULL);
        root->deactivate();
        root = browser->add_group ("point", root, &size);
        root->deactivate();
    }

    
    for(int i = 0; i < point->getNumElements(); ++i)
    {
        snprintf(buffer, 15, "[%d]",i);
        g = browser->add_group (buffer, root, &ZVector3DSize);
        point->getElementRef(i).addToBrowser(browser, g);
    }
}
