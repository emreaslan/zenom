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
    coordIndex = NULL;

    color = NULL;
    colorIndex = NULL;

    normalIndex = NULL;
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
    coordIndex = NULL;

    color = NULL;
    colorIndex = NULL;

    normalIndex = NULL;
    normal = NULL;

    *this = pRight;
}

ZIndexedFaceSet::~ZIndexedFaceSet()
{
    delete coordIndex;
    delete coord;
    zbp_coordIndex.deleteAllElements();

    delete colorIndex;
    delete color;
    zbp_colorIndex.deleteAllElements();

    delete normalIndex;
    delete normal;
    zbp_normalIndex.deleteAllElements();
}

ZIndexedFaceSet& ZIndexedFaceSet::operator=(const ZIndexedFaceSet& pRight)
{
    if( this != &pRight )
    {
        delete coord;
        delete color;

        delete normalIndex;
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


        if(pRight.normal)
            normal = new ZNormal(*pRight.normal);
        else
            normal = NULL;

        if(pRight.normalIndex)
        {
            Array<int>* normals = new Array<int>();
            for(int i = 0; i < pRight.normalIndex->getNumElements(); ++i)
                normals->appendElement(pRight.normalIndex->getElement(i));
            setNormalIndex(normals);
        }
        else
            setNormalIndex(NULL);
    }
    return *this;
}

void ZIndexedFaceSet::setCoordIndex(Array<int>* pCoordIndex)
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

void ZIndexedFaceSet::setColorIndex(Array<int>* pColorIndex)
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

void ZIndexedFaceSet::setNormalIndex(Array<int>* pNormalIndex)
{
    delete normalIndex;
    normalIndex = pNormalIndex;

    if(normalIndex)
    {
        zbp_normalIndex.deleteAllElements();
        for(int i = 0; i < normalIndex->getNumElements(); ++i)
        {
            zbp_normalIndex.appendElement(new ZParameter(Z_INTEGER, &(normalIndex->getElementRef(i))));
        }
        normalIndexSize = normalIndex->getNumElements();
    }
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
        setColorIndex(value.vIntegers);
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
    if( coordIndex == NULL || coord == NULL)
        return;

    glPushAttrib(GL_ENABLE_BIT);
    ZVector3D currCoord;
    ZColor currColor;
    ZVector3D currNormal;

    if (!solid)
    {
        glDisable(GL_CULL_FACE);
    }


    if(color)
        glEnable(GL_COLOR_MATERIAL);


    int color_index, normal_index;
    glFrontFace(ccw ? GL_CCW : GL_CW);
    int i,j;
    for(i = 0, j = 0; i < coordIndex->getNumElements(); ++i)
    {
        if (i == 0 || coordIndex->getElement(i) == -1)
        {
            if (i > 0)
                glEnd();
            
            if (i == coordIndex->getNumElements() - 1)
                break;

            glBegin(GL_POLYGON);

            if(colorIndex)
                color_index = (j < colorIndex->getNumElements())
                                         ? colorIndex->getElement(j)
                                         : j;
            else
                color_index = j;

            if (color && color_index < color->getSize() && !(colorPerVertex))
            {
                glColor3f(color->getColor(color_index).getR(), color->getColor(color_index).getG(), color->getColor(color_index).getB());
            }
            

            if (!normalPerVertex) {
                size_t i1 = (i == 0)
                       ? 0
                       : i + 1;
                if(normalIndex)
                    normal_index = (j < normalIndex->getNumElements())
                                          ? normalIndex->getElement(j)
                                          : j;
                else
                    normal_index = j;

                if (normal && normal_index < normal->getSize())
                {
                    glNormal3f(normal->getVector(normal_index).getX(), normal->getVector(normal_index).getY(),normal->getVector(normal_index).getZ());
                } else if (i < coordIndex->getNumElements() - 4
                    && coordIndex->getElement(i1) >= 0
                    && coordIndex->getElement(i1+1) >= 0
                    && coordIndex->getElement(i1+2) >= 0)
                {
                    ZVector3D v1 = coordIndex->getElement(i1+1) - coordIndex->getElement(i1+2);
                    ZVector3D v2 = coordIndex->getElement(i1+1) - coordIndex->getElement(i1+0);
                    v1 = (v1 * v2).normalize();

                    // Flip normal if primitiv-orientation is clockwise
                    if (!ccw)
                        v1 = -v1;
                    glNormal3f(v1.getX(), v1.getY(), v1.getZ());
                }
            }
            ++j;
        }
            
            if (coordIndex->getElement(i) >= 0)
            {
                // Per-vertex attributes
                if(colorIndex)
                    color_index = (i < colorIndex->getNumElements())
                                             ? colorIndex->getElement(i)
                                             : coordIndex->getElement(i);
                else
                    color_index = coordIndex->getElement(i);

                if (color && color_index < color->getSize()
                    && colorPerVertex) {
                    glColor3f(color->getColor(color_index).getR(), color->getColor(color_index).getG(), color->getColor(color_index).getB());
                }

                if (normalPerVertex)
                {
                    if(normalIndex)
                    normal_index = (i < normalIndex->getNumElements())
                                              ? normalIndex->getElement(i)
                                              : coordIndex->getElement(i);
                    else
                        normal_index = coordIndex->getElement(i);;
                        
                    if (normal && normal_index < normal->getSize()) {
                        glNormal3f(normal->getVector(normal_index).getX(), normal->getVector(normal_index).getY(),normal->getVector(normal_index).getZ());
                    } else {
                        ; // Generate per-vertex normal here...
                    }
                }

                ZVector3D v = coord->getPoint(coordIndex->getElement(i));                

                glVertex3f(v.getX(),v.getY(),v.getZ());
            }

        }

            if (i >= coordIndex->getNumElements()) {
                if (coordIndex->getElement(i - 1) >= 0) { glEnd(); }
            } else {
                if (coordIndex->getElement(i) >= 0) { glEnd(); }
            }

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
    printf("solid : %d\n", solid);
}

void ZIndexedFaceSet::addToBrowser(Browser* browser, Group* parent)
{
    Group *g, *root;
    char buffer[15];
    if(getName())
    {
        char* name = new char[256];
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
    
    if(colorIndex)
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
    
    if(coordIndex)
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

    if(normalIndex)
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

