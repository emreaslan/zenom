/*
 * File:   PlotBaseWindow.cpp
 * Author: root
 *
 * Created on September 4, 2009, 1:36 PM
 */

#include "SceneWindow.h"


SceneWindow::SceneWindow( Array<LogVariableGUI*>& logVars )
 : Window( 670, 655, "Scene Window" ), LogVariablesGUI(logVars)
{

    this->begin();
    color(fltk::color(167,162,178));
    gbox  = new Group(5, 5, w()-10, h()-10);
    gbox->box(fltk::EMBOSSED_BOX);
    gbox->begin();



    //  ----- Menu -----
    menu = new MenuBar( 0, 0, w()-10, 25);
    menu->box( fltk::EMBOSSED_BOX );
    menu->begin();

    loadVrmlItemGroup = new ItemGroup("Load Vrml");
    loadVrmlItemGroup->box(fltk::PLASTIC_UP_BOX);
    loadVrmlItemGroup->color(fltk::GRAY90);

    loadVrmlItemGroup->begin();
    loadVrmlItemGroup->add("Add", CTRL + 'A', cbAdd, this);
    loadVrmlItemGroup->add("Remove", CTRL + 'R', cbRemove, this );
    loadVrmlItemGroup->end();

    bindButton = new Button(70,0,60,23,"Bind");
    bindButton->box(fltk::PLASTIC_UP_BOX);
    bindButton->color(fltk::GRAY70);
    bindButton->highlight_color(fltk::GRAY60);
    bindButton->callback(cbBind, this);
    menu->end();
    //  --- Menu ---

    packedGroup = new PackedGroup(10, 30, 640, 585);
    packedGroup->color(fltk::BLUE);
    packedGroup->begin();

    /*********************************************/
    //             OPENGL SCENE                  //
    scene = new Scene(0, 0, 640, 480);

    buttonGroup = new BarGroup(0, 490, 640, 105);
    buttonGroup->box(fltk::PLASTIC_UP_BOX);
    //buttonGroup->color(fltk::BLUE);
    buttonGroup->callback(this->cbOpenNavigationArea, this);
    buttonGroup->begin();

    //  ----- Navigate -----
    navigateGroup = new Group(175, 20, 135, 65,"Navigation");
    navigateGroup->box(fltk::BORDER_BOX);
    //navigateGroup->color(fltk::GRAY80);
    navigateGroup->begin();
    panButton = new ZButton(5,5,25,25,"@b;P");
    panButton->button()->callback(cbChangeMode, this);
    panButton->button()->tooltip("Pan");
    rotateButton = new ZButton(5,35,25,25,"@b;R");
    rotateButton->button()->callback(cbChangeMode, this);
    rotateButton->button()->tooltip("Rotate");
    
    upButton = new ZButton(75,5,25,25,"@y-5;@b;@s+7;^");
    upButton->button()->callback(cbNavigate, this);
    leftButton = new ZButton(45,23,25,25,"@s+8;<");
    leftButton->button()->callback(cbNavigate, this);
    rightButton = new ZButton(105,23,25,25,"@s+8;>");
    rightButton->button()->callback(cbNavigate, this);
    downButton = new ZButton(75,35,25,25,"@b;@s+2;v");
    downButton->button()->callback(cbNavigate, this);
    
    navigateGroup->end();
    //  --- Navigate ---

    //  ----- Zoom -----
    zoomGroup = new Group(320, 20, 35, 65, "Zoom");
    zoomGroup->box(fltk::BORDER_BOX);
    zoomGroup->begin();
    zoomInButton = new ZButton(5, 5,25,25,"@s+8;+");
    zoomInButton->button()->callback(cbZoom, this);
    zoomInButton->button()->tooltip("Zoom In");
    zoomOutButton = new ZButton(5,35,25,25,"@s+8;-");
    zoomOutButton->button()->callback(cbZoom, this);
    zoomOutButton->button()->tooltip("Zoom Out");
    zoomGroup->end();
    //  ----- Zoom -----

    //  ----- Camera -----
    cameraGroup = new Group(370,38, 95, 35, "Viewpoint");
    cameraGroup->box(fltk::BORDER_BOX);
    //cameraGroup->color(fltk::GRAY80);
    cameraGroup->begin();
    prevCameraButton = new ZButton(5, 5,25,25,"@<<");
    prevCameraButton->button()->callback(cbChangeCamera, this);
    prevCameraButton->button()->tooltip("Previous Viewpoint");
    resetCameraButton = new ZButton(35,5,25,25,"@s-4;@square");
    resetCameraButton->button()->callback(cbChangeCamera, this);
    resetCameraButton->button()->tooltip("Reset Viewpoint");
    nextCameraButton = new ZButton(65, 5,25,25,"@>>");
    nextCameraButton->button()->callback(cbChangeCamera, this);
    nextCameraButton->button()->tooltip("Next Viewpoint");
    cameraGroup->end();
    //  ----- Camera -----
    
    buttonGroup->end();
    buttonGroup->resizable(buttonGroup);
    packedGroup->end();

    statusBar = new StatusBarGroup(0,0,10,20);
    statusBar->label("Hüsnü bitir bunu yarına kadar");
    
    gbox->end();
    this->end();
 

    packedGroup->resizable(scene);
    gbox->resizable(packedGroup);
    resizable(gbox);
    

    //  ----- Scene Bind Window -----
    const char *vrmlLabels[] = {"Vrml Objects", "Log Variables",  0};
    const char *logLabels[] = {"Log Variables", 0};
    int bindedWidths[]   = {400, 120, 0};

    sceneBindWindow = new Window( 800, 280, "Scene Bind");
    sceneBindWindow->color(fltk::color(167,162,178));
    sceneBindWindow->begin();

    gboxSelect  = new Group(5, 5, sceneBindWindow->w()-10, sceneBindWindow->h()-10);
    gboxSelect->box(fltk::EMBOSSED_BOX);

    vrmlVariableList = new Browser(10, 10, 525, sceneBindWindow->h()-50);
    vrmlVariableList->column_labels(vrmlLabels);
    vrmlVariableList->indented(1);
    vrmlVariableList->callback(cbChangedVrmlList, this);
    vrmlVariableList->when(fltk::WHEN_CHANGED);
    vrmlVariableList->column_widths(bindedWidths);

    logVariableList = new Browser(620, 10, 170, sceneBindWindow->h()-50);
    logVariableList->column_labels(logLabels);
    logVariableList->indented(1);
    logVariableList->when(fltk::WHEN_CHANGED);

    bindVariableButton = new ZButton(540, 60, 75, 22, "Bind");
    bindVariableButton->button()->callback((Callback*)this->cbBindVariable,this);

    unbindVariableButton = new ZButton(540, 90, 75, 22, "Unbind");
    unbindVariableButton->button()->callback((Callback*)this->cbUnbindVariable,this);

    unbindAllVariableButton = new ZButton(540, 120, 75, 22, "Unbind All");
    unbindAllVariableButton->button()->callback((Callback*)this->cbUnbindAllVariable,this);

    oKBindButton = new ZButton(330, 245, 65, 22, "OK");
    oKBindButton->button()->callback((Callback*)this->cbOkBindVariable,this);

    cancelBindButton = new ZButton(400, 245, 65, 22, "Cancel");
    cancelBindButton->button()->callback((Callback*)this->cbCancelBindVariable,this);

    sceneBindWindow->end();
    sceneBindWindow->set_modal();

    sceneBindWindow->hide();
    sceneBindWindow->resizable(vrmlVariableList);
    //  ----- Scene Bind Window -----


    //  ----- VRML Remove Window -----
    removeVrmlFileWindow = new Window(270,230,"Select a vrml file :");
    removeVrmlFileWindow->begin();
    vrmlFileList = new MultiBrowser(10, 10, 250, 180);

    removeVRMLButton = new ZButton(10, 200, 80, 22, "Remove");
    removeVRMLButton->button()->callback((Callback*)this->cbRemoveVRMLButton,this);
    removeAllVRMLButton = new ZButton(95, 200, 80, 22, "Remove All");
    removeAllVRMLButton->button()->callback((Callback*)this->cbRemoveAllVRMLButton,this);
    vrmlFileCancelButton = new ZButton(180, 200, 80, 22, "Cancel");
    vrmlFileCancelButton->button()->callback((Callback*)this->cbVrmlFileCancelButton,this);

    removeVrmlFileWindow->resizable(vrmlFileList);
    removeVrmlFileWindow->end();
    removeVrmlFileWindow->set_modal();
    //  ----- VRML Remove Window -----

    fillLogVariableList();
    disableButtons();
    scene->setBrowser(vrmlVariableList);
}

