/* 
 * File:   Scene.cpp
 * Author: CuneyT
 * 
 * Created on March 21, 2010, 1:57 PM
 */

#include "Scene.h"

Scene::Scene(int x,int y,int w,int h,const char *l)
  : fltk::GlWindow(x,y,w,h,l)
{
    currCameraVrmlFile = 0;
    currCameraIndex = 0;
    mode(fltk::DOUBLE_BUFFER);
    scale = 1;

    x = 0;
    y = 0;
}

Scene::~Scene()
{
    for(int i = 0; i < vrmlFilePaths.getNumElements(); ++i)
    {
        for(int j = 0; j < vrmlNodes.getElement(i)->getNumElements(); ++j)
            delete vrmlNodes.getElement(i)->getElement(j);
        delete vrmlNodes.getElement(i);


        for(int j = 0; j < vrmlViewpoints.getElement(i)->getNumElements(); ++j)
            delete vrmlViewpoints.getElement(i)->getElement(j);
        delete vrmlViewpoints.getElement(i);


        for(int j = 0; j < vrmlNavigationInfo.getElement(i)->getNumElements(); ++j)
            delete vrmlNavigationInfo.getElement(i)->getElement(j);
        delete vrmlNavigationInfo.getElement(i);
    }

    vrmlFilePaths.removeAllElements();
    vrmlNodes.removeAllElements();
    vrmlViewpoints.removeAllElements();
    vrmlNavigationInfo.removeAllElements();
}

void Scene::setBrowser(Browser* browser)
{
    vrmlBrowser = browser;
}


void Scene::draw()
{
    if (!valid())
    {
        valid(1);

        //char *argv[] = {"foo"};
        //int argc = 1; // must/should match the number of strings in argv

        //glutInit(&argc, argv);


        glLoadIdentity();
        glViewport(0,0,w(),h());
        
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LEQUAL);

        glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
        glEnable(GL_NORMALIZE);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glEnable(GL_LIGHTING);

        //glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_NICEST);
	/*glEnable (GL_RESCALE_NORMAL);

        glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_FALSE);
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
        */
        //glEnable(GL_COLOR_MATERIAL);
        
        //glEnable(GL_LIGHT0);
    }

    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

    calculateGluLookAt();
 
    glPushMatrix();
    glScalef(scale,scale,scale);
    glRotatef(x, 1, 0, 0);
    glRotatef(y, 0, 1, 0);
    
    for(int i = 0; i < vrmlNodes.getNumElements(); ++i)
        for(int j = 0; j < vrmlNodes.getElement(i)->getNumElements(); ++j)
            vrmlNodes.getElement(i)->getElement(j)->action();

    glPopMatrix();

    swap_buffers();
}

void Scene::print()
{
    for(int i = 0; i < vrmlNodes.getNumElements(); ++i)
        for(int j = 0; j < vrmlNodes.getElement(i)->getNumElements(); ++j)
            vrmlNodes.getElement(i)->getElement(j)->print();

    for(int i = 0; i < viewpoints.getNumElements(); ++i)
        cout << *viewpoints.getElement(i) << endl;
}

