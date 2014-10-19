//==============================================================================
// PlotXYWindow.cpp - PlotXY Window implementasyonu
//
// Author        :
// Version       :
// Compatibility : GCC
//==============================================================================

#include "PlotXYWindow.h"


//==============================================================================
// PlotXYWindow::PlotXYWindow
//==============================================================================
PlotXYWindow::PlotXYWindow( Array<LogVariableGUI*>& logVars, guiMessenger* messenger )
: PlotBaseWindow( logVars, (char*)"Plot XY Window" )
{

    selectAddButton->button()->callback(cbSelectAdd,this);
    selectAddAllButton->button()->callback(cbSelectAddAll,this);
    selectCancelButton->button()->callback(cbSelectCancel);
    autoTranslate->hide();

    begin();
    // GL
    glWindow = new GlPlotXYWindow(55,30,375,195);
    glWindow->set_double_buffer();
    glWindow->setMessengerObj(messenger);
    end();
    resizable(glWindow);
    
    fillList();
}

//==============================================================================
// PlotXYWindow::~PlotXYWindow
//==============================================================================
PlotXYWindow::~PlotXYWindow()
{
    delete glWindow;
}

//==============================================================================
// PlotXYWindow::enable
//==============================================================================
void PlotXYWindow::enable()
{
	menu->activate();
}

//==============================================================================
// PlotXYWindow::disable
//==============================================================================
void PlotXYWindow::disable()
{
	menu->deactivate();
}

//==============================================================================
// PlotXYWindow::save
//==============================================================================
void PlotXYWindow::save(pugi::xml_node pPlotXYWindowNode)
{
    pPlotXYWindowNode.append_attribute("X") = x();
    pPlotXYWindowNode.append_attribute("Y") = y();
    pPlotXYWindowNode.append_attribute("W") = w();
    pPlotXYWindowNode.append_attribute("H") = h();
    pPlotXYWindowNode.append_attribute("AutoScale") = autoScale->value();


    GlPlotXYWindow* glPlotXYWindow = dynamic_cast<GlPlotXYWindow*>(glWindow);
    glPlotXYWindow->save(pPlotXYWindowNode.append_child("Lines"));
    return;
}

//==============================================================================
// PlotXYWindow::load
//==============================================================================
void PlotXYWindow::load(pugi::xml_node pPlotXYWindowNode)
{
   resize(pPlotXYWindowNode.attribute("X").as_int(),
            pPlotXYWindowNode.attribute("Y").as_int(),
            pPlotXYWindowNode.attribute("W").as_int(),
            pPlotXYWindowNode.attribute("H").as_int());
    layout();

    autoScale->value( pPlotXYWindowNode.attribute("AutoScale").as_bool() );
    glWindow->setAutoScale(pPlotXYWindowNode.attribute("AutoScale").as_bool());


    Array<LogVarLine> lineVec;
    pugi::xml_node lineNodes = pPlotXYWindowNode.child("Lines");
    for ( pugi::xml_node line = lineNodes.first_child(); line; line = line.next_sibling() )
    {
        LogVarLine newLine;
        LogVariableGUI *logVarPtr = Utils::findLogVariableGUI(line.attribute("LogVariable").value());
        if( !logVarPtr)
            continue;
        newLine.logVariable = logVarPtr;
        newLine.r = line.attribute("R").as_int();
        newLine.g = line.attribute("G").as_int();
        newLine.b = line.attribute("B").as_int();
        lineVec.appendElement(newLine);
    }
    addLogVariable(lineVec);
    reallignSelected();
}

//==============================================================================
// PlotXYWindow::addLogVariable
//=============================================================================
void PlotXYWindow::addLogVariable( Array<LogVarLine>& logVariable )
{
    GlPlotXYWindow* glPlotXY = dynamic_cast<GlPlotXYWindow*>(glWindow);
    Widget* selected;

    for(int i = 0; i < logVariable.getNumElements(); ++i)
    {
        selected = NULL;
        for(int j = 0; j < selectMBrowser->size(); ++j)
            if( !strcmp(selectMBrowser->child(j)->label(), logVariable.getElement(i).logVariable->getName()) )
            {
                selected = selectMBrowser->child(j);
                break;
            }

        if (selected)
        {
            Group* group = selected->parent();

            selectedGroup->begin();
            PlotSelectedItem* newItem = new PlotSelectedItem(logVariable.getElement(i).logVariable, 0, selectMBrowser, glPlotXY);
            selectedGroup->end();
            selectedLogVars.appendElement(newItem);
            glPlotXY->addLogVariableGUI(logVariable.getElement(i).logVariable);

            newItem->setColor(logVariable.getElement(i).r, logVariable.getElement(i).g, logVariable.getElement(i).b);

            group->remove(selected);
            delete selected;
        }

    }
}


//==============================================================================
// PlotXYWindow::cbSelectAdd
//==============================================================================
void PlotXYWindow::cbSelectAdd(Widget *o, void* userData)
{
    o = o ;
    PlotXYWindow* plot = (PlotXYWindow*) userData;
    LogVariableGUI* logVar;
    PlotSelectedItem* newItem;
    ScrollGroup* selectedGroup = plot->selectedGroup;
    GlPlotXYWindow* glPlotXY = dynamic_cast<GlPlotXYWindow*>(plot->glWindow);
    int r,g,b;

    Widget* w = plot->selectMBrowser->goto_top();

    while(w)
    {
        if (w->selected())
        {
            Group* group = w->parent();
            // Log Degiskeni secilirse tum alt elementleri eklenir

            logVar = plot->findLogVariableGUI(w->label());
 
            selectedGroup->begin();
            newItem = new PlotSelectedItem(logVar,0,plot->selectMBrowser,glPlotXY);
            selectedGroup->end();
            plot->selectedLogVars.appendElement(newItem);
            glPlotXY->addLogVariableGUI(logVar);

            r = PlotBaseWindow::colorArray[plot->colorIndex%colorSize][0];
            g = PlotBaseWindow::colorArray[plot->colorIndex%colorSize][1];
            b = PlotBaseWindow::colorArray[plot->colorIndex%colorSize][2];
            ++plot->colorIndex;
            newItem->setColor(r,g,b);

            group->remove(w);
            w = plot->selectMBrowser->goto_top();

        } else {
            w = plot->selectMBrowser->next();

        }
    }
    plot->selectLogVarWindow->hide();
    plot->reallignSelected();
}

//==============================================================================
// PlotXYWindow::cbSelectAddAll
//==============================================================================
void PlotXYWindow::cbSelectAddAll(Widget *o, void* userData)
{
    PlotXYWindow* plot = (PlotXYWindow*) userData;
    for(int i = 0; i < plot->selectMBrowser->size(); ++i)
        plot->selectMBrowser->select(i, true);
    plot->cbSelectAdd(o,userData);
}

//==============================================================================
// PlotXYWindow::cbSelectCancel
//==============================================================================
void PlotXYWindow::cbSelectCancel(Widget *o, void* userData)
{
    userData = userData;
    Window* selectWindow = (Window*) o->window();
    selectWindow->hide();
}

//==============================================================================
// PlotXYWindow::fillList
//==============================================================================
void PlotXYWindow::fillList()
{
    // Sadece (1)(2) ve (2)(1) vektorler eklenir
    for(int i = 0; i < LogVariablesGUI->getNumElements(); ++i)
        if(LogVariablesGUI->getElement(i)->getSize() == 2)        
            selectMBrowser->add(LogVariablesGUI->getElement(i)->getName());
}