//==============================================================================
// SceneWindow::~SceneWindow
//==============================================================================
SceneWindow::~SceneWindow()
{

    //  ----- VRML Remove Window -----
    delete vrmlFileList;
    delete removeVRMLButton;
    delete removeAllVRMLButton;
    delete vrmlFileCancelButton;
    delete removeVrmlFileWindow;

    //  ----- Scene Bind Window -----
    delete gboxSelect;
    delete vrmlVariableList;
    delete logVariableList;
    delete bindVariableButton;
    delete unbindVariableButton;
    delete unbindAllVariableButton;
    delete oKBindButton;
    delete cancelBindButton;
    delete sceneBindWindow;

    //  --- Menu ---
    delete loadVrmlItemGroup;
    delete bindButton;
    delete menu;

    //  ----- Navigate -----
    delete upButton;
    delete leftButton;    
    delete rightButton;
    delete downButton;
    delete rotateButton;
    delete panButton;
    delete navigateGroup;

    //  ----- Zoom -----
    delete zoomInButton;
    delete zoomOutButton;
    delete zoomGroup;

    //  ----- Camera -----
    delete nextCameraButton;
    delete resetCameraButton;
    delete prevCameraButton;
    delete cameraGroup;

    delete scene;
    delete buttonGroup;
    delete packedGroup;
    delete statusBar;
    delete gbox;
}

