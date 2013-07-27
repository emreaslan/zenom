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

}

ZCoordinate::~ZCoordinate()
{

}

ZCoordinate::ZCoordinate(const ZCoordinate& pRight) : ZVrmlNode(pRight.getName(), NODE_COORDINATE)
{
    *this = pRight;
}

ZCoordinate& ZCoordinate::operator=(const ZCoordinate& pRight)
{
    if( this != &pRight )
    {     
        setName(pRight.getName());
        setPoint(pRight.point);
    }
    return *this;
}

void ZCoordinate::setPoint(const Array<ZVector3D>& pPoint)
{
    point = pPoint;
    size = point.getNumElements();
}

ZVector3D ZCoordinate::getPoint(int index)
{
	try
	{
		return point.getElement(index);
	}
	catch(std::exception& ex)
	{
		throw ZOutOfRange(ZString("Coordinate Node ") + ex.what());
	}
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
    for(int i = 0; i < point.getNumElements(); ++i)
        printf("%f %f %f ", point.getElement(i).getX(), point.getElement(i).getY(), point.getElement(i).getZ());
    printf("\n");
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

    
    for(int i = 0; i < point.getNumElements(); ++i)
    {
        snprintf(buffer, 15, "[%d]",i);
        g = browser->add_group (buffer, root, &ZVector3DSize);
        point.getElementRef(i).addToBrowser(browser, g);
    }
}
