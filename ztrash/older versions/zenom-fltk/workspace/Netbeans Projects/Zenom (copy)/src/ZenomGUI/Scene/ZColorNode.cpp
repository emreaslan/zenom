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
    color = NULL;
}

ZColorNode::ZColorNode(const ZColorNode& pRight)
: ZVrmlNode(pRight.getName(), NODE_COLOR)
{
    color = NULL;
    *this = pRight;
}

ZColorNode& ZColorNode::operator=(const ZColorNode& pRight)
{
    if( this != &pRight )
    {
        setName(pRight.getName());
        if(pRight.color)
        {            
            Array<ZColor>* colors = new Array<ZColor>();
            for(int i = 0; i < pRight.color->getNumElements(); ++i)
            {
                colors->appendElement(pRight.color->getElement(i));
            }
            setColor(colors);
        }
        else
            setColor(NULL);
    }
    return *this;
}

ZColorNode::~ZColorNode()
{
    delete color;
}

void ZColorNode::setColor(Array<ZColor>* pColor)
{
    delete color;
    color = pColor;
    if(color)
        size = color->getNumElements();
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

void ZColorNode::print()
{
    printf("ZColorNode: %s\n", getName());
    if(color != NULL)
    {
        for(int i = 0; i < color->getNumElements(); ++i)
            printf("%f %f %f ", color->getElement(i).getR(), color->getElement(i).getG(), color->getElement(i).getB());
        printf("\n");
    }

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
    for(int i = 0; i < color->getNumElements(); ++i)
    {
        snprintf(buffer, 15, "[%d]",i);
        g = browser->add_group (buffer, root, &ZVector3DSize);
        color->getElementRef(i).addToBrowser(browser, g);
    }
}