//==============================================================================
// SceneWindow::update
//==============================================================================
void SceneWindow::update()
{    
    LogVariableGUI *logVariable;
    ZParameter* vrmlVariable;
    int index;

    for(int i = 0; i < bindedVariable.getNumElements(); ++i)
    {
        logVariable  = bindedVariable.getElement(i)->logVariable;
        index = bindedVariable.getElement(i)->index;
        vrmlVariable = static_cast<ZParameter*>(bindedVariable.getElement(i)->vrmlVariableWidget->user_data());

        switch(vrmlVariable->type)
        {
            case Z_DOUBLE:
            {
                double *dtarget = static_cast<double*>(vrmlVariable->variable);
                //(*dtarget) = 10;
                (*dtarget) = logVariable->getLastHeapElement(index);
                break;
            }
            case Z_INTEGER:
            {
                int *itarget = static_cast<int*>(vrmlVariable->variable);
                //(*itarget) = 10;
                (*itarget) = static_cast<int>(logVariable->getLastHeapElement(index));
                break;
            }
            case Z_BOOLEAN:
            {
                bool *btarget = static_cast<bool*>(vrmlVariable->variable);
                //(*btarget) = false;
                (*btarget) = static_cast<bool>(logVariable->getLastHeapElement(index));
                break;
            }
        }
    }
    
}

//==============================================================================
// SceneWindow::enableButtons
//==============================================================================
void SceneWindow::enableButtons()
{
    buttonGroup->opened(true);
    cbOpenNavigationArea(buttonGroup, this);
    buttonGroup->activate();
    panButton->button()->color(fltk::BLUE);
    isPanMode = true;

}

//==============================================================================
// SceneWindow::disableButtons
//==============================================================================
void SceneWindow::disableButtons()
{
    buttonGroup->opened(false);
    cbOpenNavigationArea(buttonGroup, this);
    buttonGroup->deactivate();
}

//==============================================================================
// SceneWindow::cbOpenNavigationArea
//==============================================================================
void SceneWindow::cbOpenNavigationArea(Widget* w, void* arg)
{
    BarGroup* barGroup = (BarGroup*) w;
    Widget* widget = barGroup->window();
    

    if(barGroup->opened())
    {
        barGroup->window()->resize(barGroup->window()->w(), barGroup->window()->h()+95);
        barGroup->window()->relayout();
    }
    else
    {
        barGroup->window()->resize(barGroup->window()->w(), barGroup->window()->h()-95);
        barGroup->window()->relayout();
    }
}

//==============================================================================
// SceneWindow::cbAdd
//==============================================================================
void SceneWindow::cbAdd(Widget *o, void* userData)
{
    SceneWindow *sceneWindow = (SceneWindow*)(userData);
    FileChooser chooser("./", "VRML File (*.wrl)", FileChooser::SINGLE, "Select a vrml file" );

    chooser.exec(sceneWindow->window(), true);

    if ( chooser.value() == NULL )
        return;
    
    sceneWindow->addVRMLFile(chooser.value(0));
}

//==============================================================================
// SceneWindow::cbRemove
//==============================================================================
void SceneWindow::cbRemove(Widget *o, void* userData)
{
    // shows remove vrml widget
    SceneWindow *sceneWindow = (SceneWindow*)(userData);
    sceneWindow->removeVrmlFileWindow->show();
}

//==============================================================================
// SceneWindow::cbRemoveVRMLButton
//==============================================================================
void SceneWindow::cbRemoveVRMLButton(Widget *o, void* userData)
{
     
    SceneWindow *sceneWindow = (SceneWindow*)(userData);

    Widget* w = sceneWindow->vrmlFileList->goto_top();
    while(w)
    {
        if (w->selected())
        {
            Group* group = w->parent();


            sceneWindow->removeVRMLFile(w->label());
            group->remove(w);           
            delete w;
            w = sceneWindow->vrmlFileList->goto_top();

        } else {
            w = sceneWindow->vrmlFileList->next();

        }
    }


    if(sceneWindow->vrmlFileList->children() < 1)
    {
        sceneWindow->disableButtons();
    }

    sceneWindow->removeVrmlFileWindow->hide();
}

//==============================================================================
// SceneWindow::cbRemoveAllVRMLButton
//==============================================================================
void SceneWindow::cbRemoveAllVRMLButton(Widget *o, void* userData)
{
    SceneWindow *sceneWindow = (SceneWindow*)(userData);
    for(int i = 0; i < sceneWindow->vrmlFileList->children(); ++i)
        sceneWindow->vrmlFileList->select(i, true);
    cbRemoveVRMLButton(o, userData);
    sceneWindow->removeVrmlFileWindow->hide();
}

