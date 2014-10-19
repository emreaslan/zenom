/*
 * File:   ZPointLight.h
 * Author: root
 *
 * Created on May 3, 2010, 2:02 AM
 */

#ifndef _ZPOINTLIGHT_H
#define	_ZPOINTLIGHT_H

#include <fltk/gl.h>

#include "utils.h"
#include "Array.h"
#include "ZVrmlNode.h"

class ZPointLight : public ZVrmlNode
{
public:

    ZPointLight(const char* = NULL);

    ~ZPointLight();

    ZPointLight(const ZPointLight& pRight);

    ZPointLight& operator=(const ZPointLight& pRight);

    double getAmbientIntensity() { return ambientIntensity; }
    void setAmbientIntensity(double pAmbientIntensity) { ambientIntensity = pAmbientIntensity; }

    ZVector3D getAttenuation() { return attenuation; }
    void setAttenuation(ZVector3D pAttenuation) { attenuation = pAttenuation; }

    ZColor getColor() { return color; }
    void setColor(ZColor pColor) { color = pColor; }

    double getIntensity() { return intensity; }
    void setIntensity(double pIntensity) { intensity = pIntensity; }
    
    ZVector3D getLocation() { return location; }
    void setLocation(ZVector3D pLocation) { location = pLocation; }

    bool getOn() { return on; }
    void setOn(bool pOn) { on = pOn; }

    double getRadius() { return radius; }
    void setRadius(double pRadius) { radius = pRadius; }

    virtual ZVrmlNode* clone();

    virtual void setField(const char*, ZAttribute &);

    virtual void print();

    virtual void action();

    virtual void addToBrowser(Browser* browser, Group* parent);

private:

    double ambientIntensity;
    ZVector3D attenuation;
    ZColor color;    
    double intensity;
    ZVector3D location;
    bool on;
    double radius;

    ZParameter zbp_ambientIntensity, zbp_intensity, zbp_on, zbp_radius;

    int light;
};

#endif	/* _ZPOINTLIGHT_H */

