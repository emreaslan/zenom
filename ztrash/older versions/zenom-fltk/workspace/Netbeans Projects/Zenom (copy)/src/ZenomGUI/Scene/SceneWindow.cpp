/*
 * File:   PlotBaseWindow.cpp
 * Author: root
 *
 * Created on September 4, 2009, 1:36 PM
 */

#include "SceneWindow.h"


SceneWindow::SceneWindow( Array<LogVariableGUI*>& logVars )
 : Window( 670, 655 ), LogVariablesGUI(logVars)
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
    loadButton = new Button(0,0,60,23,"Load");
    loadButton->box(fltk::PLASTIC_UP_BOX);
    loadButton->color(fltk::GRAY70);
    loadButton->highlight_color(fltk::GRAY60);
    loadButton->callback(cbLoad, this);

    bindButton = new Button(70,0,60,23,"Bind");
    bindButton->box(fltk::PLASTIC_UP_BOX);
    bindButton->color(fltk::GRAY70);
    bindButton->highlight_color(fltk::GRAY60);
    bindButton->callback(cbBind, this);
    menu->end();
    //  --- Menu ---




    /*********************************************/
    //             OPENGL SCENE                  //
    scene = new Scene(10, 35, 640, 480);

    buttonGroup = new Group(10, 520, gbox->w()-20, 95);
    buttonGroup->box(fltk::PLASTIC_UP_BOX);
    //buttonGroup->color(fltk::BLUE);
    buttonGroup->begin();


    //  ----- Headlight -----
    headlightButton = new ZButton(210, 35, 25, 25,"@s-2;@circle;");
    headlightButton->button()->callback(cbHeadlight, this);
    headlightButton->button()->highlight_color(fltk::YELLOW);
    //  ----- Headlight -----


    //  ----- Navigate -----
    navigateGroup = new Group(240,0,95,95);
    navigateGroup->box(fltk::PLASTIC_UP_BOX);
    navigateGroup->color(fltk::GRAY80);
    navigateGroup->begin();
    rotateUpButton = new ZButton(35,5,25,25,"@y-5;@b;@s+7;^");
    rotateUpButton->button()->callback(cbRotate, this);
    rotateLeftButton = new ZButton(5,35,25,25,"@s+8;<");
    rotateLeftButton->button()->callback(cbRotate, this);
    rotateCenterButton = new ZButton(35,35,25,25,"@s-4;@square");
    rotateCenterButton->button()->callback(cbRotate, this);
    rotateRightButton = new ZButton(65,35,25,25,"@s+8;>");
    rotateRightButton->button()->callback(cbRotate, this);
    rotateDownButton = new ZButton(35,65,25,25,"@b;@s+2;v");
    rotateDownButton->button()->callback(cbRotate, this);
    rotateButton = new ZButton(5,65,25,25,"@b;R");
    rotateButton->button()->callback(cbChangeMode, this);
    panButton = new ZButton(65,65,25,25,"@b;P");
    panButton->button()->callback(cbChangeMode, this);
    navigateGroup->end();

    //  --- Navigate ---

    //  ----- Camera -----
    cameraGroup = new Group(340,30, 65, 35, "Viewpoint");
    cameraGroup->box(fltk::PLASTIC_UP_BOX);
    cameraGroup->color(fltk::GRAY80);
    cameraGroup->begin();
    nextCameraButton = new ZButton(5, 5,25,25,"@<<");
    nextCameraButton->button()->callback(cbRotate, this);
    prevCameraButton = new ZButton(35, 5,25,25,"@>>");
    prevCameraButton->button()->callback(cbRotate, this);
    cameraGroup->end();
    //  ----- Camera -----


    buttonGroup->end();

    statusBar = new StatusBarGroup(0,0,10,20);
    statusBar->label("Hüsnü bitir bunu yarına kadar");

    //gbox->end();
    this->end();
    gbox->resizable(scene);
    resizable(scene);

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

    fillLogVariableList();
    disableButtons();

}

//==============================================================================
// SceneWindow::~SceneWindow
//==============================================================================
SceneWindow::~SceneWindow()
{

    delete headlightButton;

    // delete navigation area
    delete rotateLeftButton;
    delete rotateRightButton;
    delete rotateUpButton;
    delete rotateDownButton;
    delete rotateCenterButton;
    delete rotateButton;
    delete panButton;
    delete navigateGroup;

    delete nextCameraButton;
    delete prevCameraButton;
    delete cameraGroup;

    delete buttonGroup;

    // delete buttons etc.
    delete loadButton;
    delete bindButton;
    delete menu;

    delete scene;

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
                //(*dtarget) = 3;
                (*dtarget) = logVariable->getLastHeapElement(index);
                break;
            }
            case Z_INTEGER:
            {
                int *itarget = static_cast<int*>(vrmlVariable->variable);
                //(*itarget) = 2000;
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
    buttonGroup->activate();
    panButton->button()->color(fltk::BLUE);
    isPanMode = true;
}