//==============================================================================
// SceneWindow::cbVrmlFileCancelButton
//==============================================================================
void SceneWindow::cbVrmlFileCancelButton(Widget *o, void* userData)
{
    SceneWindow *sceneWindow = (SceneWindow*)(userData);
    sceneWindow->removeVrmlFileWindow->hide();
}

//==============================================================================
// SceneWindow::cbBind
//==============================================================================
void SceneWindow::cbBind(Widget *o, void* userData)
{
    SceneWindow *sceneWindow = (SceneWindow*)(userData);
    sceneWindow->bindedVariableNotApply.deleteAllElements();
    for(int i = 0; i < sceneWindow->bindedVariable.getNumElements();++i)
        sceneWindow->bindedVariableNotApply.appendElement(new BindedVariable(*sceneWindow->bindedVariable.getElement(i)));
    sceneWindow->sceneBindWindow->show();
}

//==============================================================================
// SceneWindow::addVRMLFile
//==============================================================================
int SceneWindow::addVRMLFile(const char* filename)
{
    if(scene->addVRML(filename))
    {
        printf("VRML Couldnot load");
        //scene->unload();
        //vrmlVariableList->clear();
        //bindedVariable.deleteAllElements();
        //disableButtons();
        //label("");
        return 1;
    }
    else
    {
        if(strrchr(filename,'/'))
        {
            vrmlFileList->add(&(strrchr(filename,'/')[1]));
        }
        else
        {
            vrmlFileList->add(filename);
        }


        //vrmlVariableList->clear();
        //bindedVariable.deleteAllElements();
        //scene->fillBrowser(vrmlVariableList);
        enableButtons();

        char* file = new char[strlen(filename)];
        strcpy(file, filename);
        vrmlFiles.appendElement(file);

        return 0;
        //scene->print();
    }
}

//==============================================================================
// SceneWindow::removeVRMLFile
//==============================================================================
int SceneWindow::removeVRMLFile(const char* filename)
{
    scene->removeVRML(filename);

    bindedVariableNotApply.deleteAllElements();
    for(int i = 0; i < bindedVariable.getNumElements();++i)
        bindedVariableNotApply.appendElement(new BindedVariable(*bindedVariable.getElement(i)));

    // silinen dosyaya bagli degiskenler kaldirilir.
    for(int i = 0; i < bindedVariable.getNumElements(); ++i)
    {
        if(!strcmp(bindedVariable.getElement(i)->vrmlFilename, filename))
            unbindVariable(bindedVariable.getElement(i)->vrmlVariableWidget);
    }
    cbOkBindVariable(NULL, this);

    // Listeden vrml dugumleri silinir.
    for(int i = 0; i < vrmlVariableList->children(); ++i)
    {
        if(!strcmp(vrmlVariableList->child(i)->label(), filename))
        {
            Widget* w = vrmlVariableList->child(i);
            vrmlVariableList->remove(w);
            delete w;
            break;
        }
    }
}

//==============================================================================
// SceneWindow::cbChangeMode
//==============================================================================
void SceneWindow::cbChangeMode(Widget* w, void* userData)
{
    SceneWindow *sceneWindow = (SceneWindow*)(userData);
    if(sceneWindow->isPanMode)
    {
        sceneWindow->panButton->button()->color(fltk::GRAY65);
        sceneWindow->rotateButton->button()->color(fltk::BLUE);
    }
    else
    {
        sceneWindow->rotateButton->button()->color(fltk::GRAY65);
        sceneWindow->panButton->button()->color(fltk::BLUE);
    }

    sceneWindow->isPanMode = !sceneWindow->isPanMode;
    sceneWindow->rotateButton->redraw();
    sceneWindow->panButton->redraw();
}

//==============================================================================
// SceneWindow::cbNavigate
//==============================================================================
void SceneWindow::cbNavigate(Widget *o, void* userData)
{
    Button* rotate = (Button*)o;
    SceneWindow *sceneWindow = (SceneWindow*)(userData);
    
    if(sceneWindow->isPanMode)
    {
        if( rotate == sceneWindow->upButton->button())
            sceneWindow->scene->moveCamera(1);
        else if( rotate == sceneWindow->downButton->button())
            sceneWindow->scene->moveCamera(-1);
        else if( rotate == sceneWindow->rightButton->button())
            sceneWindow->scene->strafeCamera(1);
        else if( rotate == sceneWindow->leftButton->button())
            sceneWindow->scene->strafeCamera(-1);
    }
    else
    {
        if( rotate == sceneWindow->upButton->button())
            sceneWindow->scene->rotateViewUpDown(1);
        else if( rotate == sceneWindow->downButton->button())
            sceneWindow->scene->rotateViewUpDown(-1);
        else if( rotate == sceneWindow->rightButton->button())
            sceneWindow->scene->rotateViewLeftRight(1);
        else if( rotate == sceneWindow->leftButton->button())
            sceneWindow->scene->rotateViewLeftRight(-1);
    }
}

