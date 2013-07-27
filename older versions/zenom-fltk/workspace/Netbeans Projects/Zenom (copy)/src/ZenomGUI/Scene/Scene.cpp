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
    currCamera = 0;
    mode(fltk::DOUBLE_BUFFER);
    rotateX = 0;
    rotateY = 0;
}

Scene::~Scene()
{
    unload();
}


void Scene::draw()
{
    if (!valid())
    {
        valid(1);

        glLoadIdentity();
        glViewport(0,0,w(),h());
        
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LEQUAL);

        glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
        glEnable(GL_NORMALIZE);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glEnable(GL_LIGHTING);
        //glEnable(GL_COLOR_MATERIAL);
        
        //glEnable(GL_LIGHT0);
    }

    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

    calculateGluLookAt();
 
    glPushMatrix();  
    glRotatef(rotateX, 1, 0, 0);
    glRotatef(rotateY, 0, 1, 0);
    
    for(int i = 0; i < nodes.getNumElements(); ++i)
        nodes.getElement(i)->action();

    glPopMatrix();

    swap_buffers();
}

void Scene::print()
{
    for(int i = 0; i < nodes.getNumElements(); ++i)
        nodes.getElement(i)->print();

    for(int i = 0; i < viewpoints.getNumElements(); ++i)
        cout << *viewpoints.getElement(i) << endl;
}

void Scene::unload()
{
    for(int i = 0; i < nodes.getNumElements(); ++i)
        delete nodes.getElement(i);
    nodes.removeAllElements();

    for(int i = 0; i < viewpoints.getNumElements(); ++i)
        delete viewpoints.getElement(i);
    viewpoints.removeAllElements();

    for(int i = 0; i < navigationInfos.getNumElements(); ++i)
        delete navigationInfos.getElement(i);
    navigationInfos.removeAllElements();

    currCamera = 0;
}

bool Scene::vrmlParse(const char* filename)
{
    unload();
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
    ZVrmlActions act(&nodes, &viewpoints, &navigationInfos);
    openvrml::null_vrml97_parse_actions c;

    vrml97_grammar<ZVrmlActions, ZVrmlParseError> g(act);

    //g.error_handler.getError();



    //BOOST_SPIRIT_DEBUG_NODE(skip_g);
    //BOOST_SPIRIT_DEBUG_NODE(g);

    if (!parse(first, last, g, skip_g).full)
    {
        cout << "ERRRORRR?" << g.error_handler.getError();
        return EXIT_FAILURE;    
    }
    cout << "ERRRORRR?" << g.error_handler.getError();

    // if no camera node in the file, append a default camera
    if( !viewpoints.getNumElements() )
    {
        viewpoints.appendElement(new ZViewpoint());
        printf("default camera active");
    }

    if( !navigationInfos.getNumElements() )
    {
        navigationInfos.appendElement(new ZNavigationInfo());
        printf("default navigation active");
    }
    return EXIT_SUCCESS;
}

//==============================================================================
// Scene::calculateGluLookAt
//==============================================================================
void Scene::calculateGluLookAt()
{
    // if no view point object, no gluLookAt
    if( !viewpoints.getNumElements() )
        return;
    
    const float zNear = 1.0;
    const float zFar = 20000.0;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    float fieldOfView = RAD2DEG(viewpoints.getElement(currCamera)->getFieldOfView());  
    gluPerspective(fieldOfView, 1.0f * w() / h(), zNear, zFar);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    viewpoints.getElement(currCamera)->action();
   

    if( !navigationInfos.getNumElements() )
        return;
    navigationInfos.getElement(0)->action();
}

//==============================================================================
// Scene::fillBrowser
//==============================================================================
void Scene::fillBrowser(Browser* browser)
{
    for(int i = 0; i < nodes.getNumElements(); ++i)
        nodes.getElement(i)->addToBrowser(browser, browser);
}

//==============================================================================
// Scene::moveForward
//==============================================================================
void Scene::moveForward()
{
    //offsetPos.setZ(offsetPos.getZ()-1.0f);
    redraw();
}

//==============================================================================
// Scene::moveBackward
//==============================================================================
void Scene::moveBackward()
{
    //offsetPos.setZ(offsetPos.getZ()+1.0f);
    redraw();
}

//==============================================================================
// Scene::moveLeft
//==============================================================================
void Scene::moveLeft()
{
    //offsetPos.setX(offsetPos.getX()+1.0f);
    redraw();
}

//==============================================================================
// Scene::rotateUp
//==============================================================================
void Scene::rotateUp()
{
    //offsetRotation.setZ(0);
    //offsetRotation.setZ(offsetRotation.getZ()-5.0f);
    //offsetRotation.setAngle(offsetRotation.getAngle()-5.0f);
    redraw();
}

//==============================================================================
// Scene::rotateDown
//==============================================================================
void Scene::rotateDown()
{
    //offsetRotation.setZ(offsetRotation.getZ()+5.0f);
    //offsetRotation.setAngle(offsetRotation.getAngle()+5.0f);
    redraw();
}

//==============================================================================
// Scene::rotateLeft
//==============================================================================
void Scene::rotateLeft()
{
    //offsetPos.setZ(offsetPos.getZ()+1.0f);
    redraw();
}

//==============================================================================
// Scene::rotateRight
//==============================================================================
void Scene::rotateRight()
{
    //offsetPos.setX(offsetPos.getX()+1.0f);
    redraw();
}

//==============================================================================
// Scene::moveRight
//==============================================================================
void Scene::moveRight()
{
    //offsetPos.setX(offsetPos.getX()-1.0f);
    redraw();
}


//==============================================================================
// Scene::changeHeadlight
//==============================================================================
void Scene::changeHeadlight()
{
    bool light = !navigationInfos.getElement(0)->getHeadlight();
    navigationInfos.getElement(0)->setHeadlight(light);
    redraw();
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
                case fltk::LeftKey:
                case 'a':
                case 'A':
                    moveRight();
                        break;
                case fltk::UpKey:
                case 'w':
                case 'W':
                    moveForward();
                        break;
                case fltk::RightKey:
                case 'd':
                case 'D':
                    moveLeft();
                        break;
                case fltk::DownKey:
                case 's':
                case 'S':
                    moveBackward();
                        break;

                default:
                    break;
            }
            break;

        case fltk::MOVE:
            //printf("MOVE");
            break;
    }

    return fltk::Window::handle(e);
}