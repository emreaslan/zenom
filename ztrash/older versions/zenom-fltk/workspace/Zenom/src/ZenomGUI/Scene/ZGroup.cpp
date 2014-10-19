/* 
 * File:   ZGroup.cpp
 * Author: root
 * 
 * Created on May 3, 2010, 1:04 AM
 */

#include "ZGroup.h"

ZGroup::ZGroup(const char *pName)
 : ZVrmlNode(pName, NODE_GROUP)
{
    bboxSize.setX(-1);
    bboxSize.setY(-1);
    bboxSize.setZ(-1);
}

ZGroup::ZGroup(const ZGroup& pRight) : ZVrmlNode(NULL, NODE_GROUP)
{
    bboxSize.setX(-1);
    bboxSize.setY(-1);
    bboxSize.setZ(-1);

    *this = pRight;
}

ZGroup::~ZGroup()
{
    for(int i = 0; i < children.getNumElements(); ++i)
        delete children.getElement(i);
}

ZGroup& ZGroup::operator=(const ZGroup& pRight)
{
    if( this != &pRight )
    {
        for(int i = 0; i < children.getNumElements(); ++i)
            delete children.getElement(i);
        children.removeAllElements();

        setName(pRight.getName());
        bboxCenter = pRight.bboxCenter;
        bboxSize = pRight.bboxSize;

        for(int i = 0; i < pRight.children.getNumElements(); ++i)
            children.appendElement(pRight.children.getElement(i)->clone());
    }

    return *this;
}

ZVrmlNode* ZGroup::clone()
{
    ZGroup* clone = new ZGroup(*this);

    return dynamic_cast<ZVrmlNode*>(clone);
}

void ZGroup::setField(const char* fieldName, ZAttribute& value)
{
    if( !strcmp(fieldName, "bboxCenter") )
        setBBoxCenter(value.vZVector3D);
    else if( !strcmp(fieldName, "bboxSize") )
        setBBoxSize(value.vZVector3D);
}


void ZGroup::action()
{
    for(int i = 0; i < children.getNumElements(); ++i)
        children.getElement(i)->action();
}

void ZGroup::addToBrowser(Browser* browser, Group* parent)
{
    Group* g, *root;
    root = browser->add_group ("Group", parent, NULL);
    g = browser->add_group ("bboxCenter", root, &ZVector3DSize);
    bboxCenter.addToBrowser(browser, g);
    g = browser->add_group ("bboxSize", root, &ZVector3DSize);
    bboxSize.addToBrowser(browser, g);
    for(int i = 0; i < children.getNumElements(); ++i)
        children.getElement(i)->addToBrowser(browser, root);
}

void ZGroup::print()
{
    printf("Group: %s\n", getName());
    printf("bboxCenter "); bboxCenter.print();
    printf("bboxSize "); bboxSize.print();
    for(int i = 0; i < children.getNumElements(); ++i)
        children.getElement(i)->print();
}
