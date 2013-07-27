/* 
 * File:   ZNoSupport.cpp
 * Author: root
 * 
 * Created on April 1, 2010, 1:08 AM
 */

#include "ZNotSupportedNode.h"

ZNotSupportedNode::ZNotSupportedNode(const char* pType) : ZVrmlNode(NULL, NODE_NO_SUPPORT)
{
    setNodeType(pType);
}

ZNotSupportedNode::ZNotSupportedNode(const ZNotSupportedNode& pRight)
 : ZVrmlNode(NULL, NODE_NO_SUPPORT)
{
    
}

ZNotSupportedNode::~ZNotSupportedNode()
{        

}

ZNotSupportedNode& ZNotSupportedNode::operator =(const ZNotSupportedNode& pRight)
{
    if( this != &pRight )
    {
        setName(pRight.getName());
        nodeType = pRight.nodeType;
    }

    return *this;
}

ZVrmlNode* ZNotSupportedNode::clone()
{
    ZNotSupportedNode* clone = new ZNotSupportedNode(*this);

    return dynamic_cast<ZNotSupportedNode*>(clone);
}

void ZNotSupportedNode::setNodeType(const char* newType)
{
	nodeType = newType;
}



void ZNotSupportedNode::setField(const char* fieldName, ZAttribute& value)
{

}

void ZNotSupportedNode::action()
{

}

void ZNotSupportedNode::print()
{
    printf("not supported node : %s\n", nodeType.c_str());
}

