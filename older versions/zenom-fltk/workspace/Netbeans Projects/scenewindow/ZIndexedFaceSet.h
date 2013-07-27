/* 
 * File:   ZIndexedFaceSet.h
 * Author: root
 *
 * Created on April 1, 2010, 5:50 PM
 */

#ifndef _ZINDEXEDFACESET_H
#define	_ZINDEXEDFACESET_H

#include "Array.h"
#include "utils.h"
#include "ZGeometry.h"

#include "ZCoordinate.h"
#include "ZColorNode.h"
#include "ZNormal.h"

class ZIndexedFaceSet : public ZGeometry
{

public:
    ZIndexedFaceSet(char* = NULL);

    ZIndexedFaceSet(const ZIndexedFaceSet& pRight);

    ~ZIndexedFaceSet();

    ZIndexedFaceSet& operator=(const ZIndexedFaceSet& pRight);

    void setCoordIndex(Array<int>*);
    Array<int>* getCoordIndex() { return coordIndex; }

    void setColorIndex(Array<int>*);
    Array<int>* getColorIndex() { return colorIndex; }

    void setNormalIndex(Array<int>*);
    Array<int>* getNormalIndex() { return normalIndex; }

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
    ZCoordinate* coord;
    Array<int>* coordIndex;
    Array<ZParameter*> zbp_coordIndex;
    int coordIndexSize;

    ZColorNode* color;
    Array<int>* colorIndex;
    Array<ZParameter*> zbp_colorIndex;
    int colorIndexSize;

    ZNormal* normal;
    Array<int>* normalIndex;
    Array<ZParameter*> zbp_normalIndex;
    int normalIndexSize;

    bool normalPerVertex;
    ZParameter zbp_normalPerVertex;
    bool colorPerVertex;
    ZParameter zbp_colorPerVertex;
    bool solid;
    ZParameter zbp_solid;
    bool ccw;
    ZParameter zbp_ccw;
};

#endif	/* _ZINDEXEDFACESET_H */

