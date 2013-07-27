/* 
 * File:   ZAppearance.cpp
 * Author: root
 * 
 * Created on March 25, 2010, 12:18 AM
 */

#include "ZAppearance.h"

ZAppearance::ZAppearance(const char * pName) : ZVrmlNode(pName, NODE_APPEARANCE)
{
    material = NULL;
}

ZAppearance::~ZAppearance()
{
    delete material;
}

ZAppearance::ZAppearance(const ZAppearance& pRight)
: ZVrmlNode(NULL, NODE_APPEARANCE)
{
    material = NULL;
    *this = pRight;
}

ZAppearance& ZAppearance::operator=(const ZAppearance& pRight)
{
    if( this != &pRight )
    {
        delete material;
        
        setName(pRight.getName());
        if(pRight.material)
        {
            material = new ZMaterial(*pRight.material);
        }
        else
        {
            material = NULL;
        }
    }
    return *this;
}

ZVrmlNode* ZAppearance::clone()
{
    ZAppearance* clone = new ZAppearance(*this);

    return dynamic_cast<ZVrmlNode*>(clone);
}

void ZAppearance::addChild(ZVrmlNode* pChild)
{
    ZMaterial* m = dynamic_cast< ZMaterial* >(pChild);
    if(m != NULL)
        material = m;
}

void ZAppearance::action()
{
    if(material != NULL)
        material->action();    
}

void ZAppearance::print()
{
    if(material != NULL)
        material->print();
}

void ZAppearance::addToBrowser(Browser* browser, Group* parent)
{
    Group* g, *root;
    root = browser->add_group ("Appearance", parent, NULL);
    if(material != NULL)
        material->addToBrowser(browser, root);
}