//==============================================================================
// SceneWindow::disableButtons
//==============================================================================
void SceneWindow::disableButtons()
{

    buttonGroup->deactivate();
}

//==============================================================================
// SceneWindow::cbLoad
//==============================================================================
void SceneWindow::cbLoad(Widget *o, void* userData)
{
    SceneWindow *sceneWindow = (SceneWindow*)(userData);
    FileChooser chooser("./", "VRML File (*.wrl)", FileChooser::SINGLE, "Select a vrml file" );

    chooser.exec(sceneWindow->window(), true);

    if ( chooser.value() == NULL )
        return;
    
    sceneWindow->loadVRMLFile(chooser.value(0));
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
// SceneWindow::load
//==============================================================================
int SceneWindow::loadVRMLFile(const char* filename)
{  
    if(scene->vrmlParse(filename))
    {
        scene->unload();
        vrmlVariableList->clear();
        bindedVariable.deleteAllElements();
        disableButtons();
        label("");
        return 1;
    }
    else
    {
        vrmlVariableList->clear();
        bindedVariable.deleteAllElements();
        scene->fillBrowser(vrmlVariableList);
        enableButtons();
        headlight();
        label(filename);
        return 0;
        //scene->print();
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
// SceneWindow::cbRotate
//==============================================================================
void SceneWindow::cbRotate(Widget *o, void* userData)
{
    Button* rotate = (Button*)o;
    SceneWindow *sceneWindow = (SceneWindow*)(userData);

    if(sceneWindow->isPanMode)
    {
        if( rotate == sceneWindow->rotateUpButton->button())
            sceneWindow->scene->moveForward();
        else if( rotate == sceneWindow->rotateDownButton->button())
            sceneWindow->scene->moveBackward();
        else if( rotate == sceneWindow->rotateRightButton->button())
            sceneWindow->scene->moveLeft();
        else if( rotate == sceneWindow->rotateLeftButton->button())
            sceneWindow->scene->moveRight();
    }
    else
    {
        if( rotate == sceneWindow->rotateUpButton->button())
            sceneWindow->scene->rotateUp();
        else if( rotate == sceneWindow->rotateDownButton->button())
            sceneWindow->scene->rotateDown();
        else if( rotate == sceneWindow->rotateRightButton->button())
            sceneWindow->scene->rotateLeft();
        else if( rotate == sceneWindow->rotateLeftButton->button())
            sceneWindow->scene->rotateRight();
    }
}
//==============================================================================
// SceneWindow::cbHeadlight
//==============================================================================
void SceneWindow::cbHeadlight(Widget *o, void* userData)
{
    Button* button = (Button*)o;
    SceneWindow *sceneWindow = (SceneWindow*)(userData);
    sceneWindow->scene->changeHeadlight();
    sceneWindow->headlight();

}

//==============================================================================
// SceneWindow::headlight
//==============================================================================
void SceneWindow::headlight()
{
    if(scene->getHeadlight())
    {
        headlightButton->button()->labelcolor(fltk::YELLOW);
    }
    else
    {
        headlightButton->button()->labelcolor(fltk::BLACK);
    }
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
    ZParameter* vrmlVariable;
    char buffer[256];

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
                for(int j = 0; j < logVariable->getCols(); ++j)
                {
                    bindedVariableNotApply.appendElement(new BindedVariable(gChild->child(j),logVariable, i*logVariable->getCols()+j));
                    snprintf(buffer, 256, "%s\t%s", gChild->child(j)->label() ,logVariable->getSubNames(i,j));
                    gChild->child(j)->copy_label(buffer);                   
                }
            }
        }
        else
        {
            for(int i = 0; i < logVariable->getSize(); ++i)
            {
                bindedVariableNotApply.appendElement(new BindedVariable(g->child(i),logVariable, i));
                snprintf(buffer, 256, "%s\t%s", g->child(i)->label() ,logVariable->getSubNames(i));
                g->child(i)->copy_label(buffer);
            }
        }

        /*
        snprintf(buffer, 256, "%s\t%s", wrmlVariableWidget->label() ,logVariable->getName());
        wrmlVariableWidget->copy_label(buffer);
         */

    }
    else
    {
        int index = 0;
        Group* group;
        logVariable = static_cast<LogVariableGUI*>(logVariableWidget->user_data());
        if(logVariable->getSize() > 1)
        {
            index = logVariableWidget->parent()->find(logVariableWidget);
        }

        // Unbinded if vrml variable binded a log variable
        removeUnbindVariable(wrmlVariableWidget);
        bindedVariableNotApply.appendElement(new BindedVariable(wrmlVariableWidget,logVariable, index));
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
            bindedVariableNotApply.getElement(i)->reset();
            delete bindedVariableNotApply.getElement(i);
            bindedVariableNotApply.removeElement(i);

            int length = strlen(vrmlWidget->label()) - strlen(strchr(vrmlWidget->label(),'\t'));
            strncpy (buffer, vrmlWidget->label(), length);
            buffer[length] = '\0';
            vrmlWidget->copy_label(buffer);
            break;
        }
    }


    /*
    int length;
    if(strchr(vrmlWidget->parent()->label(),'\t'))
    {
        length = strlen(vrmlWidget->parent()->label()) - strlen(strchr(vrmlWidget->parent()->label(),'\t'));
        strncpy (buffer, vrmlWidget->parent()->label(), length);
        buffer[length] = '\0';
        vrmlWidget->parent()->copy_label(buffer);
    }
     */
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
    for(int i = 0; i < selectWindow->bindedVariableName.getNumElements(); ++i)
        delete[] selectWindow->bindedVariableName.getElement(i);
    selectWindow->bindedVariableName.removeAllElements();
    
    selectWindow->bindedVariable.deleteAllElements();
    for(int i = 0; i < selectWindow->bindedVariableNotApply.getNumElements(); ++i)    
        selectWindow->bindedVariable.appendElement(selectWindow->bindedVariableNotApply.getElement(i));    
    selectWindow->bindedVariableNotApply.removeAllElements();
    selectWindow->sceneBindWindow->hide();

    SceneWindowConfig config = selectWindow->save();

    config.x += 20;
    config.y += 20;
    config.w += 20;
    config.h += 20;

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

    sceneConfig.vrmlFiles.appendElement(label());
    cout << "label : " << label() << endl;
    
    char* parentPath;
    int length;
    Widget* vrmlVariableWidget;
    Widget* parent;
  

    for(int i = 0; i < bindedVariable.getNumElements(); ++i)
    {

        vrmlVariableWidget = bindedVariable.getElementRef(i)->vrmlVariableWidget;
        
        parent = vrmlVariableWidget;
        length = strlen(vrmlVariableWidget->label()) - strlen(strchr(vrmlVariableWidget->label(),'\t'));
        cout << "Widget label : " << vrmlVariableWidget->label() << endl;
        cout << "Islem sonrasi string : " << strchr(vrmlVariableWidget->label(),'\t') << endl;
        parentPath = new char[length + 1];
        strncpy (parentPath, parent->label(), length);
        parentPath[length] = '\0';
        while(parent->user_data() != NULL)
        {            
            parent = parent->parent();
            length = strlen(parent->label()) + strlen(parentPath) + 2;
            char* temp = new char[length];
            sprintf(temp, "%s->%s", parent->label(), parentPath);
            delete[] parentPath;
            parentPath = temp;
        }

        //bindedVrmlVariable = new SceneBindVariableConfig;
        bindedVrmlVariable.path = parentPath;
        bindedVrmlVariable.logVariable = bindedVariable.getElementRef(i)->logVariable;
        bindedVrmlVariable.index = bindedVariable.getElementRef(i)->index;

        sceneConfig.bindedVariable.appendElement(bindedVrmlVariable);
        
        //printf("\n%s %s %d", parentPath, bindedVrmlVariable.logVariable->getName(), bindedVrmlVariable.index);
    }

    return sceneConfig;
}

