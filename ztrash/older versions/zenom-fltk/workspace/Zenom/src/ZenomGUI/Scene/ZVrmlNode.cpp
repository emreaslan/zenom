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
    name = pName;
}

ZVrmlNode::~ZVrmlNode()
{

}

void ZVrmlNode::setName(const char* newName)
{
	name = newName;
}
 

