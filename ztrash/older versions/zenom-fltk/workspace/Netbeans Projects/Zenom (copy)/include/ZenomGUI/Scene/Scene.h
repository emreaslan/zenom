/* 
 * File:   Scene.h
 * Author: CuneyT
 *
 * Created on March 21, 2010, 1:57 PM
 */

#ifndef _SCENE_H
#define	_SCENE_H

#include <fltk/math.h>
#include <fltk/gl.h>
#include <fltk/GlWindow.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <fltk/visual.h>
#include <fltk/events.h>

#include "vrmlparserstructs.h"

#include <iostream>
using namespace std;

class Scene  : public fltk::GlWindow
{
public:

    Scene(int x,int y,int w,int h,const char *l=0);

    ~Scene();

    bool vrmlParse(const char* filename);

    void unload();

    void print();

    void fillBrowser(Browser* browser);

    void moveForward();
    void moveBackward();
    void moveLeft();
    void moveRight();

    void rotateUp();
    void rotateDown();
    void rotateLeft();
    void rotateRight();
    
    void changeHeadlight();
    bool getHeadlight() { return navigationInfos.getElement(0)->getHeadlight(); }


private:
    virtual int handle(int e);
    
    void calculateGluLookAt();

    void draw();

    Array<ZVrmlNode *> nodes;

    Array<ZViewpoint *> viewpoints;
    int currCamera;

    Array<ZNavigationInfo *> navigationInfos;

    double rotateX, rotateY;



};

#endif	/* _SCENE_H */

