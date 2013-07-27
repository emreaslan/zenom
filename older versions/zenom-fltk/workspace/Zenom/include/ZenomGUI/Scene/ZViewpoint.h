/* 
 * File:   ZIndexedLineSet.h
 * Author: root
 *
 * Created on April 1, 2010, 12:56 AM
 */

#ifndef _ZVIEWPOINT_H
#define	_ZVIEWPOINT_H

#include "Array.h"
#include "utils.h"
#include "ZVrmlNode.h"

#include <fltk/gl.h>
#include <fltk/GlWindow.h>
#include <GL/gl.h>
#include <GL/glu.h>

class ZViewpoint : public ZVrmlNode
{
  
    friend ostream &operator<<( ostream &, const ZViewpoint & );

public:
    ZViewpoint(char* = NULL);

    ZViewpoint(const ZViewpoint& pRight);
    
    virtual ~ZViewpoint();

    ZViewpoint& operator=(const ZViewpoint& pRight);

    void setFieldOfView(float);
    float getFieldOfView() { return fieldOfView; }

    void setJump(bool);
    bool getJump() { return jump; }

    void setOrientation(ZRotation);
    ZRotation getOrientation() { return orientation; }

    void setPosition(ZVector3D);
    ZVector3D getPosition() { return position; }

    void setDescription(const char*);
    const char* getDescription() { return description.c_str(); }

    virtual ZVrmlNode* clone();

    virtual void setField(const char*, ZAttribute &);

    virtual void action();

    virtual void addToBrowser(Browser* browser, Group* parent);
    
    virtual void print();



private:

    void move();

    float fieldOfView;
    bool jump;
    ZRotation orientation;
    ZVector3D position;
    ZString description;

    ZVector3D target;
    ZVector3D up;

    ZVector3D offsetPos;
    ZRotation offsetRotation;
};
 



#endif	/* _ZVIEWPOINT_H */

