/* 
 * File:   Scene.h
 * Author: CuneyT
 *
 * Created on March 21, 2010, 1:57 PM
 */

#ifndef _SCENE_H
#define	_SCENE_H

#include <fltk/math.h>
#include <fltk/visual.h>
#include <fltk/events.h>

#include "ZString.h"
#include "vrmlparserstructs.h"
#include "Camera.h"

#include <iostream>
using namespace std;

class Scene  : public fltk::GlWindow
{
public:

    Scene(int x,int y,int w,int h,const char *l=0);

    ~Scene();

    bool addVRML(const char* filename);

    void removeVRML(const char* filename);

    void print();

    void setBrowser(Browser* browser);
   
    void nextCamera();
    void prevCamera();
    void resetCamera();

    void zoomIn();
    void zoomOut();

    void rotateViewUpDown(float angle);
    void rotateViewLeftRight(float angle);

    // This strafes the camera left or right depending on the speed (+/-)
    void strafeCamera(float speed);

    // This will move the camera forward or backward depending on the speed
    void moveCamera(float speed);

private:
    virtual int handle(int e);
    
    void calculateGluLookAt();

    void draw();

    void setCamera(ZViewpoint*);

    Array<ZString> vrmlFilePaths;
    Array< Array<ZVrmlNode *>* > vrmlNodes;
    Array< Array<ZViewpoint *>* > vrmlViewpoints;
    Array< Array<ZNavigationInfo *>* > vrmlNavigationInfo;

    bool defaultCamera;
    double scale;


    Array<ZViewpoint *> viewpoints;
    Array<ZNavigationInfo *> navigationInfos;

    ZViewpoint * currCamera;
    int currCameraVrmlFile;
    int currCameraIndex;
    
    Browser* vrmlBrowser;
    GLCamera camera;

    double x,y;
};

#endif	/* _SCENE_H */

