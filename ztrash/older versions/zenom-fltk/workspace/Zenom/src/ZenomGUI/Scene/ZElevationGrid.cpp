/* 
 * File:   ZElevationGrid.cpp
 * Author: root
 * 
 * Created on May 6, 2010, 10:06 AM
 */

#include "ZElevationGrid.h"

ZElevationGrid::ZElevationGrid(char* pName)
: ZGeometry(pName, NODE_ELEVATION_GRID)
{
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
    zbp_xDimension.type = Z_INTEGER;
    zbp_xDimension.variable = &xDimension;
    zbp_xSpacing.type = Z_DOUBLE;
    zbp_xSpacing.variable = &xSpacing;
    zbp_zDimension.type = Z_INTEGER;
    zbp_zDimension.variable = &zDimension;
    zbp_zSpacing.type = Z_DOUBLE;
    zbp_zSpacing.variable = &zSpacing;

    setNormalPerVertex(true);
    setColorPerVertex(true);
    setSolid(true);
    setCcw(true);
    setXDimension(0);
    setXSpacing(1.0);
    setZDimension(0);
    setZSpacing(1.0);
}

ZElevationGrid::ZElevationGrid(const ZElevationGrid& pRight)
: ZGeometry(NULL, NODE_ELEVATION_GRID)
{
    color = NULL;
    normal = NULL;
    
    *this = pRight;
}

ZElevationGrid::~ZElevationGrid()
{
    delete color;
    delete normal;
    zbp_height.deleteAllElements();
}

ZElevationGrid& ZElevationGrid::operator=(const ZElevationGrid& pRight)
{
    if( this != &pRight )
    {
        delete color;
        delete normal;

        setName(pRight.getName());
        colorPerVertex = pRight.colorPerVertex;
        solid = pRight.solid;
        normalPerVertex = pRight.normalPerVertex;
        ccw = pRight.ccw;
        xDimension = pRight.xDimension;
        xSpacing = pRight.xSpacing;
        zDimension = pRight.zDimension;
        zSpacing = pRight.zSpacing;

        zbp_normalPerVertex.type = Z_BOOLEAN;
        zbp_normalPerVertex.variable = &normalPerVertex;
        zbp_colorPerVertex.type = Z_BOOLEAN;
        zbp_colorPerVertex.variable = &colorPerVertex;
        zbp_solid.type = Z_BOOLEAN;
        zbp_solid.variable = &solid;
        zbp_ccw.type = Z_BOOLEAN;
        zbp_ccw.variable = &ccw;
        zbp_xDimension.type = Z_INTEGER;
        zbp_xDimension.variable = &xDimension;
        zbp_xSpacing.type = Z_DOUBLE;
        zbp_xSpacing.variable = &xSpacing;
        zbp_zDimension.type = Z_INTEGER;
        zbp_zDimension.variable = &zDimension;
        zbp_zSpacing.type = Z_DOUBLE;
        zbp_zSpacing.variable = &zSpacing;

        if(pRight.color)
            color = new ZColorNode(*pRight.color);
        else
            color = NULL;
        
        if(pRight.normal)
            normal = new ZNormal(*pRight.normal);
        else
            normal = NULL;

        setHeight(pRight.height);

    }
    return *this;
}

void ZElevationGrid::setHeight(const Array<double>& pHeight)
{
    height = pHeight;

    zbp_height.deleteAllElements();
    for(int i = 0; i < height.getNumElements(); ++i)
    {
        zbp_height.appendElement(new ZParameter(Z_DOUBLE, &(height.getElementRef(i))));
    }
    heightSize = height.getNumElements();
}

void ZElevationGrid::setSolid(bool pSolid)
{
    solid = pSolid;
}

ZVrmlNode* ZElevationGrid::clone()
{
    ZElevationGrid* clone = new ZElevationGrid(*this);

    return dynamic_cast<ZElevationGrid*>(clone);
}

void ZElevationGrid::setField(const char* fieldName, ZAttribute& value)
{
    if( !strcmp(fieldName, "zDimension") )
        setZDimension(value.vInt);
    else if( !strcmp(fieldName, "xDimension") )
        setXDimension(value.vInt);
    else if( !strcmp(fieldName, "zSpacing") )
        setZSpacing(value.vFloat);
    else if( !strcmp(fieldName, "xSpacing") )
        setXSpacing(value.vFloat);
    else if( !strcmp(fieldName, "colorPerVertex") )
        setColorPerVertex(value.vBool);
    else if( !strcmp(fieldName, "solid") )
        setSolid(value.vBool);
    else if( !strcmp(fieldName, "ccw") )
        setCcw(value.vBool);
    else if( !strcmp(fieldName, "normalPerVertex") )
        setNormalPerVertex(value.vBool);
    else if( !strcmp(fieldName, "height") )
        setHeight(value.vDoubles);
}

void ZElevationGrid::addChild(ZVrmlNode* pChild)
{
    ZColorNode* colorNode;
    ZNormal* normalNode;

    if( (colorNode = dynamic_cast< ZColorNode* >(pChild)) != NULL)
        color = colorNode;
    else if( (normalNode = dynamic_cast< ZNormal* >(pChild)) != NULL)
        normal = normalNode;
    else
        pChild->print();

}

