/* 
 * File:   ZIndexedFaceSet.cpp
 * Author: root
 * 
 * Created on April 1, 2010, 5:50 PM
 */

#include "ZIndexedFaceSet.h"


ZIndexedFaceSet::ZIndexedFaceSet(char* pName)
: ZGeometry(pName, NODE_INDEXED_FACE_SET)
{
    coord = NULL;
    color = NULL;
    normal = NULL;


    zbp_normalPerVertex.type = Z_BOOLEAN;
    zbp_normalPerVertex.variable = &normalPerVertex;
    zbp_colorPerVertex.type = Z_BOOLEAN;
    zbp_colorPerVertex.variable = &colorPerVertex;
    zbp_solid.type = Z_BOOLEAN;
    zbp_solid.variable = &solid;
    zbp_ccw.type = Z_BOOLEAN;
    zbp_ccw.variable = &ccw;

    setNormalPerVertex(true);
    setColorPerVertex(true);
    setSolid(true);
    setCcw(true);
}

ZIndexedFaceSet::ZIndexedFaceSet(const ZIndexedFaceSet& pRight)
: ZGeometry(NULL, NODE_INDEXED_FACE_SET)
{
    coord = NULL;
    color = NULL;
    normal = NULL;

    *this = pRight;
}

ZIndexedFaceSet::~ZIndexedFaceSet()
{
    delete coord;
    zbp_coordIndex.deleteAllElements();

    delete color;
    zbp_colorIndex.deleteAllElements();

    delete normal;
    zbp_normalIndex.deleteAllElements();
}

ZIndexedFaceSet& ZIndexedFaceSet::operator=(const ZIndexedFaceSet& pRight)
{
    if( this != &pRight )
    {
        delete coord;
        delete color;
        delete normal;

        setName(pRight.getName());
        colorPerVertex = pRight.colorPerVertex;
        solid = pRight.solid;
        normalPerVertex = pRight.normalPerVertex;
        ccw = pRight.ccw;

        zbp_normalPerVertex.type = Z_BOOLEAN;
        zbp_normalPerVertex.variable = &normalPerVertex;
        zbp_colorPerVertex.type = Z_BOOLEAN;
        zbp_colorPerVertex.variable = &colorPerVertex;
        zbp_solid.type = Z_BOOLEAN;
        zbp_solid.variable = &solid;
        zbp_ccw.type = Z_BOOLEAN;
        zbp_ccw.variable = &ccw;

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

        if(pRight.normal)
            normal = new ZNormal(*pRight.normal);
        else
            normal = NULL;
        setNormalIndex(pRight.normalIndex);
    }
    return *this;
}

void ZIndexedFaceSet::setCoordIndex(const Array<int>& pCoordIndex)
{
    coordIndex = pCoordIndex;

    zbp_coordIndex.deleteAllElements();
    for(int i = 0; i < coordIndex.getNumElements(); ++i)
    {
        zbp_coordIndex.appendElement(new ZParameter(Z_INTEGER, &(coordIndex.getElementRef(i))));
    }
    coordIndexSize = coordIndex.getNumElements();
}

void ZIndexedFaceSet::setColorIndex(const Array<int>& pColorIndex)
{
    colorIndex = pColorIndex;

    zbp_colorIndex.deleteAllElements();
    for(int i = 0; i < colorIndex.getNumElements(); ++i)
    {
        zbp_colorIndex.appendElement(new ZParameter(Z_INTEGER, &(colorIndex.getElementRef(i))));
    }
    colorIndexSize = colorIndex.getNumElements();


}

void ZIndexedFaceSet::setNormalIndex(const Array<int>& pNormalIndex)
{
    normalIndex = pNormalIndex;

    zbp_normalIndex.deleteAllElements();
    for(int i = 0; i < normalIndex.getNumElements(); ++i)
    {
        zbp_normalIndex.appendElement(new ZParameter(Z_INTEGER, &(normalIndex.getElementRef(i))));
    }
    normalIndexSize = normalIndex.getNumElements();
}

void ZIndexedFaceSet::setSolid(bool pSolid)
{
    solid = pSolid;
}

ZVrmlNode* ZIndexedFaceSet::clone()
{
    ZIndexedFaceSet* clone = new ZIndexedFaceSet(*this);

    return dynamic_cast<ZIndexedFaceSet*>(clone);
}

void ZIndexedFaceSet::setField(const char* fieldName, ZAttribute& value)
{
    if( !strcmp(fieldName, "coordIndex") )
        setCoordIndex(value.vIntegers);
    else if( !strcmp(fieldName, "colorIndex") )
        setColorIndex(value.vIntegers);
    else if( !strcmp(fieldName, "normalIndex") )
        setNormalIndex(value.vIntegers);
    else if( !strcmp(fieldName, "colorPerVertex") )
        setColorPerVertex(value.vBool);
    else if( !strcmp(fieldName, "solid") )
        setSolid(value.vBool);
    else if( !strcmp(fieldName, "ccw") )
        setCcw(value.vBool);
    else if( !strcmp(fieldName, "normalPerVertex") )
        setNormalPerVertex(value.vBool);
}

