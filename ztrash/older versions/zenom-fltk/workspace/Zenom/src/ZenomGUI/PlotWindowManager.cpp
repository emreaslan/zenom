/*
 * SceneWindowManager.cpp
 *
 *  Created on: Dec 14, 2010
 *      Author: root
 */

#include "PlotWindowManager.h"

PlotWindowManager::PlotWindowManager()
: logVariableGUIArray(NULL)
{

}

PlotWindowManager::PlotWindowManager(Array< LogVariableGUI* >& pLogVariableGUIArray)
: logVariableGUIArray(&pLogVariableGUIArray)
{

}

PlotWindowManager::~PlotWindowManager()
{
	closeAllWindows();
}

void PlotWindowManager::newPlotWindow()
{
	clearHidedWindows();

    PlotWindow* newPlot;
    newPlot = new PlotWindow(*logVariableGUIArray, messenger);
    newPlot->show();
    plotWindows.appendElement(newPlot);
}

void PlotWindowManager::closeAllWindows()
{
	for(int i = 0; i < plotWindows.getNumElements(); ++i)
	{
		plotWindows[i]->hide();
		delete plotWindows[i];
	}
	plotWindows.removeAllElements();
}

void PlotWindowManager::enableWindows()
{
	clearHidedWindows();

    for (int i = 0; i < plotWindows.getNumElements(); ++i)
    {
		plotWindows[i]->enable();
    }
}

void PlotWindowManager::disableWindows()
{
    for (int i = 0; i < plotWindows.getNumElements(); ++i)
    {
		plotWindows[i]->disable();
    }
}

void PlotWindowManager::save(pugi::xml_node archive)
{
	clearHidedWindows();

	// Plot Window
    for (int i = 0; i < plotWindows.getNumElements(); ++i)
    {
		plotWindows[i]->save(archive.append_child("PlotWindow"));
    }
}

void PlotWindowManager::load(pugi::xml_node archive)
{
	// Plot Window
    PlotWindow* newPlot;
    for ( pugi::xml_node newPlotNode = archive.first_child(); newPlotNode ; newPlotNode = newPlotNode.next_sibling() )
    {
        newPlot = new PlotWindow(*logVariableGUIArray, messenger);
        newPlot->load( newPlotNode);
		plotWindows.appendElement(newPlot); 
		newPlot->show();              
    }
}

void PlotWindowManager::clearHidedWindows()
{
	//Plot Window
	int i = 0;
    while( i < plotWindows.getNumElements())
    {
        if(!plotWindows.getElement(i)->visible())
        {
            delete plotWindows.getElement(i);
            plotWindows.removeElement(i);            
        }
        else
		{
            ++i;
		}
    }
}

void PlotWindowManager::setLogVariableArray(Array< LogVariableGUI* >& pLogVariableGUIArray)
{
	logVariableGUIArray = &pLogVariableGUIArray;
}

void PlotWindowManager::setMessenger(guiMessenger* pMessenger)
{
	messenger = pMessenger;
}
