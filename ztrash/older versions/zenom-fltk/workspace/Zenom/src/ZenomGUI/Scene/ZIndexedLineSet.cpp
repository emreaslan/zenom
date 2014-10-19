
#include "ZIndexedLineSet.h"

ZIndexedLineSet::ZIndexedLineSet(char* pName)
: ZGeometry(pName, NODE_INDEXED_LINE_SET)
{
    coord = NULL;
    color = NULL;

    zbp_colorPerVertex.type = Z_BOOLEAN;
    zbp_colorPerVertex.variable = &colorPerVertex;

    setColorPerVertex(true);
}

ZIndexedLineSet::ZIndexedLineSet(const ZIndexedLineSet& pRight)
: ZGeometry(NULL, NODE_INDEXED_LINE_SET)
{
    coord = NULL;
    color = NULL;

    *this = pRight;
}

ZIndexedLineSet::~ZIndexedLineSet()
{
    delete coord;
    delete color;

    zbp_coordIndex.deleteAllElements();
    zbp_colorIndex.deleteAllElements();
}

ZIndexedLineSet& ZIndexedLineSet::operator=(const ZIndexedLineSet& pRight)
{
    if( this != &pRight )
    {
        delete color;
        delete coord;

        setName(pRight.getName());
        colorPerVertex = pRight.colorPerVertex;
        zbp_colorPerVertex.type = Z_BOOLEAN;
        zbp_colorPerVertex.variable = &colorPerVertex;

        if(pRight.color)
            color = new ZColorNode(*pRight.color);
        else
            color = NULL;
        setColorIndex(pRight.colorIndex);


        if(pRight.coord)
            coord = new ZCoordinate(*pRight.coord);
        else
            coord = NULL;
        setCoordIndex(pRight.coordIndex);
        
    }
    return *this;
}

void ZIndexedLineSet::setCoordIndex(const Array<int>& pCoordIndex)
{
    coordIndex = pCoordIndex;

    zbp_coordIndex.deleteAllElements();
    for(int i = 0; i < coordIndex.getNumElements(); ++i)
    {
        zbp_coordIndex.appendElement(new ZParameter(Z_INTEGER, &(coordIndex.getElementRef(i))));
    }
    coordIndexSize = coordIndex.getNumElements();
}

void ZIndexedLineSet::setColorIndex(const Array<int>& pColorIndex)
{
    colorIndex = pColorIndex;

    zbp_colorIndex.deleteAllElements();
    for(int i = 0; i < colorIndex.getNumElements(); ++i)
    {
        zbp_colorIndex.appendElement(new ZParameter(Z_INTEGER, &(colorIndex.getElementRef(i))));
    }
    colorIndexSize = colorIndex.getNumElements();
}

ZVrmlNode* ZIndexedLineSet::clone()
{
    ZIndexedLineSet* clone = new ZIndexedLineSet(*this);

    return dynamic_cast<ZVrmlNode*>(clone);
}

void ZIndexedLineSet::setField(const char* fieldName, ZAttribute& value)
{
    if( !strcmp(fieldName, "coordIndex") )
        setCoordIndex(value.vIntegers);
    else if( !strcmp(fieldName, "colorIndex") )
        setColorIndex(value.vIntegers);
    else if( !strcmp(fieldName, "colorPerVertex") )
        setColorPerVertex(value.vBool);

}

void ZIndexedLineSet::addChild(ZVrmlNode* pChild)
{
    ZCoordinate*c = dynamic_cast< ZCoordinate* >(pChild);
    if(c != NULL)
        coord = c;
    else
    {
        ZColorNode* c = dynamic_cast< ZColorNode* >(pChild);
        if(c != NULL)
            color = c;
        else
            pChild->print();         
    }
}

void ZIndexedLineSet::action()
{
    if( coordIndex.isEmpty() || coord == NULL)
        return;

    glPushAttrib(GL_ENABLE_BIT);

    if(color)
    	glDisable(GL_LIGHTING);

    try
    {
        int colorIndx = 0;
        for(int i = 0; i < coordIndex.getNumElements()-1; ++i)
        {
            glBegin(GL_LINE);

            if(!colorPerVertex && color)
            {
            	if(!colorIndex.isEmpty())
            	{
            		glColor3dv(color->getColor(colorIndex.getElement(colorIndx)).getColor());
            	}
            	else
            	{
            		glColor3dv(color->getColor(colorIndx).getColor());
            	}
            	++colorIndx;
            }

            while( coordIndex.getElement(i+1) != -1 && i < coordIndex.getNumElements()-1)
            {
            	if(colorPerVertex && color)
      	        {
            		if(!colorIndex.isEmpty())
            		{
            			glColor3dv(color->getColor(colorIndex.getElement(i)).getColor());
            		}
            		else
            		{
            		    glColor3dv(color->getColor(coordIndex.getElement(i)).getColor());
            		}
            	}

                glVertex3dv(coord->getPoint(coordIndex.getElement(i)).getVec());


            	if(colorPerVertex && color)
      	        {
            		if(!colorIndex.isEmpty())
            		{
            			glColor3dv(color->getColor(colorIndex.getElement(i+1)).getColor());
            		}
            		else
            		{
            		    glColor3dv(color->getColor(coordIndex.getElement(i+1)).getColor());
            		}
            	}

                glVertex3dv(coord->getPoint(coordIndex.getElement(i+1)).getVec());

                ++i;
            }
            ++i; // -1 den kurtulmak icin

            glEnd();
        }
    }
    catch(std::exception& ex)
    {
    	printf("IndexedLineSet : %s", ex.what());
    }

    glPopAttrib();
}

void ZIndexedLineSet::addToBrowser(Browser* browser, Group* parent)
{
    Group *g, *root;
    char buffer[15];
    if(getName())
    {
        char name[256];
        snprintf(name,256,"IndexedLineSet (%s)", getName());
        root = browser->add_group (name, parent, NULL);
    }
    else
    {
        root = browser->add_group ("IndexedLineSet", parent, NULL);
        root->deactivate();
    }
    if(color)
        color->addToBrowser(browser, root);
    if(!colorIndex.isEmpty())
    {        
        g = browser->add_group ("colorIndex", root, &colorIndexSize);
        for(int i = 0; i < zbp_colorIndex.getNumElements(); ++i)
        {
            snprintf(buffer, 15, "[%d]",i);
            browser->add_leaf (buffer, g, zbp_colorIndex.getElementRef(i));
        }
    }


    if(coord)
        coord->addToBrowser(browser, root);
    if(!coordIndex.isEmpty())
    {
        g = browser->add_group ("coordIndex", root, &coordIndexSize);
        for(int i = 0; i < zbp_coordIndex.getNumElements(); ++i)
        {
            snprintf(buffer, 15, "[%d]",i);
            browser->add_leaf (buffer, g, zbp_coordIndex.getElementRef(i));
        }
    }

    browser->add_leaf ("colorPerVertex", root, &zbp_colorPerVertex);
}

void ZIndexedLineSet::print()
{
    printf("ZIndexedLineSet: %s\n", getName());
        
    if(coord != NULL)
        coord->print();

    printf("coordIndex:\n");
    for(int i = 0; i < coordIndex.getNumElements(); ++i)
        printf("%d ", coordIndex.getElement(i));
    printf("\n");


    if(color != NULL)
        color->print();

    printf("colorIndex:\n");
    for(int i = 0; i < colorIndex.getNumElements(); ++i)
        printf("%d ", colorIndex.getElement(i));
    printf("\n");



    printf("colorPerVertex : %d\n", colorPerVertex);
}

