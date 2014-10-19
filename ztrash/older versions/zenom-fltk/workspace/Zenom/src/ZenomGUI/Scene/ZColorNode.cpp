/* 
 * File:   ZColorNode.cpp
 * Author: root
 * 
 * Created on April 1, 2010, 4:38 AM
 */

#include "ZColorNode.h"

ZColorNode::ZColorNode(char* pName)
: ZVrmlNode(pName, NODE_COLOR)
{

}

ZColorNode::ZColorNode(const ZColorNode& pRight)
: ZVrmlNode(pRight.getName(), NODE_COLOR)
{
    *this = pRight;
}

ZColorNode& ZColorNode::operator=(const ZColorNode& pRight)
{
    if( this != &pRight )
    {
        setName(pRight.getName());
        setColor(pRight.color);
    }
    return *this;
}

ZColorNode::~ZColorNode()
{

}

void ZColorNode::setColor(const Array<ZColor>& pColor)
{
    color = pColor;
    size = color.getNumElements();
}

ZVrmlNode* ZColorNode::clone()
{
    ZColorNode* clone = new ZColorNode(*this);

    return dynamic_cast<ZVrmlNode*>(clone);
}

void ZColorNode::setField(const char* fieldName, ZAttribute& value)
{
    if( !strcmp(fieldName, "color") )
        setColor(value.vZColors);
}

ZColor ZColorNode::getColor(int index)
{
	try
	{
		return color.getElement(index);
	}
	catch(std::exception& ex)
	{
		throw ZOutOfRange(ZString("Normal Node ") + ex.what());
	}
}

void ZColorNode::print()
{
    printf("ZColorNode: %s\n", getName());
    for(int i = 0; i < color.getNumElements(); ++i)
        printf("%f %f %f ", color.getElement(i).getR(), color.getElement(i).getG(), color.getElement(i).getB());
    printf("\n");
}

void ZColorNode::addToBrowser(Browser* browser, Group* parent)
{
    Group *g, *root;
    char buffer[15];
    if(getName())
    {
        char name[256];
        snprintf(name,256,"color (%s)", getName());
        root = browser->add_group (name, parent, NULL);
    }
    else
    {
        root = browser->add_group ("color", parent, NULL);
        root->deactivate();
    }

    root = browser->add_group ("color", root, &size);
    for(int i = 0; i < color.getNumElements(); ++i)
    {
        snprintf(buffer, 15, "[%d]",i);
        g = browser->add_group (buffer, root, &ZVector3DSize);
        color.getElementRef(i).addToBrowser(browser, g);
    }
}