bool Scene::addVRML(const char* filename)
{
    ifstream infile;
    infile.open(filename);
    if (!infile.is_open())
    {
        cout <<": could not open file" << endl;
        return EXIT_FAILURE;
    }


    istream & in(infile);

    typedef multi_pass<istreambuf_iterator<char> > multi_pass_iterator_t;
    typedef istream::char_type char_t;

    multi_pass_iterator_t
        in_begin(make_multi_pass(istreambuf_iterator<char_t>(in))),
        in_end(make_multi_pass(istreambuf_iterator<char_t>()));

    typedef position_iterator<multi_pass_iterator_t> iterator_t;

    iterator_t first(in_begin, in_end, filename), last;

    vrml97_skip_grammar skip_g;
    Array<ZVrmlNode *>* newNodes = new Array<ZVrmlNode *>();
    Array<ZViewpoint *>* newViewpoints = new Array<ZViewpoint *>();
    Array<ZNavigationInfo *>* newNavigation = new Array<ZNavigationInfo *>();
    ZVrmlActions act(newNodes, newViewpoints, newNavigation);
    //openvrml::null_vrml97_parse_actions c;

    vrml97_grammar<ZVrmlActions, ZVrmlParseError> g(act);

    //g.error_handler.getError();



    //BOOST_SPIRIT_DEBUG_NODE(skip_g);
    //BOOST_SPIRIT_DEBUG_NODE(g);

    if (!parse(first, last, g, skip_g).full)
    {
        // Error, de-allocate memory
        for(int i = 0; i < newNodes->getNumElements(); ++i)
            delete newNodes->getElement(i);
        delete newNodes;

        for(int i = 0; i < newViewpoints->getNumElements(); ++i)
            delete newViewpoints->getElement(i);
        delete newViewpoints;

        for(int i = 0; i < newNavigation->getNumElements(); ++i)
            delete newNavigation->getElement(i);
        delete newNavigation;
        
        cout << "ERRRORRR?" << g.error_handler.getError();
        return EXIT_FAILURE;    
    }
    cout << "ERRRORRR?" << g.error_handler.getError();


    ZString newVrmlFile;
    if(strrchr(filename,'/'))
    {
        newVrmlFile = &(strrchr(filename,'/')[1]);
    }
    else
    {
        newVrmlFile = filename;
    }
    
    vrmlFilePaths.appendElement(newVrmlFile);
    vrmlNodes.appendElement(newNodes);


    Group *vrmlRoot;
    vrmlRoot = vrmlBrowser->add_group (newVrmlFile.c_str(), vrmlBrowser, NULL);
    for(int i = 0; i < newNodes->getNumElements(); ++i)
        newNodes->getElement(i)->addToBrowser(vrmlBrowser, vrmlRoot);

    vrmlViewpoints.appendElement(newViewpoints);
    vrmlNavigationInfo.appendElement(newNavigation);
    

    // if no camera node in the file, append a default camera
    if( !newViewpoints->getNumElements() )
    {
        newViewpoints->appendElement(new ZViewpoint());
        printf("default camera active");
    }

    if( !newNavigation->getNumElements() )
    {
        newNavigation->appendElement(new ZNavigationInfo());
        printf("default navigation active");
    }

    setCamera(vrmlViewpoints.getElement(currCameraVrmlFile)->getElement(currCameraIndex));
    
    return EXIT_SUCCESS;
}

//==============================================================================
// Scene::unload
//==============================================================================
void Scene::removeVRML(const char* filename)
{
    for(int i = 0; i < vrmlFilePaths.getNumElements(); ++i)
    {
        if(vrmlFilePaths.getElement(i) == filename)
        {
            vrmlFilePaths.removeElement(i);

            for(int j = 0; j < vrmlNodes.getElement(i)->getNumElements(); ++j)
                delete vrmlNodes.getElement(i)->getElement(j);
            delete vrmlNodes.getElement(i);
            vrmlNodes.removeElement(i);
            
            for(int j = 0; j < vrmlViewpoints.getElement(i)->getNumElements(); ++j)
                delete vrmlViewpoints.getElement(i)->getElement(j);
            delete vrmlViewpoints.getElement(i);
            vrmlViewpoints.removeElement(i);
            
            for(int j = 0; j < vrmlNavigationInfo.getElement(i)->getNumElements(); ++j)
                delete vrmlNavigationInfo.getElement(i)->getElement(j);
            delete vrmlNavigationInfo.getElement(i);
            vrmlNavigationInfo.removeElement(i);

            break;
        }
    }    
}

//==============================================================================
// Scene::calculateGluLookAt
//==============================================================================
void Scene::calculateGluLookAt()
{
    // if no view point object, no gluLookAt
    if( !vrmlViewpoints.getNumElements() )
        return;
    
    const float zNear = 1.0;
    const float zFar = 20000.0;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    float fieldOfView = RAD2DEG(vrmlViewpoints.getElement(currCameraVrmlFile)->getElement(currCameraIndex)->getFieldOfView());
    gluPerspective(fieldOfView, 1.0f * w() / h(), zNear, zFar);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    camera.render();

    //viewpoints.getElement(currCamera)->action();
   

    if( !vrmlNavigationInfo.getNumElements() )
        return;
    vrmlNavigationInfo.getElement(0)->getElement(0)->action();
}

//==============================================================================
// Scene::handle
//==============================================================================
int Scene::handle(int e)
{

    switch(fltk::event())
    {
        case fltk::KEY:
            switch(fltk::event_key())
            {
                case 'w':
                case 'W':
                    moveCamera(1);
                    break;

                case 's':
                case 'S':
                    moveCamera(-1);
                    break;

                case 'a':
                case 'A':
                    strafeCamera(1);
                    break;

                case 'd':
                case 'D':
                    strafeCamera(-1);
                    break;
                    
                case fltk::LeftKey:
                    x -= 15;
                    //rotateViewLeftRight(1);
                    break;

                case fltk::RightKey:
                    //rotateViewLeftRight(-1);
                    x += 15;
                    break;

                case fltk::UpKey:
                    y += 15;
                    //rotateViewUpDown(1);
                    break;

                case fltk::DownKey:
                    y -= 15;
                    //rotateViewUpDown(-1);
                    break;

                case 'X':
                case 'x':
                case fltk::SubtractKey:
                    zoomOut();
                    break;

                case 'Z':
                case 'z':
                case fltk::AddKey:
                    zoomIn();
                    break;

                default:
                    break;
            }
            break;

        case fltk::PUSH:
            if( fltk::RightButton == fltk::event_button() )
            {
                fltk::warp_mouse(20, 20);


                //cursor(fltk::CURSOR_CROSS);
            }
            else if( fltk::LeftButton == fltk::event_button() )
            {
                //preMousePosX = fltk::event_x();
                //preMousePosY = fltk::event_y();
                //cursor(fltk::CURSOR_MOVE);
            }
            break;

        case fltk::MOVE:
            //printf("MOVE");
            break;
    }

    redraw();
    return fltk::Window::handle(e);
}

