
#include "ZIndexedLineSet.h"

ZIndexedLineSet::ZIndexedLineSet(char* pName)
: ZGeometry(pName, NODE_INDEXED_LINE_SET)
{
    coord = NULL;
    coordIndex = NULL;

    color = NULL;
    colorIndex = NULL;

    zbp_colorPerVertex.type = Z_BOOLEAN;
    zbp_colorPerVertex.variable = &colorPerVertex;

    setColorPerVertex(true);
}

ZIndexedLineSet::ZIndexedLineSet(const ZIndexedLineSet& pRight)
: ZGeometry(NULL, NODE_INDEXED_LINE_SET)
{
    coord = NULL;
    coordIndex = NULL;

    color = NULL;
    colorIndex = NULL;

    *this = pRight;
}

ZIndexedLineSet::~ZIndexedLineSet()
{
    delete coordIndex;
    delete coord;

    delete colorIndex;
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

        if(pRight.colorIndex)
        {
            Array<int>* colors = new Array<int>();
            for(int i = 0; i < pRight.colorIndex->getNumElements(); ++i)
                colors->appendElement(pRight.colorIndex->getElement(i));
            setColorIndex(colors);
        }
        else
            setColorIndex(NULL);

        if(pRight.coord)
            coord = new ZCoordinate(*pRight.coord);
        else
            coord = NULL;

        if(pRight.coordIndex)
        {
            Array<int>* coords = new Array<int>();
            for(int i = 0; i < pRight.coordIndex->getNumElements(); ++i)
                coords->appendElement(pRight.coordIndex->getElement(i));
            setCoordIndex(coords);
        }
        else        
            setCoordIndex(NULL);
        
    }
    return *this;
}

void ZIndexedLineSet::setCoordIndex(Array<int>* pCoordIndex)
{
    delete coordIndex;
    coordIndex = pCoordIndex;

    if(coordIndex)
    {
        zbp_coordIndex.deleteAllElements();
        for(int i = 0; i < coordIndex->getNumElements(); ++i)
        {
            zbp_coordIndex.appendElement(new ZParameter(Z_INTEGER, &(coordIndex->getElementRef(i))));
        }
        coordIndexSize = coordIndex->getNumElements();
    }

}

void ZIndexedLineSet::setColorIndex(Array<int>* pColorIndex)
{
    delete colorIndex;
    colorIndex = pColorIndex;

    if(colorIndex)
    {
        zbp_colorIndex.deleteAllElements();
        for(int i = 0; i < colorIndex->getNumElements(); ++i)
        {
            zbp_colorIndex.appendElement(new ZParameter(Z_INTEGER, &(colorIndex->getElementRef(i))));
        }
        colorIndexSize = colorIndex->getNumElements();
    }
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
    if( coordIndex == NULL || coord == NULL)
        return;

    glPushAttrib(GL_ENABLE_BIT);

    if(color)
        glDisable(GL_LIGHTING);

    ZVector3D currCoord;
    ZColor currColor;
    for(int i = 0, j = 0; i < coordIndex->getNumElements(); ++i)
    {
        glBegin(GL_LINE_STRIP);
        while( coordIndex->getElement(i) != -1 && i < coordIndex->getNumElements())
        {
            if(color != NULL)
            {
                if( colorIndex && j < colorIndex->getNumElements() )
                    currColor = color->getColor(colorIndex->getElement(j));
                else
                    currColor = color->getColor(j);

                if( getColorPerVertex() )
                    j = (j + 1) % color->getSize();


                glColor3f(currColor.getR(), currColor.getG(), currColor.getB());
            }
            
            if(coordIndex->getElement(i) < coord->getSize())
                currCoord = coord->getPoint(coordIndex->getElement(i));
            glVertex3f(currCoord.getX(), currCoord.getY(), currCoord.getZ());
            ++i;
        }
        
        if( color && !getColorPerVertex() )
            j = (j + 1) % color->getSize();
        
        glEnd();
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
    if(colorIndex)
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
    if(coordIndex)
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
    if(coordIndex != NULL)
    {
        for(int i = 0; i < coordIndex->getNumElements(); ++i)
            printf("%d ", coordIndex->getElement(i));
        printf("\n");
    }


    if(color != NULL)
        color->print();

    printf("colorIndex:\n");
    if(colorIndex != NULL)
    {
        for(int i = 0; i < colorIndex->getNumElements(); ++i)
            printf("%d ", colorIndex->getElement(i));
        printf("\n");
    }

    printf("colorPerVertex : %d\n", colorPerVertex);
}

