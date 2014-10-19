/* 
 * File:   ZSpotLight.cpp
 * Author: root
 * 
 * Created on May 3, 2010, 4:55 AM
 */

#include "ZSpotLight.h"

ZSpotLight::ZSpotLight(const char * pName)
: ZVrmlNode(pName, NODE_SPOT_LIGHT)
{
    ambientIntensity = 0;
    attenuation = ZVector3D(1.0, 0.0, 0.0);
    beamWidth = 1.570796;
    color = ZColor(1.0, 1.0, 1.0);
    cutOffAngle = 0.785398;
    direction = ZVector3D(0.0, 0.0, -1.0);
    intensity = 1;
    location = ZVector3D(0.0, 0.0, 0.0);
    on = true;
    radius = 100;

    zbp_ambientIntensity.type = Z_DOUBLE;
    zbp_ambientIntensity.variable = &ambientIntensity;
    zbp_beamWidth.type = Z_DOUBLE;
    zbp_beamWidth.variable = &beamWidth;
    zbp_cutOffAngle.type = Z_DOUBLE;
    zbp_cutOffAngle.variable = &cutOffAngle;
    zbp_intensity.type = Z_DOUBLE;
    zbp_intensity.variable = &intensity;
    zbp_on.type = Z_BOOLEAN;
    zbp_on.variable = &on;
    zbp_radius.type = Z_DOUBLE;
    zbp_radius.variable = &radius;

    light = -1;
}

ZSpotLight::~ZSpotLight()
{

}

ZSpotLight::ZSpotLight(const ZSpotLight& pRight)
: ZVrmlNode(NULL, NODE_SPOT_LIGHT)
{
    *this = pRight;
}

ZSpotLight& ZSpotLight::operator=(const ZSpotLight& pRight)
{
    if( this != &pRight )
    {
        setName(pRight.getName());
        ambientIntensity = pRight.ambientIntensity;
        attenuation      = pRight.attenuation;
        beamWidth = pRight.beamWidth;
        color     = pRight.color;
        cutOffAngle = pRight.cutOffAngle;
        direction = pRight.direction;
        intensity = pRight.intensity;
        location  = pRight.location;
        on        = pRight.on;
        radius    = pRight.radius;


        zbp_ambientIntensity.type = Z_DOUBLE;
        zbp_ambientIntensity.variable = &ambientIntensity;
        zbp_beamWidth.type = Z_DOUBLE;
        zbp_beamWidth.variable = &beamWidth;
        zbp_cutOffAngle.type = Z_DOUBLE;
        zbp_cutOffAngle.variable = &cutOffAngle;
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

ZVrmlNode* ZSpotLight::clone()
{
    ZSpotLight* clone = new ZSpotLight(*this);

    return dynamic_cast<ZVrmlNode*>(clone);
}

void ZSpotLight::setField(const char* fieldName, ZAttribute& value)
{
    if( !strcmp(fieldName, "ambientIntensity") )
        setAmbientIntensity(value.vFloat);
    else if( !strcmp(fieldName, "attenuation") )
        setAttenuation(value.vZVector3D);
    else if( !strcmp(fieldName, "beamWidth") )
        setBeamWidth(value.vFloat);
    else if( !strcmp(fieldName, "color") )
        setColor(value.vZColor);
    else if( !strcmp(fieldName, "cutOffAngle") )
        setCutOffAngle(value.vFloat);
    else if( !strcmp(fieldName, "direction") )
        setDirection(value.vZVector3D);
    else if( !strcmp(fieldName, "intensity") )
        setIntensity(value.vFloat);
    else if( !strcmp(fieldName, "location") )
        setLocation(value.vZVector3D);
    else if( !strcmp(fieldName, "on") )
        setOn(value.vBool);
    else if( !strcmp(fieldName, "radius") )
        setRadius(value.vFloat);
}


void ZSpotLight::action()
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

    float dir[3] = { direction.getX(), direction.getY(), direction.getZ() };

    glLightfv(light, GL_AMBIENT, amb);
    glLightfv(light, GL_DIFFUSE, dif);
    glLightfv(light, GL_POSITION, pos);
    glLightfv(light, GL_SPECULAR, dif);

    glLightf(light, GL_CONSTANT_ATTENUATION, attenuation.getX());
    glLightf(light, GL_LINEAR_ATTENUATION, attenuation.getY());
    glLightf(light, GL_QUADRATIC_ATTENUATION, attenuation.getZ());

    glLightfv(light, GL_SPOT_DIRECTION, dir);
    glLightf(light, GL_SPOT_CUTOFF, GLfloat(cutOffAngle * 180.0 / PI));
    glLightf(light, GL_SPOT_EXPONENT, beamWidth < cutOffAngle ? 1.0f : 0.0f);
}

void ZSpotLight::print()
{
    printf("SpotLight: %s\n", getName());
    printf("ambientIntensity %f\n", ambientIntensity);
    printf("attenuation "); attenuation.print(); printf("\n");
    printf("beamWidth %f\n", beamWidth);
    printf("color "); color.print(); printf("\n");
    printf("cutOffAngle %f\n", cutOffAngle);
    printf("direction "); direction.print(); printf("\n");
    printf("intensity %f\n", intensity);
    printf("location "); location.print(); printf("\n");
    printf("on %d\n", on);
    printf("radius %f\n", radius);
}


void ZSpotLight::addToBrowser(Browser* browser, Group* parent)
{
    Group* g, *root;
    if(getName())
    {
        char name[256];
        snprintf(name,256,"SpotLight (%s)", getName());
        root = browser->add_group (name, parent, NULL);
    }
    else
    {
        root = browser->add_group ("SpotLight", parent, NULL);
        root->deactivate();
    }
    browser->add_leaf ("ambientIntensity", root, &zbp_ambientIntensity);
    g = browser->add_group ("attenuation", root, &ZVector3DSize);
    attenuation.addToBrowser(browser, g);
    browser->add_leaf ("beamWidth", root, &zbp_beamWidth);
    g = browser->add_group ("color", root, &ZColorSize);
    color.addToBrowser(browser, g);
    browser->add_leaf ("cutOffAngle", root, &zbp_cutOffAngle);
    g = browser->add_group ("direction", root, &ZVector3DSize);
    direction.addToBrowser(browser, g);
    browser->add_leaf ("intensity", root, &zbp_intensity);
    g = browser->add_group ("location", root, &ZVector3DSize);
    location.addToBrowser(browser, g);
    browser->add_leaf ("on", root, &zbp_on);
    browser->add_leaf ("radius", root, &zbp_radius);
}