//==============================================================================
// SceneWindow::cbZoom
//==============================================================================
void SceneWindow::cbZoom(Widget *o, void* userData)
{
    Button* zoomButton = (Button*)o;
    SceneWindow *sceneWindow = (SceneWindow*)(userData);

    if( zoomButton == sceneWindow->zoomInButton->button())
        sceneWindow->scene->zoomIn();
    else if( zoomButton == sceneWindow->zoomOutButton->button())
        sceneWindow->scene->zoomOut();

}

//==============================================================================
// SceneWindow::cbChangeCamera
//==============================================================================
void SceneWindow::cbChangeCamera(Widget *o, void* userData)
{
    Button* cameraButton = (Button*)o;
    SceneWindow *sceneWindow = (SceneWindow*)(userData);

    if( cameraButton == sceneWindow->nextCameraButton->button())
        sceneWindow->scene->nextCamera();
    else if( cameraButton == sceneWindow->prevCameraButton->button())
        sceneWindow->scene->prevCamera();
    else if( cameraButton == sceneWindow->resetCameraButton->button())
        sceneWindow->scene->resetCamera();
}


//==============================================================================
// SceneWindow::cbBindVariable
//==============================================================================
void SceneWindow::cbBindVariable(Widget* widget, void* arg)
{
    SceneWindow* selectWindow = (SceneWindow*)arg;
    Widget* wv = selectWindow->vrmlVariableList->goto_focus();
    if(wv == NULL)
    {
        fltk::alert("Please select a vrml variable from the list.");
        return;
    }

    if(!wv->active())
    {
        fltk::alert("Please select a valid vrml variable from the list.");
        return;
    }

    Widget* wl = selectWindow->logVariableList->goto_focus();
    if(wl == NULL)
    {
        fltk::alert("Please select a log variable from the list.");
        return;
    }

    if(!wl->active() || (wv->is_group() && !wl->is_group()) || (!wv->is_group() && wl->is_group()))
    {
        fltk::alert("Please select a valid log variable from the list.");
        return;
    }

    
    selectWindow->bindVariable(wv, wl);
    selectWindow->vrmlVariableList->redraw();
}

//==============================================================================
// SceneWindow::bindVariable
//==============================================================================
void SceneWindow::bindVariable(Widget* wrmlVariableWidget, Widget* logVariableWidget)
{
    LogVariableGUI *logVariable;
    char buffer[256];
    BindedVariable* newElement;
    Array<int> vrmlElementIndex;
    const char* vrmlFilename;

    const int* count = vrmlVariableList->focus_index();
    int indexSize = vrmlVariableList->focus_level();
    for(int i = 0; i < indexSize+1; ++i)
        vrmlElementIndex.appendElement(count[i]);
    
    vrmlFilename = vrmlVariableList->child(vrmlElementIndex.getElement(0))->label();
    vrmlElementIndex.removeElement(0);

    if(wrmlVariableWidget->is_group())
    {
        logVariable = static_cast<LogVariableGUI*>(logVariableWidget->user_data());
        Group* g = static_cast<Group*> (wrmlVariableWidget);
        unbindVariable(g);

        if (!strcmp(wrmlVariableWidget->label(), "point") || !strcmp(wrmlVariableWidget->label(), "color") ||
                !strcmp(wrmlVariableWidget->label(), "vector"))
        {
            for(int i = 0; i < logVariable->getRows(); ++i)
            {
                Group* gChild = static_cast<Group*> (g->child(i));
                vrmlElementIndex.appendElement(i);
                for(int j = 0; j < logVariable->getCols(); ++j)
                {
                    newElement = new BindedVariable(gChild->child(j),logVariable, i*logVariable->getCols()+j);
                    vrmlElementIndex.appendElement(j);
                    newElement->vrmlIndex = vrmlElementIndex;
                    newElement->setVrmlFilename(vrmlFilename);
                    bindedVariableNotApply.appendElement(newElement);
                    snprintf(buffer, 256, "%s\t%s", gChild->child(j)->label() ,logVariable->getSubNames(i,j));
                    gChild->child(j)->copy_label(buffer);

                    vrmlElementIndex.removeElement(vrmlElementIndex.getNumElements()-1);
                }
                vrmlElementIndex.removeElement(vrmlElementIndex.getNumElements()-1);
            }
        }
        else
        {
            for(int i = 0; i < logVariable->getSize(); ++i)
            {
                newElement = new BindedVariable(g->child(i),logVariable, i);
                vrmlElementIndex.appendElement(i);
                newElement->vrmlIndex = vrmlElementIndex;
                newElement->setVrmlFilename(vrmlFilename);
                bindedVariableNotApply.appendElement(newElement);
                snprintf(buffer, 256, "%s\t%s", g->child(i)->label() ,logVariable->getSubNames(i));
                g->child(i)->copy_label(buffer);

                vrmlElementIndex.removeElement(vrmlElementIndex.getNumElements()-1);
            }
        }
    }
    else
    {
        int index = 0;
        logVariable = static_cast<LogVariableGUI*>(logVariableWidget->user_data());
        if(logVariable->getSize() > 1)
        {
            index = logVariableWidget->parent()->find(logVariableWidget);
        }

        // Unbinded if vrml variable binded a log variable
        removeUnbindVariable(wrmlVariableWidget);
        newElement = new BindedVariable(wrmlVariableWidget,logVariable, index);
        newElement->vrmlIndex = vrmlElementIndex;
        newElement->setVrmlFilename(vrmlFilename);
        bindedVariableNotApply.appendElement(newElement);
        snprintf(buffer, 256, "%s\t%s", wrmlVariableWidget->label() ,logVariableWidget->label());
        wrmlVariableWidget->copy_label(buffer);
    }

}

