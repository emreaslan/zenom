/* 
 * File:   ZMaterial.cpp
 * Author: root
 * 
 * Created on March 25, 2010, 12:28 AM
 */

#include "ZMaterial.h"

ZMaterial::ZMaterial(const char * pName) : ZVrmlNode(pName, NODE_MATERIAL)
{
    ambientIntensity = 0.2;
    diffuseColor = ZColor(0.8, 0.8, 0.8);
    emissiveColor = ZColor(0.0, 0.0, 0.0);
    shininess = 0.2;
    specularColor = ZColor(0.0, 0.0, 0.0);;
    transparency = 0;

    zbp_ambientIntensity.type = Z_DOUBLE;
    zbp_ambientIntensity.variable = &ambientIntensity;
    zbp_shininess.type = Z_DOUBLE;
    zbp_shininess.variable = &shininess;
    zbp_transparency.type = Z_DOUBLE;
    zbp_transparency.variable = &transparency;
}

ZMaterial::~ZMaterial()
{
    
}

ZMaterial::ZMaterial(const ZMaterial& pRight)
: ZVrmlNode(NULL, NODE_MATERIAL)
{
    *this = pRight;
}

ZMaterial& ZMaterial::operator=(const ZMaterial& pRight)
{
    if( this != &pRight )
    {
        setName(pRight.getName());
        ambientIntensity = pRight.ambientIntensity;
        diffuseColor     = pRight.diffuseColor;
        emissiveColor    = pRight.emissiveColor;
        shininess        = pRight.shininess;
        specularColor    = pRight.specularColor;
        transparency     = pRight.transparency;
        
        zbp_ambientIntensity.type = Z_DOUBLE;
        zbp_ambientIntensity.variable = &ambientIntensity;
        zbp_shininess.type = Z_DOUBLE;
        zbp_shininess.variable = &shininess;
        zbp_transparency.type = Z_DOUBLE;
        zbp_transparency.variable = &transparency;
    }
    return *this;
}

ZVrmlNode* ZMaterial::clone()
{
    ZMaterial* clone = new ZMaterial(*this);

    return dynamic_cast<ZVrmlNode*>(clone);
}

void ZMaterial::setField(const char* fieldName, ZAttribute& value)
{
    if( !strcmp(fieldName, "ambientIntensity") )
        setAmbientIntensity(value.vFloat);
    else if( !strcmp(fieldName, "diffuseColor") )
        setDiffuseColor(value.vZColor);
    else if( !strcmp(fieldName, "emissiveColor") )
        setEmissiveColor(value.vZColor);
    else if( !strcmp(fieldName, "shininess") )
        setShininess(value.vFloat);
    else if( !strcmp(fieldName, "specularColor") )
        setSpecularColor(value.vZColor);
    else if( !strcmp(fieldName, "transparency") )
        setTransparency(value.vFloat);
}


void ZMaterial::action()
{
    const float alpha = 1.0f - transparency;
    const float ambient[4] = { ambientIntensity * diffuseColor.getR(),
                               ambientIntensity * diffuseColor.getG(),
                               ambientIntensity * diffuseColor.getB(),
                               alpha };
    const float diffuse[4] = { diffuseColor.getR(),
                               diffuseColor.getG(),
                               diffuseColor.getB(),
                               alpha };
    const float emission[4] = { emissiveColor.getR(),
                                emissiveColor.getG(),
                                emissiveColor.getB(),
                                alpha };
    const float specular[4] = { specularColor.getR(),
                                specularColor.getG(),
                                specularColor.getB(),
                                alpha };

    if ( transparency > 0.0f)
    {
        glEnable(GL_BLEND);
    }

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emission);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess * 128);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
}

void ZMaterial::print()
{
    printf("MATERIAL: %s\n", getName());
    printf("ambientIntensity %f\n", ambientIntensity);
    printf("diffuseColor "); diffuseColor.print(); printf("\n");
    printf("emissiveColor "); emissiveColor.print(); printf("\n");
    printf("shininess %f\n", shininess);
    printf("specularColor "); specularColor.print(); printf("\n");
    printf("transparency %f\n", transparency);
}


void ZMaterial::addToBrowser(Browser* browser, Group* parent)
{
    
    Group* g, *root;
    if(getName())
    {
        char name[256];
        snprintf(name,256,"Material (%s)", getName());
        root = browser->add_group (name, parent, NULL);
    }
    else
    {
        root = browser->add_group ("Material", parent, NULL);
        root->deactivate();
    }
    
    browser->add_leaf ("ambientIntensity", root, &zbp_ambientIntensity);
    g = browser->add_group ("diffuseColor", root, &ZColorSize);
    diffuseColor.addToBrowser(browser, g);
    g = browser->add_group ("emissiveColor", root, &ZColorSize);
    emissiveColor.addToBrowser(browser, g);
    browser->add_leaf ("shininess", root, &zbp_shininess);
    g = browser->add_group ("specularColor", root, &ZColorSize);
    specularColor.addToBrowser(browser, g);
    browser->add_leaf ("transparency", root, &zbp_transparency);

}


