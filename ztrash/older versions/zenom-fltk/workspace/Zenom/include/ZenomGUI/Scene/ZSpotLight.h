/* 
 * File:   ZSpotLight.h
 * Author: root
 *
 * Created on May 3, 2010, 4:55 AM
 */

#ifndef _ZSPOTLIGHT_H
#define	_ZSPOTLIGHT_H

#include <fltk/gl.h>

#include "utils.h"
#include "Array.h"
#include "ZVrmlNode.h"

class ZSpotLight : public ZVrmlNode
{
public:

    ZSpotLight(const char* = NULL);

    ~ZSpotLight();

    ZSpotLight(const ZSpotLight& pRight);

    ZSpotLight& operator=(const ZSpotLight& pRight);

    double getAmbientIntensity() { return ambientIntensity; }
    void setAmbientIntensity(double pAmbientIntensity) { ambientIntensity = pAmbientIntensity; }

    ZVector3D getAttenuation() { return attenuation; }
    void setAttenuation(ZVector3D pAttenuation) { attenuation = pAttenuation; }

    double getBeamWidth() { return beamWidth; }
    void setBeamWidth(double pBeamWidth) { beamWidth = pBeamWidth; }

    ZColor getColor() { return color; }
    void setColor(ZColor pColor) { color = pColor; }

    double getCutOffAngle() { return cutOffAngle; }
    void setCutOffAngle(double pCutOffAngle) { cutOffAngle = pCutOffAngle; }

    ZVector3D getDirection() { return direction; }
    void setDirection(ZVector3D pDirection) { direction = pDirection; }

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
    double beamWidth;
    ZColor color;
    double cutOffAngle;
    ZVector3D direction;
    double intensity;
    ZVector3D location;
    bool on;
    double radius;

    ZParameter zbp_ambientIntensity, zbp_beamWidth, zbp_cutOffAngle, zbp_intensity, zbp_on, zbp_radius;

    int light;
};


#endif	/* _ZSPOTLIGHT_H */

