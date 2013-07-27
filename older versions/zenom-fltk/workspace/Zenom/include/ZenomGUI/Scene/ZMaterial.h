/* 
 * File:   ZMaterial.h
 * Author: root
 *
 * Created on March 25, 2010, 12:29 AM
 */

#ifndef _ZMATERIAL_H
#define	_ZMATERIAL_H

#include <fltk/gl.h>

#include "ZVrmlNode.h"
#include "Array.h"


class ZMaterial : public ZVrmlNode
{
public:
    
    ZMaterial(const char* = NULL);

    ~ZMaterial();

    ZMaterial(const ZMaterial& pRight);

    ZMaterial& operator=(const ZMaterial& pRight);

    double getAmbientIntensity() { return ambientIntensity; }
    void setAmbientIntensity(double pAmbientIntensity) { ambientIntensity = pAmbientIntensity; }

    ZColor getDiffuseColor() { return diffuseColor; }
    void setDiffuseColor(ZColor pDiffuseColor) { diffuseColor = pDiffuseColor; }

    ZColor getEmissiveColor() { return emissiveColor; }
    void setEmissiveColor(ZColor pEmissiveColor) { emissiveColor = pEmissiveColor; }

    double getShininess() { return shininess; }
    void setShininess(double pShininess) { shininess = pShininess; }

    ZColor getSpecularColor() { return specularColor; }
    void setSpecularColor(ZColor pSpecularColor) { specularColor = pSpecularColor; }

    double getTransparency() { return transparency; }
    void setTransparency(double pTransparency) { transparency = pTransparency; }

    virtual ZVrmlNode* clone();

    virtual void setField(const char*, ZAttribute &);

    virtual void print();

    virtual void action();

    virtual void addToBrowser(Browser* browser, Group* parent);

private:
    
    double ambientIntensity;
    ZColor diffuseColor;
    ZColor emissiveColor;
    double shininess;
    ZColor specularColor;
    double transparency;
    
    ZParameter zbp_ambientIntensity, zbp_shininess, zbp_transparency;

};

#endif	/* _ZMATERIAL_H */