//==============================================================================
// SceneWindow::cbUnbindVariable
//==============================================================================
void SceneWindow::cbUnbindVariable(Widget* widget, void* arg)
{
    SceneWindow* selectWindow = (SceneWindow*)arg;

    Widget* wv = selectWindow->vrmlVariableList->goto_focus();
    if(wv == NULL)
    {
        fltk::alert("Please select a vrml variable from the list.");
        return;
    }

    if(wv->user_data() == NULL)
        return;

    selectWindow->unbindVariable(wv);
    selectWindow->vrmlVariableList->redraw();
}

//==============================================================================
// SceneWindow::unbindVariable
//==============================================================================
void SceneWindow::unbindVariable(Widget* vrmlWidget)
{
    char buffer[256];
    int length;

    if(vrmlWidget->is_group())
    {
        Group* g = static_cast<Group*> (vrmlWidget);
        if(strchr(vrmlWidget->label(),'\t'))
        {
            length = strlen(vrmlWidget->label()) - strlen(strchr(vrmlWidget->label(),'\t'));
            strncpy (buffer, vrmlWidget->label(), length);
            buffer[length] = '\0';
            vrmlWidget->copy_label(buffer);
        }

        if (!strcmp(vrmlWidget->label(), "point") || !strcmp(vrmlWidget->label(), "color") ||
                !strcmp(vrmlWidget->label(), "vector"))
        {
            for(int i = 0; i < g->children(); ++i)
            {
                Group* gChild = static_cast<Group*> (g->child(i));
                if(strchr(gChild->label(),'\t'))
                {
                    length = strlen(gChild->label()) - strlen(strchr(gChild->label(),'\t'));
                    strncpy (buffer, gChild->label(), length);
                    buffer[length] = '\0';
                    gChild->copy_label(buffer);
                }
                
                for(int j = 0; j < gChild->children(); ++j)
                {
                    removeUnbindVariable(gChild->child(j));
                }
            }
        }
        else
        {
            for(int i = 0; i < g->children(); ++i)
            {
                removeUnbindVariable(g->child(i));
            }
        }
    }
    else
    {
        removeUnbindVariable(vrmlWidget);
        /*
        if(strchr(vrmlWidget->parent()->label(),'\t'))
        {
            length = strlen(vrmlWidget->parent()->label()) - strlen(strchr(vrmlWidget->parent()->label(),'\t'));
            strncpy (buffer, vrmlWidget->parent()->label(), length);
            buffer[length] = '\0';
            vrmlWidget->parent()->copy_label(buffer);
        }
         */
    }
}

//==============================================================================
// SceneWindow::removeUnbindVariable
//==============================================================================
void SceneWindow::removeUnbindVariable(Widget* vrmlWidget)
{
    char buffer[256];

    for(int i = 0; i < bindedVariableNotApply.getNumElements(); ++i)
    {
        if(bindedVariableNotApply.getElement(i)->vrmlVariableWidget == vrmlWidget)
        {
            delete bindedVariableNotApply.getElement(i);
            bindedVariableNotApply.removeElement(i);

            int length = strlen(vrmlWidget->label()) - strlen(strchr(vrmlWidget->label(),'\t'));
            strncpy (buffer, vrmlWidget->label(), length);
            buffer[length] = '\0';
            vrmlWidget->copy_label(buffer);
            break;
        }
    }

    scene->redraw();
}

//==============================================================================
// SceneWindow::cbUnbindAllVariable
//==============================================================================
void SceneWindow::cbUnbindAllVariable(Widget* w, void* arg)
{
    SceneWindow* selectWindow = (SceneWindow*)arg;
    selectWindow->bindedVariableNotApply.deleteAllElements();

    char buffer[256];
    int length;
    Widget* vrmlWidget = selectWindow->vrmlVariableList->goto_top();
    while( vrmlWidget )
    {
        if(strchr(vrmlWidget->label(),'\t'))
        {
            length = strlen(vrmlWidget->label()) - strlen(strchr(vrmlWidget->label(),'\t'));
            strncpy (buffer, vrmlWidget->label(), length);
            buffer[length] = '\0';
            vrmlWidget->copy_label(buffer);
        }
        vrmlWidget = selectWindow->vrmlVariableList->next();
    }
    selectWindow->vrmlVariableList->redraw();
}

