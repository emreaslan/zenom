/* 
 * File:   ZDirectionalLight.cpp
 * Author: root
 * 
 * Created on May 3, 2010, 2:02 AM
 */

#include "ZDirectionalLight.h"

ZDirectionalLight::ZDirectionalLight(const char * pName)
: ZVrmlNode(pName, NODE_DIRECTIONAL_LIGHT)
{
    ambientIntensity = 0;
    color = ZColor(1.0, 1.0, 1.0);
    direction = ZVector3D(0.0, 0.0, -1.0);
    intensity = 1;
    on = true;

    zbp_ambientIntensity.type = Z_DOUBLE;
    zbp_ambientIntensity.variable = &ambientIntensity;
    zbp_intensity.type = Z_DOUBLE;
    zbp_intensity.variable = &intensity;
    zbp_on.type = Z_BOOLEAN;
    zbp_on.variable = &on;

    light = -1;
}

ZDirectionalLight::~ZDirectionalLight()
{

}

ZDirectionalLight::ZDirectionalLight(const ZDirectionalLight& pRight)
: ZVrmlNode(NULL, NODE_DIRECTIONAL_LIGHT)
{
    *this = pRight;
}

ZDirectionalLight& ZDirectionalLight::operator=(const ZDirectionalLight& pRight)
{
    if( this != &pRight )
    {
        setName(pRight.getName());
        ambientIntensity = pRight.ambientIntensity;
        color     = pRight.color;
        direction = pRight.direction;
        intensity = pRight.intensity;
        on        = pRight.on;


        zbp_ambientIntensity.type = Z_DOUBLE;
        zbp_ambientIntensity.variable = &ambientIntensity;
        zbp_intensity.type = Z_DOUBLE;
        zbp_intensity.variable = &intensity;
        zbp_on.type = Z_BOOLEAN;
        zbp_on.variable = &on;

        light = -1;
    }
    return *this;
}

ZVrmlNode* ZDirectionalLight::clone()
{
    ZDirectionalLight* clone = new ZDirectionalLight(*this);

    return dynamic_cast<ZVrmlNode*>(clone);
}

void ZDirectionalLight::setField(const char* fieldName, ZAttribute& value)
{
    if( !strcmp(fieldName, "ambientIntensity") )
        setAmbientIntensity(value.vFloat);
    else if( !strcmp(fieldName, "color") )
        setColor(value.vZColor);
    else if( !strcmp(fieldName, "direction") )
        setDirection(value.vZVector3D);
    else if( !strcmp(fieldName, "intensity") )
        setIntensity(value.vFloat);
    else if( !strcmp(fieldName, "on") )
        setOn(value.vBool);
}


void ZDirectionalLight::action()
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
    float pos[4] = { direction.getX(), direction.getY(), -direction.getZ(), 0.0 };

    glLightfv(light, GL_AMBIENT, amb);
    glLightfv(light, GL_DIFFUSE, dif);
    glLightfv(light, GL_POSITION, pos);
    glLightfv(light, GL_SPECULAR, dif);

    glLightf(light, GL_CONSTANT_ATTENUATION, 1.0);
    glLightf(light, GL_LINEAR_ATTENUATION, 0.0);
    glLightf(light, GL_QUADRATIC_ATTENUATION, 0.0);

    glLightf(light, GL_SPOT_CUTOFF, 180.0);
    glLightf(light, GL_SPOT_EXPONENT, 0.0);
}

void ZDirectionalLight::print()
{
    printf("DirectionalLight: %s\n", getName());
    printf("ambientIntensity %f\n", ambientIntensity);
    printf("color "); color.print(); printf("\n");
    printf("direction "); direction.print(); printf("\n");
    printf("intensity %f\n", intensity);
    printf("on %d\n", on);
}


void ZDirectionalLight::addToBrowser(Browser* browser, Group* parent)
{
    Group* g, *root;
    if(getName())
    {
        char name[256];
        snprintf(name,256,"DirectionalLight (%s)", getName());
        root = browser->add_group (name, parent, NULL);
    }
    else
    {
        root = browser->add_group ("DirectionalLight", parent, NULL);
        root->deactivate();
    }
    browser->add_leaf ("ambientIntensity", root, &zbp_ambientIntensity);
    g = browser->add_group ("color", root, &ZColorSize);
    color.addToBrowser(browser, g);
    g = browser->add_group ("direction", root, &ZColorSize);
    direction.addToBrowser(browser, g);
    browser->add_leaf ("intensity", root, &zbp_intensity);
    browser->add_leaf ("on", root, &zbp_on);
}



