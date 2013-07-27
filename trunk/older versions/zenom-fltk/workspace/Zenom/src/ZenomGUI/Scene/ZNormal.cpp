
#include "ZNormal.h"

ZNormal::ZNormal(char* pName) : ZVrmlNode(pName, NODE_NORMAL)
{

}

ZNormal::ZNormal(const ZNormal& pRight) : ZVrmlNode(NULL, NODE_NORMAL)
{
    *this = pRight;
}

ZNormal::~ZNormal()
{

}

ZNormal& ZNormal::operator=(const ZNormal& pRight)
{
    if( this != &pRight )
    {       
        setName(pRight.getName());
        setVector(pRight.vector);
    }
    return *this;
}

ZVector3D ZNormal::getVector(int index)
{
	try
	{
		return vector.getElement(index);
	}
	catch(std::exception& ex)
	{
		throw ZOutOfRange(ZString("Normal Node ") + ex.what());
	}
}

void ZNormal::setVector(const Array<ZVector3D>& pVector)
{
    vector = pVector;
    size = vector.getNumElements();
}

ZVrmlNode* ZNormal::clone()
{
    ZNormal* clone = new ZNormal(*this);

    return dynamic_cast<ZVrmlNode*>(clone);
}

void ZNormal::setField(const char* fieldName, ZAttribute& value)
{
    if( !strcmp(fieldName, "vector") )
        setVector(value.vZVector3Ds);
}

void ZNormal::print()
{
    printf("ZNormal: %s\n", getName());
    for(int i = 0; i < vector.getNumElements(); ++i)
        printf("%f %f %f ", vector.getElement(i).getX(), vector.getElement(i).getY(), vector.getElement(i).getZ());
    printf("\n");
}

void ZNormal::addToBrowser(Browser* browser, Group* parent)
{
    Group *g, *root;
    char buffer[15];
    if(getName())
    {
        char name[256];
        snprintf(name,256,"normal (%s)", getName());
        root = browser->add_group (name, parent, NULL);
    }
    else
    {
        root = browser->add_group ("normal", parent, NULL);
        root->deactivate();
    }

    root = browser->add_group ("vector", root, &size);
    for(int i = 0; i < vector.getNumElements(); ++i)
    {
        snprintf(buffer, 15, "[%d]",i);
        g = browser->add_group (buffer, root, &ZVector3DSize);
        vector.getElementRef(i).addToBrowser(browser, g);
    }
}