//==============================================================================
// SceneWindow::cbOkBindVariable
//==============================================================================
void SceneWindow::cbOkBindVariable(Widget* w, void* arg)
{
    SceneWindow* selectWindow = (SceneWindow*)arg;
    
    for(int i = 0; i < selectWindow->bindedVariable.getNumElements(); ++i)
        selectWindow->bindedVariable.getElement(i)->reset();
    selectWindow->bindedVariable.deleteAllElements();
    
    for(int i = 0; i < selectWindow->bindedVariableNotApply.getNumElements(); ++i)
        selectWindow->bindedVariable.appendElement(selectWindow->bindedVariableNotApply.getElement(i));    
    selectWindow->bindedVariableNotApply.removeAllElements();
    selectWindow->sceneBindWindow->hide();

    //SceneWindowConfig config = selectWindow->save();
    //selectWindow->load(config);
}

//==============================================================================
// SceneWindow::cbCancelBindVariable
//==============================================================================
void SceneWindow::cbCancelBindVariable(Widget* w, void* arg)
{
    SceneWindow* selectWindow = (SceneWindow*)arg;

    selectWindow->cbUnbindAllVariable(w, arg);

    char buffer[256];

    Widget* vrmlVariableWidget;
    LogVariableGUI *logVariable;
    int index;
    for(int i = 0; i < selectWindow->bindedVariable.getNumElements(); ++i)
    {
        vrmlVariableWidget = selectWindow->bindedVariable.getElementRef(i)->vrmlVariableWidget;
        logVariable = selectWindow->bindedVariable.getElementRef(i)->logVariable;
        index = selectWindow->bindedVariable.getElementRef(i)->index;

        snprintf(buffer, 256, "%s\t%s", vrmlVariableWidget->label(), logVariable->getSubNames(index));
        vrmlVariableWidget->copy_label(buffer);
    }

    selectWindow->sceneBindWindow->hide();
}

//==============================================================================
// SceneWindow::cbChangedVrmlList
//==============================================================================
void SceneWindow::cbChangedVrmlList(Widget* w, void* arg)
{
    SceneWindow* selectWindow = (SceneWindow*)arg;
    selectWindow->updateLogVariableBrowser();
}


//==============================================================================
// SceneWindow::updateLogVariableBrowser
//==============================================================================
void SceneWindow::updateLogVariableBrowser()
{
    char buffer[256];
    int length;
    LogVariableGUI *logVariable;
    
    Widget* w = vrmlVariableList->goto_focus();
    if(w == NULL || !w->active())
        return;

    int requiredSize = 0;
    if(w->is_group() )
    {
        if(w->user_data())
            requiredSize = *(static_cast<int*>(w->user_data()));
    }
    else
        requiredSize = 1;
   
    
    if(strchr(w->label(),'\t'))
    {
        length = strlen(w->label()) - strlen(strchr(w->label(),'\t'));
        strncpy (buffer, w->label(), length);
        buffer[length] = '\0';
    }
    else
    {
        strcpy (buffer, w->label());
    }

    for(int i = 0; i < logVariableList->children(); ++i)
    {
        logVariable = static_cast<LogVariableGUI*>(logVariableList->child(i)->user_data());
        if(requiredSize == 1)
        {
            logVariableList->child(i)->activate();
            if(logVariableList->child(i)->is_group())
            {
                Group* g = static_cast<Group*> (logVariableList->child(i));
                for(int j = 0; j < g->children(); ++j)
                    g->child(j)->activate();
            }
        }
        else if( (!strcmp(buffer, "point") || !strcmp(buffer, "color") || !strcmp(buffer, "vector"))
                && logVariable->getCols() == 3 && logVariable->getSize()/3 <= requiredSize)
        {
            logVariableList->child(i)->activate();
            if(logVariableList->child(i)->is_group())
            {
                Group* g = static_cast<Group*> (logVariableList->child(i));
                for(int j = 0; j < g->children(); ++j)
                    g->child(j)->deactivate();
            }
        }
        else if (( !strcmp(buffer, "coordIndex") || !strcmp(buffer, "colorIndex") || !strcmp(buffer, "normalIndex"))
                && logVariable->getCols() == 1 && logVariable->getSize() <= requiredSize)
        {
            logVariableList->child(i)->activate();
            if(logVariableList->child(i)->is_group())
            {
                Group* g = static_cast<Group*> (logVariableList->child(i));
                for(int j = 0; j < g->children(); ++j)
                    g->child(j)->deactivate();
            }
        }
        else if(logVariable->getSize() == requiredSize)
        {
            logVariableList->child(i)->activate();

            if(logVariableList->child(i)->is_group())
            {
                Group* g = static_cast<Group*> (logVariableList->child(i));
                for(int j = 0; j < g->children(); ++j)
                    g->child(j)->deactivate();
            }
        }
        else
        {
            logVariableList->child(i)->deactivate();
            if(logVariableList->child(i)->is_group())
            {
                Group* g = static_cast<Group*> (logVariableList->child(i));
                for(int j = 0; j < g->children(); ++j)
                    g->child(j)->deactivate();
            }
        }
    }
}

