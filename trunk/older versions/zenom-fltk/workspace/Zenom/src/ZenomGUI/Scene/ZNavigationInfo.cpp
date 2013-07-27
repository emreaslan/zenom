/* 
 * File:   ZNavigationInfo.cpp
 * Author: root
 * 
 * Created on May 4, 2010, 5:23 AM
 */

#include "ZNavigationInfo.h"

ZNavigationInfo::ZNavigationInfo(char* pName)
: ZVrmlNode(pName, NODE_VIEWPOINT)
{
    headlight = true;
    zbp_headlight.type = Z_BOOLEAN;
    zbp_headlight.variable = &headlight;
}

ZNavigationInfo::ZNavigationInfo(const ZNavigationInfo& pRight): ZVrmlNode(NULL, NODE_VIEWPOINT)
{
    *this = pRight;
}

ZNavigationInfo::~ZNavigationInfo()
{

}

ZNavigationInfo& ZNavigationInfo::operator=(const ZNavigationInfo& pRight)
{
    if( this != &pRight )
    {
        setName(pRight.getName());
        headlight = pRight.headlight;
        zbp_headlight.type = Z_BOOLEAN;
        zbp_headlight.variable = &headlight;
    }
    return *this;
}


ZVrmlNode* ZNavigationInfo::clone()
{
    ZNavigationInfo* clone = new ZNavigationInfo(*this);

    return dynamic_cast<ZVrmlNode*>(clone);
}

void ZNavigationInfo::setField(const char* fieldName, ZAttribute& value)
{
    if( !strcmp(fieldName, "headlight") )
        setHeadlight(value.vBool);
}

void ZNavigationInfo::action()
{
    if(headlight)
    {
        glEnable(GL_LIGHT0);
    }
    else
    {
        glDisable(GL_LIGHT0);
        return;
    }
    

    float amb[4] = { 0, 0, 0, 1 };
    float dif[4] = { 1, 1, 1, 1 };
    float pos[4] = { 0, 0, 100, 1 };
    float shin[] = { 0.6, 0.6, 0.6, 1.0 };

    glLightfv(GL_LIGHT0, GL_AMBIENT, amb);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, dif);
    glLightfv(GL_LIGHT0, GL_POSITION, pos);
    glLightfv(GL_LIGHT0, GL_SPECULAR, shin);

    /*
    glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 1.0);
    glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.0);
    glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0.0);

    glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 180.0);
    glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, 0.0);

     */
    
}

void ZNavigationInfo::addToBrowser(Browser* browser, Group* parent)
{
	//TODO
	/*
    Group*root;
    if(getName())
    {
        char* name = new char[256];
        snprintf(name,256,"NavigationInfo (%s)", getName());
        root = browser->add_group (name, parent, NULL);
    }
    else
    {
        root = browser->add_group ("NavigationInfo", parent, NULL);
        root->deactivate();
    }
    browser->add_leaf("headlight", root, &zbp_headlight);
    */
}

void ZNavigationInfo::print()
{
    printf("NavigationInfo: %s\n", getName());
    printf("headlight %d\n", headlight);
}

