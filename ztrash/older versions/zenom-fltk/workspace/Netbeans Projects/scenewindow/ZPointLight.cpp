/*
 * File:   ZPointLight.cpp
 * Author: root
 *
 * Created on May 3, 2010, 2:02 AM
 */

#include "ZPointLight.h"

ZPointLight::ZPointLight(const char * pName)
: ZVrmlNode(pName, NODE_POINT_LIGHT)
{
    ambientIntensity = 0;
    attenuation = ZVector3D(1.0, 0.0, 0.0);
    color = ZColor(1.0, 1.0, 1.0);
    intensity = 1;
    location = ZVector3D(0.0, 0.0, 0.0);
    on = true;
    radius = 100;

    zbp_ambientIntensity.type = Z_DOUBLE;
    zbp_ambientIntensity.variable = &ambientIntensity;
    zbp_intensity.type = Z_DOUBLE;
    zbp_intensity.variable = &intensity;
    zbp_on.type = Z_BOOLEAN;
    zbp_on.variable = &on;
    zbp_radius.type = Z_DOUBLE;
    zbp_radius.variable = &radius;

    light = -1;
}

ZPointLight::~ZPointLight()
{

}

ZPointLight::ZPointLight(const ZPointLight& pRight)
: ZVrmlNode(NULL, NODE_POINT_LIGHT)
{
    *this = pRight;
}

ZPointLight& ZPointLight::operator=(const ZPointLight& pRight)
{
    if( this != &pRight )
    {
        setName(pRight.getName());
        ambientIntensity = pRight.ambientIntensity;
        attenuation      = pRight.attenuation;
        color     = pRight.color;
        intensity = pRight.intensity;
        location  = pRight.location;
        on        = pRight.on;
        radius    = pRight.radius;


        zbp_ambientIntensity.type = Z_DOUBLE;
        zbp_ambientIntensity.variable = &ambientIntensity;
        zbp_intensity.type = Z_DOUBLE;
        zbp_intensity.variable = &intensity;
        zbp_on.type = Z_BOOLEAN;
        zbp_on.variable = &on;
        zbp_radius.type = Z_DOUBLE;
        zbp_radius.variable = &radius;

        light = -1;
    }
    return *this;
}

ZVrmlNode* ZPointLight::clone()
{
    ZPointLight* clone = new ZPointLight(*this);

    return dynamic_cast<ZVrmlNode*>(clone);
}

void ZPointLight::setField(const char* fieldName, ZAttribute& value)
{
    if( !strcmp(fieldName, "ambientIntensity") )
        setAmbientIntensity(value.vFloat);
    else if( !strcmp(fieldName, "attenuation") )
        setAttenuation(value.vZVector3D);
    else if( !strcmp(fieldName, "color") )
        setColor(value.vZColor);
    else if( !strcmp(fieldName, "intensity") )
        setIntensity(value.vFloat);
    else if( !strcmp(fieldName, "location") )
        setLocation(value.vZVector3D);
    else if( !strcmp(fieldName, "on") )
        setOn(value.vBool);
    else if( !strcmp(fieldName, "radius") )
        setRadius(value.vFloat);
}


void ZPointLight::action()
{
    if(on)
    {
        if(light == -1)
        {
            GLboolean lightOn;
            for(int i = 1; i < GL_MAX_LIGHTS; ++i)
            {
                glGetBooleanv(GL_LIGHT0 + i, &lightOn);
                if(!lightOn)
                {
                    light = GL_LIGHT0 + i;
                    break;
                }
            }

            if(light == -1)
                return;
        }

        glEnable(light);
    }
    else
    {
        if(light != -1)
        {
            glDisable(light);
            light = -1;
        }
        return;
    }


    float amb[4] = { ambientIntensity * color.getR(),
                     ambientIntensity * color.getG(),
                     ambientIntensity * color.getB(),
                     1.0 };
    float dif[4] = { intensity * color.getR(),
                     intensity * color.getG(),
                     intensity * color.getB(),
                     1.0 };
    float pos[4] = { location.getX(), location.getY(), location.getZ(), 1.0 };

    glLightfv(light, GL_AMBIENT, amb);
    glLightfv(light, GL_DIFFUSE, dif);
    glLightfv(light, GL_POSITION, pos);

    glLightf(light, GL_CONSTANT_ATTENUATION, attenuation.getX());
    glLightf(light, GL_LINEAR_ATTENUATION, attenuation.getY());
    glLightf(light, GL_QUADRATIC_ATTENUATION, attenuation.getZ());

    glLightf(light, GL_SPOT_CUTOFF, 180.0);
    glLightf(light, GL_SPOT_EXPONENT, 0.0);
}

void ZPointLight::print()
{
    printf("PointLight: %s\n", getName());
    printf("ambientIntensity %f\n", ambientIntensity);
    printf("attenuation "); attenuation.print(); printf("\n");
    printf("color "); color.print(); printf("\n");
    printf("intensity %f\n", intensity);
    printf("location "); location.print(); printf("\n");
    printf("on %f\n", on);
    printf("radius %f\n", radius);
}


void ZPointLight::addToBrowser(Browser* browser, Group* parent)
{
    Group* g, *root;
    if(getName())
    {
        char name[256];
        snprintf(name,256,"PointLight (%s)", getName());
        root = browser->add_group (name, parent, NULL);
    }
    else
    {
        root = browser->add_group ("PointLight", parent, NULL);
        root->deactivate();
    }
    browser->add_leaf ("ambientIntensity", root, &zbp_ambientIntensity);
    g = browser->add_group ("attenuation", root, &ZVector3DSize);
    attenuation.addToBrowser(browser, g);
    g = browser->add_group ("color", root, &ZColorSize);
    color.addToBrowser(browser, g);
    browser->add_leaf ("intensity", root, &zbp_intensity);
    g = browser->add_group ("location", root, &ZVector3DSize);
    location.addToBrowser(browser, g);
    browser->add_leaf ("on", root, &zbp_on);
    browser->add_leaf ("radius", root, &zbp_radius);
}



