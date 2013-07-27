//==============================================================================
// PlotWindow.cpp - PlotWindow implementasyonu
//
// Author        :
// Version       :
// Compatibility : GCC
//==============================================================================

#include "PlotWindow.h"
#include "Config.h"


//==============================================================================
// PlotWindow::PlotWindow
//==============================================================================
PlotWindow::PlotWindow( Array<LogVariableGUI*>& logVars, guiMessenger* messenger )
: PlotBaseWindow( logVars, (char*)"Plot Window" )
{
    //  ----- Plot Select Window -----

    selectAddButton->button()->callback(cbSelectAdd,this);
    selectAddAllButton->button()->callback(cbSelectAddAll,this);
    selectCancelButton->button()->callback(cbSelectCancel);

    begin();
    // GL
    glWindow = new GlPlotWindow(55,30,375,195);
    glWindow->set_double_buffer();
    glWindow->setMessengerObj(messenger);
    end();
    resizable(glWindow);

    fillList();
}

//==============================================================================
// PlotWindow::~PlotWindow
//==============================================================================
PlotWindow::~PlotWindow()
{
    delete glWindow;
}


//==============================================================================
// PlotWindow::save
//==============================================================================
PlotConfig PlotWindow::save()
{
    PlotConfig rValue;
    rValue.x = x();
    rValue.y = y();
    rValue.w = w();
    rValue.h = h();
    GlPlotWindow* glPlotWindow = dynamic_cast<GlPlotWindow*>(glWindow);
    rValue.line = glPlotWindow->save();
    rValue.isAutoScale = autoScale->value();
    rValue.isAutoTranslate = autoTranslate->value();

    return rValue;
}

//==============================================================================
// PlotWindow::load
//==============================================================================
void PlotWindow::load(PlotConfig* config)
{
    resize(config->x, config->y, config->w, config->h);
    layout();

    autoScale->value(config->isAutoScale);
    autoTranslate->value(config->isAutoTranslate);
    glWindow->setAutoScale(config->isAutoScale);
    glWindow->setAutoTranslate(config->isAutoTranslate);

    addLogVariable(config->line);
    reallignSelected();
}

//==============================================================================
// PlotWindow::addLogVariable
//=============================================================================
void PlotWindow::addLogVariable( Array<LogVarLine>& logVariable )
{
    Widget* selected;
    Group* g;
    for(int i = 0; i < logVariable.getNumElements(); ++i)
    {
        selected = NULL;
        for(int j = 0; j < selectMBrowser->size(); ++j)
            if( !strcmp(selectMBrowser->child(j)->label(), logVariable.getElement(i).logVariable->getName()) )
                selected = selectMBrowser->child(j);

        if(selected)
        {
            if(selected->is_group())
            {
                g = dynamic_cast<Group*>(selected);
                selected = NULL;
                for(int j = 0; j < g->children(); ++j)
                    if( !strcmp(g->child(j)->label(), logVariable.getElement(i).logVariable->getSubNames(logVariable.getElement(i).index)) )
                        selected = g->child(j);

                if(selected)
                {

                    PlotSelectedItem* newItem;
                    GlPlotWindow* glPlotWindow = dynamic_cast<GlPlotWindow*>(glWindow);

                    selectedGroup->begin();
                    newItem = new PlotSelectedItem(logVariable.getElement(i).logVariable, logVariable.getElement(i).index, selectMBrowser, glPlotWindow);
                    selectedGroup->end();
                    selectedLogVars.appendElement(newItem);
                    glPlotWindow->addLogVariableGUI(logVariable.getElement(i).logVariable, logVariable.getElement(i).index);

                    newItem->setColor(logVariable.getElement(i).r, logVariable.getElement(i).g, logVariable.getElement(i).b);

                    g->remove(selected);
                    delete selected;
                }
            }
            else
            {
                PlotSelectedItem* newItem;
                GlPlotWindow* glPlotWindow = dynamic_cast<GlPlotWindow*>(glWindow);

                selectedGroup->begin();
                newItem = new PlotSelectedItem(logVariable.getElement(i).logVariable, logVariable.getElement(i).index, selectMBrowser, glPlotWindow);
                selectedGroup->end();
                selectedLogVars.appendElement(newItem);
                glPlotWindow->addLogVariableGUI(logVariable.getElement(i).logVariable, logVariable.getElement(i).index);

                newItem->setColor(logVariable.getElement(i).r, logVariable.getElement(i).g, logVariable.getElement(i).b);

                selectMBrowser->remove(selected);
                delete selected;
            }
        }
    }

}