//==============================================================================
// SceneWindow::fillLogVariableList
//==============================================================================
void SceneWindow::fillLogVariableList()
{
    Group* g;
    for(int i = 0; i < LogVariablesGUI.getNumElements(); ++i)
    {
        // Vector olmayan degiskenler icin
        if(LogVariablesGUI.getElement(i)->getSize() == 1)
        {
            logVariableList->add_leaf(LogVariablesGUI.getElement(i)->getName(), logVariableList, LogVariablesGUI.getElement(i))->deactivate();
        }
        else
        {
            g = logVariableList->add_group (LogVariablesGUI.getElement(i)->getName(), logVariableList, LogVariablesGUI.getElement(i));
            g->deactivate();
            for(int j = 0; j < LogVariablesGUI.getElement(i)->getSize(); ++j)
                logVariableList->add_leaf(LogVariablesGUI.getElement(i)->getSubNames(j), g, LogVariablesGUI.getElement(i));
        }
    }
}

//==============================================================================
// SceneWindow::save
//==============================================================================
SceneWindowConfig SceneWindow::save()
{
    SceneWindowConfig sceneConfig;
    SceneBindVariableConfig bindedVrmlVariable;

    sceneConfig.x = x();
    sceneConfig.y = y();
    sceneConfig.w = w();
    sceneConfig.h = h();

    for(int i = 0; i < vrmlFiles.getNumElements(); ++i)
        sceneConfig.vrmlFiles.appendElement(vrmlFiles.getElement(i));

    printf("\n\nSaved Data :\n");
    for(int i = 0; i < bindedVariable.getNumElements(); ++i)
    {
        bindedVrmlVariable.vrmlFilename = bindedVariable.getElement(i)->vrmlFilename;
        bindedVrmlVariable.vrmlIndex = bindedVariable.getElement(i)->vrmlIndex;
        bindedVrmlVariable.logVariable = bindedVariable.getElement(i)->logVariable;
        bindedVrmlVariable.logVarIndex = bindedVariable.getElement(i)->index;

        sceneConfig.bindedVariable.appendElement(bindedVrmlVariable);

        printf("%s ", bindedVrmlVariable.vrmlFilename);
        for(int j = 0; j < bindedVrmlVariable.vrmlIndex.getNumElements(); ++j)
            printf("%d ", bindedVrmlVariable.vrmlIndex.getElement(j));
        printf(" %s %d\n", bindedVrmlVariable.logVariable->getName(), bindedVrmlVariable.logVarIndex);
    }

    return sceneConfig;
}

void SceneWindow::load(SceneWindowConfig* config)
{

    resize(config->x, config->y, config->w, config->h);
    layout();

    // Load vrml files
    for(int i = 0; i < config->vrmlFiles.getNumElements(); ++i)
    {
        if(addVRMLFile(config->vrmlFiles.getElement(i)))
        {
            printf("ERROR VRML FILE\n");
        }
    }    
    
    Widget* vrmlWidget;
    Widget* logWidget;
    Group* group;
    int* indexes;
    int level;
    bool vrmlFileFound;

    for(int i = 0; i < config->bindedVariable.getNumElements(); ++i)
    {
        // Find VRML Variable Widget
        indexes = new int [config->bindedVariable.getElement(i).vrmlIndex.getNumElements()+1];
        for(int j = 1; j < config->bindedVariable.getElement(i).vrmlIndex.getNumElements()+1; ++j)
            indexes[j] = config->bindedVariable.getElement(i).vrmlIndex.getElement(j-1);

        vrmlFileFound = false;
        for(int j = 0; j < vrmlFileList->children(); ++j)
        {
            if(!strcmp(vrmlFileList->child(j)->label(),config->bindedVariable.getElement(i).vrmlFilename))
            {
                vrmlFileFound = true;
                indexes[0] = j;
                break;
            }
        }

        if(!vrmlFileFound)
        {
            printf("ERROR vrml file not load");
            continue;
        }
        

        level = config->bindedVariable.getElement(i).vrmlIndex.getNumElements();        
        vrmlWidget = vrmlVariableList->goto_index(indexes, level);
        delete[] indexes;

        if(!vrmlWidget)
        {
            printf("ERROR vrml file not load");
            continue;
        }

        // Find Log Variable Widget
        logWidget = NULL;
        for(int j = 0; j < logVariableList->children(); ++j)
        {
            if(!strcmp(logVariableList->child(j)->label(),config->bindedVariable.getElement(i).logVariable->getName()))
            {
                logWidget = logVariableList->child(j);
                break;
            }
        }

        if(logWidget == NULL)
        {
            printf("ERROR log variable not found");
            continue;
        }

        if(logWidget->is_group())
        {
            group = static_cast<Group*>(logWidget);
            logWidget = group->child(config->bindedVariable.getElement(i).logVarIndex);
        }

        bindVariable(vrmlWidget, logWidget);
    }

    cbOkBindVariable(NULL, this);
}