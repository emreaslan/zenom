/* 
 * File:   ZIndexedLineSet.h
 * Author: root
 *
 * Created on April 1, 2010, 12:56 AM
 */

#ifndef _ZINDEXEDLINESET_H
#define	_ZINDEXEDLINESET_H



#include "Array.h"
#include "utils.h"
#include "ZGeometry.h"

#include "ZCoordinate.h"
#include "ZColorNode.h"

class ZIndexedLineSet : public ZGeometry
{
public:
    ZIndexedLineSet(char* = NULL);

    ZIndexedLineSet(const ZIndexedLineSet& pRight);
    
    ~ZIndexedLineSet();

    ZIndexedLineSet& operator=(const ZIndexedLineSet& pRight);

    void setCoordIndex(const Array<int>&);
    Array<int>& getCoordIndex() { return coordIndex; }

    void setColorIndex(const Array<int>&);
    Array<int>& getColorIndex() { return colorIndex; }

    void setColorPerVertex(bool pColorPerVertex) { colorPerVertex = pColorPerVertex; }
    bool getColorPerVertex() { return colorPerVertex; }

    virtual void addChild(ZVrmlNode*);

    virtual ZVrmlNode* clone();
    
    virtual void setField(const char*, ZAttribute &);

    virtual void action();

    virtual void addToBrowser(Browser* browser, Group* parent);

    void print();

private:
    ZCoordinate* coord;
    Array<int> coordIndex;
    Array<ZParameter*> zbp_coordIndex;
    int coordIndexSize;

    ZColorNode* color;
    Array<int> colorIndex;
    Array<ZParameter*> zbp_colorIndex;
    int colorIndexSize;

    bool colorPerVertex;
    ZParameter zbp_colorPerVertex;
};
 



#endif	/* _ZINDEXEDLINESET_H */