//==============================================================================
// PlotWindow::cbSelectAdd
//==============================================================================
void PlotWindow::cbSelectAdd(Widget *o, void* userData)
{
    o = o;
    PlotWindow* plot = (PlotWindow*) userData;
    LogVariableGUI* logVar;
    
    
    Widget* w = plot->selectMBrowser->goto_top();
    
    while(w)
    {
        if (w->selected())
        {
            Group* group = w->parent();
            // Log Degiskeni secilirse tum alt elementleri eklenir
            if(group->label() == NULL)
            {
                logVar = plot->findLogVariableGUI(w->label());
                if(logVar->getSize() == 1)
                {
                    plot->addNewPlotItem(logVar,0);
                }
                else
                {
                    Group* rootLog = (Group*)w;
                    for( int i = 0; i < rootLog->children(); ++i)
                    {
                        int row = atoi(strchr(rootLog->child(i)->label(),'(')+1);
                        int col = atoi(strrchr(rootLog->child(i)->label(),'(')+1);
                        int index = logVar->getCols()*row + col;
                        plot->addNewPlotItem(logVar,index);
                    }
                }
            }
            // Log Degiskeninin elemanlarindan birinin secilmesi
            else
            {
                logVar = plot->findLogVariableGUI(group->label());
                int row = atoi(strchr(w->label(),'(')+1);
                int col = atoi(strrchr(w->label(),'(')+1);
                int index = logVar->getCols()*row + col;
                plot->addNewPlotItem(logVar,index);
            }

            group->remove(w);
            delete w;
            w = plot->selectMBrowser->goto_top();

        } else {
            w = plot->selectMBrowser->next();

        }
    }
    plot->selectLogVarWindow->hide();
    plot->reallignSelected();
}

//==============================================================================
// PlotWindow::cbSelectAddAll
//==============================================================================
void PlotWindow::cbSelectAddAll(Widget *o, void* userData)
{
    PlotWindow* plot = (PlotWindow*) userData;
    for(int i = 0; i < plot->selectMBrowser->size(); ++i)
        plot->selectMBrowser->select(i, true);
    plot->cbSelectAdd(o,userData);
}

//==============================================================================
// PlotWindow::cbSelectCancel
//==============================================================================
void PlotWindow::cbSelectCancel(Widget *o, void* userData)
{
    userData = userData;
    Window* selectWindow = (Window*) o->window();
    selectWindow->hide();
}

//==============================================================================
// PlotWindow::fillList
//==============================================================================
void PlotWindow::fillList()
{
    Group* g;
    for(int i = 0; i < LogVariablesGUI->getNumElements(); ++i)
    {
        // Vector olmayan degiskenler icin
        if(LogVariablesGUI->getElement(i)->getSize() == 1)
        {
            selectMBrowser->add(LogVariablesGUI->getElement(i)->getName());
        }
        else
        {
            g = selectMBrowser->add_group (LogVariablesGUI->getElement(i)->getName(), selectMBrowser);
            for(int j = 0; j < LogVariablesGUI->getElement(i)->getSize(); ++j)            
                selectMBrowser->add_leaf(LogVariablesGUI->getElement(i)->getSubNames(j), g);               
        }
    }
}

//==============================================================================
// PlotWindow::addNewPlotItem
//==============================================================================
void PlotWindow::addNewPlotItem(LogVariableGUI* logVar, int element)
{
    int r,g,b;
    PlotSelectedItem* newItem;
    GlPlotWindow* glPlotWindow = dynamic_cast<GlPlotWindow*>(glWindow);
    
    selectedGroup->begin();
    newItem = new PlotSelectedItem(logVar,element,selectMBrowser,glPlotWindow);
    selectedGroup->end();
    selectedLogVars.appendElement(newItem);
    glPlotWindow->addLogVariableGUI(logVar,element);

    r = PlotBaseWindow::colorArray[colorIndex%colorSize][0];
    g = PlotBaseWindow::colorArray[colorIndex%colorSize][1];
    b = PlotBaseWindow::colorArray[colorIndex%colorSize][2];
    ++colorIndex;
    newItem->setColor(r,g,b);
}





