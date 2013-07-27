/* 
 * File:   ZElevationGrid.h
 * Author: root
 *
 * Created on May 6, 2010, 10:06 AM
 */

#ifndef _ZELEVATIONGRID_H
#define	_ZELEVATIONGRID_H

#include "Array.h"
#include "utils.h"
#include "ZGeometry.h"

#include "ZColorNode.h"
#include "ZNormal.h"

class ZElevationGrid : public ZGeometry
{

public:
    ZElevationGrid(char* = NULL);

    ZElevationGrid(const ZElevationGrid& pRight);

    ~ZElevationGrid();

    ZElevationGrid& operator=(const ZElevationGrid& pRight);

    void setHeight(Array<double>*);
    Array<double>* getHeight() { return height; }

    void setXDimension(int pXDimension) { xDimension = pXDimension; }
    int getXDimension() { return xDimension; }

    void setXSpacing(double pXSpacing) { xSpacing = pXSpacing; }
    double getXSpacing() { return xSpacing; }

    void setZDimension(int pZDimension) { zDimension = pZDimension; }
    int getZDimension() { return zDimension; }

    void setZSpacing(double pZSpacing) { zSpacing = pZSpacing; }
    double getZSpacing() { return zSpacing; }

    void setColorPerVertex(bool pColorPerVertex) { colorPerVertex = pColorPerVertex; }
    bool getColorPerVertex() { return colorPerVertex; }

    void setSolid(bool pSolid);
    bool getSolid() { return solid; }

    void setCcw(bool pccw) { ccw = pccw; }
    bool getCcw() { return ccw; }

    void setNormalPerVertex(bool pNormalPerVertex) { normalPerVertex = pNormalPerVertex; }
    bool getNormalPerVertex() { return normalPerVertex; }

    virtual void addChild(ZVrmlNode*);

    virtual ZVrmlNode* clone();

    virtual void setField(const char*, ZAttribute &);

    virtual void action();

    void print();

    virtual void addToBrowser(Browser* browser, Group* parent);

private:

    ZVector3D calculateNormal(int i, int j);

    ZColorNode* color;
    ZNormal* normal;

    Array<double>* height;
    Array<ZParameter*> zbp_height;
    int heightSize;

    bool ccw;
    ZParameter zbp_ccw;
    bool colorPerVertex;
    ZParameter zbp_colorPerVertex;

    bool normalPerVertex;
    ZParameter zbp_normalPerVertex;
    bool solid;
    ZParameter zbp_solid;

    int xDimension;
    ZParameter zbp_xDimension;
    double xSpacing;
    ZParameter zbp_xSpacing;

    int zDimension;
    ZParameter zbp_zDimension;
    double zSpacing;
    ZParameter zbp_zSpacing;
};


#endif	/* _ZELEVATIONGRID_H */

