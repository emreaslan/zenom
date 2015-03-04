/* 
 * File:   ZVrmlNode.cpp
 * Author: CuneyT
 * 
 * Created on March 21, 2010, 2:35 PM
 */

#include "ZVrmlNode.h"

ZVrmlNode::ZVrmlNode(const char* pName, ZVrmlNodeType pType)
{
    type = pType;
    name = NULL;
    setName(pName);
}

ZVrmlNode::~ZVrmlNode()
{
    delete[] name;
}

void ZVrmlNode::setName(const char* newName)
{
    delete[] name;
    if(newName != NULL)
    {        
        name = new char[strlen(newName)];
        strcpy(name, newName);
    } else {
        name = NULL;
    }
}
 
