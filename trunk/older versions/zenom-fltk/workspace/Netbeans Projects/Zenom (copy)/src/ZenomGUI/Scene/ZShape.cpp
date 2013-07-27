/* 
 * File:   ZShape.cpp
 * Author: CuneyT
 * 
 * Created on March 21, 2010, 2:47 PM
 */

#include "ZShape.h"
#include "ZGeometry.h"

ZShape::ZShape(char * pName) : ZVrmlNode(pName, NODE_SHAPE)
{
    geometry = NULL;
    appearance = NULL;
}

ZShape::ZShape(const ZShape& pRight): ZVrmlNode(NULL, NODE_SHAPE)
{
    geometry = NULL;
    appearance = NULL;
    *this = pRight;
}

ZShape::~ZShape()
{
    delete geometry;
    delete appearance;
}

ZShape& ZShape::operator=(const ZShape& pRight)
{
    if( this != &pRight )
    {
        delete geometry;
        delete appearance;

        setName(pRight.getName());
        if(pRight.geometry)
            geometry = dynamic_cast< ZGeometry* >(pRight.geometry->clone());
        else
            geometry = NULL;


        if(pRight.appearance)
            appearance = new ZAppearance(*pRight.appearance);
        else
            appearance = NULL;
    }
    return *this;
}

void ZShape::addChild(ZVrmlNode* pChild)
{
    ZGeometry*g = dynamic_cast< ZGeometry* >(pChild);
    if(g != NULL)
        geometry = g;
    else
    {
        ZAppearance* a = dynamic_cast< ZAppearance* >(pChild);
        if(a != NULL)
            appearance = a;
        else
            pChild->print();
    }
}

ZVrmlNode* ZShape::clone()
{
    ZShape* clone = new ZShape(*this);

    return dynamic_cast<ZShape*>(clone);
}

void ZShape::setField(const char*, ZAttribute&)
{
    
}

void ZShape::action()
{
    if(appearance != NULL)
        appearance->action();

    if(geometry != NULL)
        geometry->action();
}


void ZShape::addToBrowser(Browser* browser, Group* parent)
{
    Group* g, *root;
    root = browser->add_group ("Shape", parent, NULL);
    if(appearance != NULL)
        appearance->addToBrowser(browser, root);

    if(geometry != NULL)
        geometry->addToBrowser(browser, root);
}

void ZShape::print()
{
    printf("Shape %s\n", getName());
    if(appearance != NULL)
        appearance->print();

    if(geometry != NULL)
        geometry->print();

}