void ZElevationGrid::action()
{
    if( height.isEmpty() )
        return;

    glPushAttrib(GL_ENABLE_BIT);
    
    if(color)
        glEnable(GL_COLOR_MATERIAL);

    if (!solid)
    {
        glDisable(GL_CULL_FACE);
    }

    glFrontFace(ccw ? GL_CCW : GL_CW);

    try
    {
        double y;
        ZVector3D v1, v2;
        for (int j = 0; j < zDimension-1; ++j)
        {
            for (int i = 0; i < xDimension-1; ++i)
            {

                glBegin(GL_QUADS);

                // --------------- Point 1  ---------------
                if(color)
                {
                    if(colorPerVertex)
                    {
                        glColor3dv(color->getColor(j * xDimension + i).getColor());
                    }
                    else
                    {
                        glColor3dv(color->getColor(j * (xDimension - 1) + i).getColor());
                    }
                }

                if(normal)
                {
                    if(normalPerVertex)
                    {
                        glNormal3dv(normal->getVector(j * xDimension + i).getVec());
                    }
                    else
                    {
                        glNormal3dv(normal->getVector(j * (xDimension - 1) + i).getVec());
                    }
                }
                else
                {
                    /*
                     * No support normal per vertex
                     */
                    y = height.getElement(j * xDimension + i + 1) - height.getElement(j * xDimension + i);
                    v1 = ZVector3D(xSpacing, y, 0);
                    y = height.getElement(j * xDimension + i + xDimension) - height.getElement(j * xDimension + i);
                    v2 = ZVector3D(0, y, zSpacing);
                    v1 = (v1*v2).normalize();
                    if (!ccw)
                         v1 = -v1;

                    glNormal3dv(v1.getVec());
                }
                y = height.getElement(j * xDimension + i);
                glVertex3f(xSpacing * i, y, zSpacing * j);

                // --------------- Point 2  ---------------
                if(colorPerVertex && color)
                {
                    glColor3dv(color->getColor(j * xDimension + i + 1).getColor());
                }

                if(normalPerVertex && normal)
                {
                    glNormal3dv(normal->getVector(j * xDimension + i + 1).getVec());
                }

                y = height.getElement(j * xDimension + i + 1);
                glVertex3f(xSpacing * (i + 1), y, zSpacing * j);

                // --------------- Point 3  ---------------
                if(colorPerVertex && color)
                {
                    glColor3dv(color->getColor((j + 1) * xDimension + i + 1).getColor());
                }

                if(normalPerVertex && normal)
                {
                    glNormal3dv(normal->getVector((j + 1) * xDimension + i + 1).getVec());
                }

                y = height.getElement((j + 1) * xDimension + i + 1);
                glVertex3f(xSpacing * (i + 1), y, zSpacing * (j + 1));

                // --------------- Point 4  ---------------
                if(colorPerVertex && color)
                {
                    glColor3dv(color->getColor((j + 1) * xDimension + i).getColor());
                }

                if(normalPerVertex && normal)
                {
                    glNormal3dv(normal->getVector((j + 1) * xDimension + i).getVec());
                }

                y = height.getElement((j + 1) * xDimension + i);
                glVertex3f(xSpacing * i, y, zSpacing * (j + 1));

                glEnd();
            }
        }
    }
    catch(std::exception& ex)
    {
    	printf("ElevationGrid : %s", ex.what());
    }

    glEnable(GL_CULL_FACE);
    glDisable(GL_COLOR_MATERIAL);
    glFrontFace(GL_CCW);
    glPopAttrib();
}

void ZElevationGrid::print()
{
    printf("ZElevationGrid: %s\n", getName());

    if(color != NULL)
        color->print();

    printf("height:\n");
    for(int i = 0; i < height.getNumElements(); ++i)
        printf("%f ", height.getElement(i));
    printf("\n");

    printf("zDimension : %d\n", zDimension);
    printf("zSpacing : %f\n", zSpacing);
    printf("xDimension : %d\n", xDimension);
    printf("xSpacing : %f\n", xSpacing);
    printf("colorPerVertex : %d\n", colorPerVertex);
    printf("solid : %d\n", solid);
}

void ZElevationGrid::addToBrowser(Browser* browser, Group* parent)
{
    
    Group *g, *root;
    char buffer[15];
    if(getName())
    {
        char name[256];
        snprintf(name,256,"ElevationGrid (%s)", getName());
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

    if(!height.isEmpty())
    {
        g = browser->add_group ("height", root, &heightSize);
        for(int i = 0; i < zbp_height.getNumElements(); ++i)
        {
            snprintf(buffer, 15, "[%d]",i);
            browser->add_leaf (buffer, g, zbp_height.getElementRef(i));
        }
    }

    if(normal != NULL)
    {
        normal->addToBrowser(browser, root);
    }

    browser->add_leaf ("xSpacing", root, &zbp_xSpacing);
    browser->add_leaf ("zSpacing", root, &zbp_zSpacing);
    browser->add_leaf ("colorPerVertex", root, &zbp_colorPerVertex);
    //browser->add_leaf ("normalPerVertex", root, &zbp_normalPerVertex);
    browser->add_leaf ("solid", root, &zbp_solid);
    browser->add_leaf ("ccw", root, &zbp_ccw);
    
}

