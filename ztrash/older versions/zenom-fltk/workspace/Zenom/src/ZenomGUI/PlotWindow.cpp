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
// PlotWindow::enable
//==============================================================================
void PlotWindow::enable()
{
	menu->activate();
}

//==============================================================================
// PlotWindow::disable
//==============================================================================
void PlotWindow::disable()
{
	menu->deactivate();
}

//==============================================================================
// PlotWindow::save
//==============================================================================
void PlotWindow::save(pugi::xml_node pPlotWindowNode)
{
    pPlotWindowNode.append_attribute("X") = x();
    pPlotWindowNode.append_attribute("Y") = y();
    pPlotWindowNode.append_attribute("W") = w();
    pPlotWindowNode.append_attribute("H") = h();
    pPlotWindowNode.append_attribute("AutoScale") = autoScale->value();
    pPlotWindowNode.append_attribute("AutoTranslate") = autoTranslate->value();


    GlPlotWindow* glPlotWindow = dynamic_cast<GlPlotWindow*>(glWindow);
    glPlotWindow->save(pPlotWindowNode.append_child("Lines")) ;
    
    return;
}

//==============================================================================
// PlotWindow::load
//==============================================================================
void PlotWindow::load(pugi::xml_node pPlotWindowNode)
{
    resize(pPlotWindowNode.attribute("X").as_int(),
            pPlotWindowNode.attribute("Y").as_int(),
            pPlotWindowNode.attribute("W").as_int(),
            pPlotWindowNode.attribute("H").as_int());
    layout();

    autoScale->value( pPlotWindowNode.attribute("AutoScale").as_bool() );
    autoTranslate->value( pPlotWindowNode.attribute("AutoTranslate").as_bool() );
    glWindow->setAutoScale(pPlotWindowNode.attribute("AutoScale").as_bool());
    glWindow->setAutoTranslate(pPlotWindowNode.attribute("AutoTranslate").as_bool());


    Array<LogVarLine> lineVec;
    pugi::xml_node lineNodes = pPlotWindowNode.child("Lines");
    for ( pugi::xml_node line = lineNodes.first_child(); line; line = line.next_sibling() )
    {
        LogVarLine newLine;
        LogVariableGUI *logVarPtr = Utils::findLogVariableGUI(line.attribute("LogVariable").value());
        if( !logVarPtr)
            continue;
        newLine.logVariable = logVarPtr;
        newLine.index = line.attribute("Index").as_int();
        newLine.r = line.attribute("R").as_int();
        newLine.g = line.attribute("G").as_int();
        newLine.b = line.attribute("B").as_int();
        lineVec.appendElement(newLine);
    }
    addLogVariable(lineVec);
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





