//==============================================================================
// PlotSelectedItem.cpp - Plot Selected Item Window implementasyonu
//
// Author        :
// Version       :
// Compatibility : GCC
//==============================================================================

#include <fltk/Font.h>

#include "PlotSelectedItem.h"

//==============================================================================
// PlotSelectedItem::PlotSelectedItem
//==============================================================================
PlotSelectedItem::PlotSelectedItem(LogVariableGUI* logVar, int index,
        MultiBrowser* mBrowser, GlPlotWindow* gl) : Group(0, 0, 130, 20)
{

    logVarGUI = logVar;
    element = index;
    glWindow = gl;
    selectedMBrowser = mBrowser;
    isPlotXY = false;

    box(fltk::FLAT_BOX);
    color(fltk::GRAY90);
    begin();
    if(logVar->getSize() == 1)
        colorButton = new Button( 0, 0, 20, 20, logVar->getName() );        
    else
        colorButton = new Button( 0, 0, 20, 20, logVar->getSubNames(element) );
    colorButton->align(fltk::ALIGN_RIGHT);
    colorButton->box(fltk::EMBOSSED_BOX);
    colorButton->color(BLUE);
    colorButton->callback( cbChangeColor );

    closeButton = new Button( 113, 2, 15, 16,"X");
    closeButton->box(fltk::FLAT_BOX);
    closeButton->color(fltk::GRAY85);
    closeButton->highlight_color(fltk::color(217,54,54));
    closeButton->highlight_textcolor(fltk::GRAY95);
    closeButton->labelcolor(fltk::color(217,54,54));
    closeButton->callback(cbClose);
    end();    
}

//==============================================================================
// PlotSelectedItem::PlotSelectedItem
//==============================================================================
PlotSelectedItem::PlotSelectedItem(LogVariableGUI* logVar, int index,
        MultiBrowser* mBrowser, GlPlotXYWindow* gl) : Group(0, 0, 120, 20)
{

    logVarGUI = logVar;
    element = index;
    glWindow = gl;
    selectedMBrowser = mBrowser;
    isPlotXY = true;

    box(fltk::FLAT_BOX);
    color(fltk::GRAY90);
    begin();
    colorButton = new Button( 0, 0, 20, 20, logVar->getName() );
    colorButton->align(fltk::ALIGN_RIGHT);
    colorButton->box(fltk::EMBOSSED_BOX);
    colorButton->color(BLUE);
    colorButton->callback( cbChangeColor );

    closeButton = new Button( 103, 2, 15, 16,"X");
    closeButton->box(fltk::FLAT_BOX);
    closeButton->color(fltk::GRAY85);
    closeButton->highlight_color(fltk::color(217,54,54));
    closeButton->highlight_textcolor(fltk::GRAY95);
    closeButton->labelcolor(fltk::color(217,54,54));
    closeButton->callback(cbClose);
    end();
}

//==============================================================================
// PlotSelectedItem::~PlotSelectedItem
//==============================================================================
PlotSelectedItem::~PlotSelectedItem()
{
    delete colorButton;
    delete closeButton;
}

//==============================================================================
// PlotSelectedItem::cbClose
//==============================================================================
void PlotSelectedItem::cbClose(Widget *o, void* userData)
{
    userData = userData;
    PlotSelectedItem* selectedItem = (PlotSelectedItem*) o->parent();
    LogVariableGUI* logVar = selectedItem->logVarGUI;
    MultiBrowser* mBrowser = selectedItem->selectedMBrowser;

    if(selectedItem->logVarGUI->getSize() == 1 || selectedItem->isPlotXY)
    {
        // Browsera eklenir
        mBrowser->add(logVar->getName());
        
        if(selectedItem->isPlotXY)
        {
            GlPlotXYWindow* glPlotXYWindow = dynamic_cast<GlPlotXYWindow*>(selectedItem->glWindow);
            glPlotXYWindow->removeLogVariableGUI(logVar);            
        }
        else
        {
            GlPlotWindow* glPlotWindow = dynamic_cast<GlPlotWindow*>(selectedItem->glWindow);
            glPlotWindow->removeLogVariableGUI(logVar,selectedItem->element);
        }
    }
    else
    {
        Group* parent = selectedItem->findParentInBrowser(logVar->getName());
        if( parent == NULL )
            parent = mBrowser->add_group (logVar->getName(), mBrowser);
        mBrowser->add_leaf(logVar->getSubNames(selectedItem->element), parent);

        GlPlotWindow* glPlotWindow = dynamic_cast<GlPlotWindow*>(selectedItem->glWindow);
        glPlotWindow->removeLogVariableGUI(logVar,selectedItem->element);
               
    }
    
    selectedItem->logVarGUI->setMouseOver(selectedItem->element,false);
    selectedItem->hide();
    selectedItem->window()->handle(50);
}

//==============================================================================
// PlotSelectedItem::cbChangeColor
//==============================================================================
void PlotSelectedItem::cbChangeColor( Widget* o, void* userData )
{
    userData = userData;
    PlotSelectedItem* selectedItem = (PlotSelectedItem*) o->parent();
    Button *colorButton = (Button*)o;
    uchar r, g, b;
    
    fltk::split_color(o->parent()->color(),r,g,b);

    if (!fltk::color_chooser("New color:", r,g,b))
        return;

    
    if(selectedItem->isPlotXY)
    {
        GlPlotXYWindow* glPlotXYWindow = dynamic_cast<GlPlotXYWindow*>(selectedItem->glWindow);
        glPlotXYWindow->changeLogColor(selectedItem->logVarGUI,r,g,b);        
    }
    else
    {
        GlPlotWindow* glPlotWindow = dynamic_cast<GlPlotWindow*>(selectedItem->glWindow);
        glPlotWindow->changeLogColor(selectedItem->logVarGUI,selectedItem->element,r,g,b);
    }
    colorButton->color(fltk::color(r,g,b));
    colorButton->redraw();
}

//==============================================================================
// PlotSelectedItem::setColor
//==============================================================================
void PlotSelectedItem::setColor(int r, int g, int b)
{   
    if(isPlotXY)
    {
        GlPlotXYWindow* glPlotXYWindow = dynamic_cast<GlPlotXYWindow*>(glWindow);
        glPlotXYWindow->changeLogColor(logVarGUI,r,g,b);
    }
    else
    {
        GlPlotWindow* glPlotWindow = dynamic_cast<GlPlotWindow*>(glWindow);
        glPlotWindow->changeLogColor(logVarGUI,element,r,g,b);
    }

    colorButton->color(fltk::color(r,g,b));
    colorButton->redraw();
}

//==============================================================================
// PlotSelectedItem::findParentInBrowser
//==============================================================================
Group* PlotSelectedItem::findParentInBrowser(const char* name)
{
    Group* g;
    for(int i = 0; i < selectedMBrowser->size(); ++i)
    {
        g = (Group*)selectedMBrowser->goto_index(i);
        if(!strcmp(g->label(),name))
            return g;
    }

    return NULL;
}

//==============================================================================
// PlotSelectedItem::handle
//==============================================================================
int PlotSelectedItem::handle(int e)
{
    switch(e)
    {
        case ENTER:
            logVarGUI->setMouseOver(element,true);
            colorButton->labeltype(fltk::EMBOSSED_LABEL);
            break;

        case LEAVE:
            logVarGUI->setMouseOver(element,false);
            colorButton->labeltype(fltk::NORMAL_LABEL);
            break;
    }

    colorButton->parent()->redraw();
    return fltk::Group::handle(e);
}