void SceneWindow::load(SceneWindowConfig* config)
{

    resize(config->x, config->y, config->w, config->h);
    layout();

    
    for(int i = 0; i < config->vrmlFiles.getNumElements(); ++i)
    {
        if(loadVRMLFile(config->vrmlFiles.getElement(i)))
        {
            printf("ERROR VRML FILE\n");
            return;            
        }
    }    


    //Transform (Pyramid01)->scale->x 1x3 0

    
    Widget* vrmlWidget;
    Widget* logWidget;
    Group* group;
    char* label;
    for(int i = 0; i < config->bindedVariable.getNumElements(); ++i)
    {
        // Find VRML Variable Widget
        vrmlWidget = vrmlVariableList;
        label = strtok(config->bindedVariable.getElement(i).path, "->");
        while(label != NULL)
        {
            group = static_cast<Group*>(vrmlWidget);
            for(int i = 0; i < group->children(); ++i)
            {
                if(!strcmp(group->child(i)->label(), label))
                {
                    vrmlWidget = group->child(i);
                    break;
                }
            }

            label = strtok(NULL, "->");
        }

        // Find Log Variable Widget
        for(int j = 0; j < logVariableList->children(); ++j)
        {
            if(!strcmp(logVariableList->child(j)->label(),config->bindedVariable.getElement(i).logVariable->getName()))
            {
                logWidget = logVariableList->child(j);
                break;
            }
        }

        if(logWidget->is_group())
        {
            group = static_cast<Group*>(logWidget);
            logWidget = group->child(config->bindedVariable.getElement(i).index);
        }

        bindVariable(vrmlWidget, logWidget);
    }

    cbOkBindVariable(NULL, this);
}