void ZIndexedFaceSet::addChild(ZVrmlNode* pChild)
{
    ZCoordinate* coordinateNode;
    ZColorNode* colorNode;
    ZNormal* normalNode;

    if( (coordinateNode = dynamic_cast< ZCoordinate* >(pChild)) != NULL)
        coord = coordinateNode;
    else if( (colorNode = dynamic_cast< ZColorNode* >(pChild)) != NULL)
        color = colorNode;
    else if( (normalNode = dynamic_cast< ZNormal* >(pChild)) != NULL)
        normal = normalNode;
    else
        pChild->print();

}

void ZIndexedFaceSet::action()
{
    if( coordIndex.isEmpty() || coord == NULL)
        return;

    glPushAttrib(GL_ENABLE_BIT);

    if (!solid)
    {
        glDisable(GL_CULL_FACE);
    }


    if(color)
    {
        glEnable(GL_COLOR_MATERIAL);
    }

    glFrontFace(ccw ? GL_CCW : GL_CW);

    try
    {
        ZVector3D v1, v2;
        int colorIndx = 0, normalIndx = 0;
        for(int i = 0; i < coordIndex.getNumElements(); ++i)
        {
            glBegin(GL_POLYGON);

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

            if(!normalPerVertex && normal)
            {
                if(!normalIndex.isEmpty())
                {
                    glNormal3dv(normal->getVector(normalIndex.getElement(normalIndx)).getVec());
                }
                else
                {
                    glNormal3dv(normal->getVector(normalIndx).getVec());
                }
                ++normalIndx;
            }
            else
            {
                // calculate normal
                if(i < coordIndex.getNumElements() - 2 &&
                        coordIndex.getElement(i) != -1 &&
                        coordIndex.getElement(i+1) != -1 &&
                        coordIndex.getElement(i+2) != -1)
                {
                    v1 = coord->getPoint(coordIndex.getElement(i+1)) - coord->getPoint(coordIndex.getElement(i));
                    v2 = coord->getPoint(coordIndex.getElement(i+2)) - coord->getPoint(coordIndex.getElement(i));

                    v1 = (v1*v2).normalize();
                    if (!ccw)
                         v1 = -v1;
                    glNormal3dv(v1.getVec());
                }
            }

            while(i < coordIndex.getNumElements() && coordIndex.getElement(i) != -1)
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

                if(normalPerVertex && normal)
                {
                    // no support normal per vertex
                    if(!normalIndex.isEmpty())
                    {
                        glNormal3dv(normal->getVector(normalIndex.getElement(i)).getVec());
                    }
                    else
                    {
                        glNormal3dv(normal->getVector(coordIndex.getElement(i)).getVec());
                    }
                }

                glVertex3dv(coord->getPoint(coordIndex.getElement(i)).getVec());
                ++i;
            }
            glEnd();
        }
    }
    catch(std::exception& ex)
    {
    	printf("IndexedFaceSet : %s", ex.what());
    }
            
    glEnable(GL_CULL_FACE);
    glDisable(GL_COLOR_MATERIAL);
    glFrontFace(GL_CCW);
    glPopAttrib();
}

void ZIndexedFaceSet::print()
{
    printf("ZIndexedFaceSet: %s\n", getName());

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
    printf("solid : %d\n", solid);
}

void ZIndexedFaceSet::addToBrowser(Browser* browser, Group* parent)
{
    Group *g, *root;
    char buffer[15];
    if(getName())
    {
        char name[256];
        snprintf(name,256,"IndexedFaceSet (%s)", getName());
        root = browser->add_group (name, parent, NULL);
    }
    else
    {
        root = browser->add_group ("IndexedFaceSet", parent, NULL);
        root->deactivate();
    }
    if(color != NULL)
    {
        color->addToBrowser(browser, root);
    }
    
    if(!colorIndex.isEmpty())
    {
        g = browser->add_group ("colorIndex", root, &colorIndexSize);
        for(int i = 0; i < zbp_colorIndex.getNumElements(); ++i)
        {
            snprintf(buffer, 15, "[%d]",i);
            browser->add_leaf (buffer, g, zbp_colorIndex.getElementRef(i));
        }
    }

    if(coord != NULL)
    {
        coord->addToBrowser(browser, root);
    }
    
    if(!coordIndex.isEmpty())
    {
        g = browser->add_group ("coordIndex", root, &coordIndexSize);
        for(int i = 0; i < zbp_coordIndex.getNumElements(); ++i)
        {
            snprintf(buffer, 15, "[%d]",i);
            browser->add_leaf (buffer, g, zbp_coordIndex.getElementRef(i));
        }
    }

    if(normal != NULL)
    {
        normal->addToBrowser(browser, root);
    }

    if(!normalIndex.isEmpty())
    {
        g = browser->add_group ("normalIndex", root, &normalIndexSize);
        for(int i = 0; i < zbp_normalIndex.getNumElements(); ++i)
        {
            snprintf(buffer, 15, "[%d]",i);
            browser->add_leaf (buffer, g, zbp_normalIndex.getElementRef(i));
        }
    }

    browser->add_leaf ("colorPerVertex", root, &zbp_colorPerVertex);
    browser->add_leaf ("normalPerVertex", root, &zbp_normalPerVertex);
    browser->add_leaf ("solid", root, &zbp_solid);
    browser->add_leaf ("ccw", root, &zbp_ccw);
}

