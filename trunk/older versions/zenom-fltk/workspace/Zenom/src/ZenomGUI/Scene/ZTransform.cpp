/* 
 * File:   ZTransform.cpp
 * Author: CuneyT
 * 
 * Created on March 21, 2010, 2:15 PM
 */

#include "ZTransform.h"


ZTransform::ZTransform(const char *pName)
 : ZVrmlNode(pName, NODE_TRANSFORM)
{
    scale.setX(1);
    scale.setY(1);
    scale.setZ(1);

    bboxSize.setX(-1);
    bboxSize.setY(-1);
    bboxSize.setZ(-1);
}

ZTransform::ZTransform(const ZTransform& pRight) : ZVrmlNode(NULL, NODE_TRANSFORM)
{

    *this = pRight;
}

ZTransform::~ZTransform()
{
    for(int i = 0; i < children.getNumElements(); ++i)
        delete children.getElement(i);
}

ZTransform& ZTransform::operator=(const ZTransform& pRight)
{
    if( this != &pRight )
    {

        for(int i = 0; i < children.getNumElements(); ++i)
            delete children.getElement(i);
        children.removeAllElements();

        setName(pRight.getName());
        center = pRight.center;
        rotation = pRight.rotation;
        scale = pRight.scale;
        scaleOrientation = pRight.scaleOrientation;
        translation = pRight.translation;
        bboxCenter = pRight.bboxCenter;
        bboxSize = pRight.bboxSize;

        for(int i = 0; i < pRight.children.getNumElements(); ++i)
            children.appendElement(pRight.children.getElement(i)->clone());
    }

    return *this;
}

ZVrmlNode* ZTransform::clone()
{
    ZTransform* clone = new ZTransform(*this);

    return dynamic_cast<ZVrmlNode*>(clone);
}

void ZTransform::setField(const char* fieldName, ZAttribute& value)
{
    if( !strcmp(fieldName, "center") )
        setCenter(value.vZVector3D);
    else if( !strcmp(fieldName, "scale") )
        setScale(value.vZVector3D);
    else if( !strcmp(fieldName, "translation") )
        setTranslation(value.vZVector3D);
    else if( !strcmp(fieldName, "bboxCenter") )
        setBBoxCenter(value.vZVector3D);
    else if( !strcmp(fieldName, "bboxSize") )
        setBBoxSize(value.vZVector3D);
    else if( !strcmp(fieldName, "rotation") )
        setRotation(value.vZRotation);
    else if( !strcmp(fieldName, "scaleOrientation") )
        setScaleOrientation(value.vZRotation);
}


void ZTransform::action()
{

    glPushMatrix();

    
    glTranslated(translation.getX(), translation.getY(), translation.getZ());
    glTranslatef(center.getX(), center.getY(), center.getZ());
    glRotatef(rotation.angle, rotation.x, rotation.y, rotation.z);
    glRotatef(scaleOrientation.angle, scaleOrientation.x, scaleOrientation.y, scaleOrientation.z);
    glScalef(scale.getX(), scale.getY(), scale.getZ());
    glRotatef(-scaleOrientation.angle, scaleOrientation.x, scaleOrientation.y, scaleOrientation.z);
    glTranslatef(-center.getX(), -center.getY(), -center.getZ());
     

    for(int i = 0; i < children.getNumElements(); ++i)
        children.getElement(i)->action();

    glPopMatrix();

}

void ZTransform::addToBrowser(Browser* browser, Group* parent)
{
    Group* g, *root;
    if(getName())
    {
        char name[256];
        snprintf(name,256,"Transform (%s)", getName());
        root = browser->add_group (name, parent, NULL);
    }
    else
    {
        root = browser->add_group ("Transform", parent, NULL);
        root->deactivate();
    }
    g = browser->add_group ("center", root, &ZVector3DSize);
    center.addToBrowser(browser, g);
    g = browser->add_group ("rotation", root, &ZRotationSize);
    rotation.addToBrowser(browser, g);
    g = browser->add_group ("scale", root, &ZVector3DSize);
    scale.addToBrowser(browser, g);
    g = browser->add_group ("scaleOrientation", root, &ZRotationSize);
    scaleOrientation.addToBrowser(browser, g);
    g = browser->add_group ("translation", root, &ZVector3DSize);
    translation.addToBrowser(browser, g);

    for(int i = 0; i < children.getNumElements(); ++i)
        children.getElement(i)->addToBrowser(browser, root);
}

void ZTransform::print()
{
    printf("TRANSFORM: %s\n", getName());
    printf("center "); center.print();
    printf("scale "); scale.print();
    printf("translation "); translation.print();
    printf("rotation "); rotation.print();
    printf("scaleOrientation"); scaleOrientation.print();

    for(int i = 0; i < children.getNumElements(); ++i)
        children.getElement(i)->print();
}