void Scene::zoomIn()
{
    scale = scale * 1.5;
    redraw();
}

void Scene::zoomOut()
{
    scale = scale / 1.5;
    redraw();
}

void Scene::rotateViewUpDown(float angle)
{
    camera.moveEyeUpDown(angle);
    redraw();
}

void Scene::rotateViewLeftRight(float angle)
{
    camera.moveEyeLeftRight(angle);
    redraw();
}

void Scene::strafeCamera(float speed)
{
    camera.moveEyeLeftRight(speed);
    redraw();
}


void Scene::moveCamera(float speed)
{
    camera.moveCameraFortBack(speed);
    redraw();
}

void Scene::nextCamera()
{
    if(vrmlViewpoints.getElement(currCameraVrmlFile)->getNumElements()-1 > currCameraIndex)
    {
        ++currCameraIndex;
        currCamera = vrmlViewpoints.getElement(currCameraVrmlFile)->getElement(currCameraIndex);
        setCamera(currCamera);
    }
    else
    {        
        if(vrmlViewpoints.getNumElements()-1 > currCameraVrmlFile)
        {
            currCameraIndex = 0;
            ++currCameraVrmlFile;
            currCamera = vrmlViewpoints.getElement(currCameraVrmlFile)->getElement(currCameraIndex);
            setCamera(currCamera);
        }      
    }
  

    redraw();
}

void Scene::prevCamera()
{
    if(0 < currCameraIndex)
    {
        --currCameraIndex;
        currCamera = vrmlViewpoints.getElement(currCameraVrmlFile)->getElement(currCameraIndex);
        setCamera(currCamera);
    }
    else
    {
        if(0 < currCameraVrmlFile)
        {
            currCameraIndex = vrmlViewpoints.getElement(currCameraVrmlFile)->getNumElements()-1;
            --currCameraVrmlFile;
            currCamera = vrmlViewpoints.getElement(currCameraVrmlFile)->getElement(currCameraIndex);
            setCamera(currCamera);
        }
    }
    redraw();
}

void Scene::resetCamera()
{
    camera.gotoInitialPos();
    redraw();
}

void Scene::setCamera(ZViewpoint* pCamera)
{
    Vector3D pos, target, up;

    const double s = sin(DEG2RAD(pCamera->getOrientation().getAngle()));
    const double c = cos(DEG2RAD(pCamera->getOrientation().getAngle()));
    const double t = 1.0 - c;
    const double distance = 20000.0 * 0.2;
    // Transform [0,0,1] by the orientation to determine sight line

    pos = Vector3D(pCamera->getPosition().getX(), pCamera->getPosition().getY(), pCamera->getPosition().getZ());
    target.X = t * pCamera->getOrientation().getX() * pCamera->getOrientation().getZ() + s * pCamera->getOrientation().getY();
    target.Y = t * pCamera->getOrientation().getY() * pCamera->getOrientation().getZ() - s * pCamera->getOrientation().getX();
    target.Z = t * pCamera->getOrientation().getZ() * pCamera->getOrientation().getZ() + c;

    // Move along that vector the specified distance away from position[]
    target.X = target.X * -distance + pCamera->getPosition().getX();
    target.Y = target.Y * -distance + pCamera->getPosition().getY();
    target.Z = target.Z * -distance + pCamera->getPosition().getZ();

    // Transform [0,1,0] by the orientation to determine up vector
    up.X = t * pCamera->getOrientation().getX() * pCamera->getOrientation().getY() - s * pCamera->getOrientation().getZ();
    up.Y = t * pCamera->getOrientation().getY() * pCamera->getOrientation().getY() + c;
    up.Z = t * pCamera->getOrientation().getY() * pCamera->getOrientation().getZ() + s * pCamera->getOrientation().getX();

    camera.setInitialParams(pos, target, up);
}
