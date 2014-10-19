/* 
 * File:   ZDirectionalLight.h
 * Author: root
 *
 * Created on May 3, 2010, 2:02 AM
 */

#ifndef _ZDIRECTIONALLIGHT_H
#define	_ZDIRECTIONALLIGHT_H

#include <fltk/gl.h>

#include "utils.h"
#include "Array.h"
#include "ZVrmlNode.h"

class ZDirectionalLight : public ZVrmlNode
{
public:

    ZDirectionalLight(const char* = NULL);

    ~ZDirectionalLight();

    ZDirectionalLight(const ZDirectionalLight& pRight);

    ZDirectionalLight& operator=(const ZDirectionalLight& pRight);

    double getAmbientIntensity() { return ambientIntensity; }
    void setAmbientIntensity(double pAmbientIntensity) { ambientIntensity = pAmbientIntensity; }

    ZColor getColor() { return color; }
    void setColor(ZColor pColor) { color = pColor; }

    ZVector3D getDirection() { return direction; }
    void setDirection(ZVector3D pDirection) { direction = pDirection; }

    double getIntensity() { return intensity; }
    void setIntensity(double pIntensity) { intensity = pIntensity; }

    bool getOn() { return on; }
    void setOn(bool pOn) { on = pOn; }

    virtual ZVrmlNode* clone();

    virtual void setField(const char*, ZAttribute &);

    virtual void print();

    virtual void action();

    virtual void addToBrowser(Browser* browser, Group* parent);

private:

    double ambientIntensity;
    ZColor color;
    ZVector3D direction;
    double intensity;
    bool on;
    
    ZParameter zbp_ambientIntensity, zbp_intensity, zbp_on;

    int light;
};

#endif	/* _ZDIRECTIONALLIGHT_H */

