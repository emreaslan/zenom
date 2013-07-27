/*
 * SceneWindowManager.cpp
 *
 *  Created on: Dec 14, 2010
 *      Author: root
 */

#include "PlotXYWindowManager.h"

PlotXYWindowManager::PlotXYWindowManager()
: logVariableGUIArray(NULL)
{

}

PlotXYWindowManager::PlotXYWindowManager(Array< LogVariableGUI* >& pLogVariableGUIArray)
: logVariableGUIArray(&pLogVariableGUIArray)
{

}

PlotXYWindowManager::~PlotXYWindowManager()
{
	closeAllWindows();
}


void PlotXYWindowManager::newPlotXYWindow()
{
	clearHidedWindows();

    PlotXYWindow* newPlot;
    newPlot = new PlotXYWindow(*logVariableGUIArray, messenger);
    newPlot->show();
    plotXYWindows.appendElement(newPlot);
}


void PlotXYWindowManager::closeAllWindows()
{
	for(int i = 0; i < plotXYWindows.getNumElements(); ++i)
	{
		plotXYWindows[i]->hide();
		delete plotXYWindows[i];
	}
	plotXYWindows.removeAllElements();
}

void PlotXYWindowManager::enableWindows()
{
	clearHidedWindows();

    for (int i = 0; i < plotXYWindows.getNumElements(); ++i)
    {
    	plotXYWindows[i]->enable();
    }
}

void PlotXYWindowManager::disableWindows()
{
    for (int i = 0; i < plotXYWindows.getNumElements(); ++i)
    {
    	plotXYWindows[i]->disable();
    }
}

void PlotXYWindowManager::save(pugi::xml_node archive)
{
	clearHidedWindows();

    for (int i = 0; i < plotXYWindows.getNumElements(); ++i)
    {
    	plotXYWindows[i]->save(archive.append_child("PlotXYWindow"));
    }
}

void PlotXYWindowManager::load(pugi::xml_node archive)
{
	//Plot XY Window
	PlotXYWindow* newPlotXY;
    for ( pugi::xml_node newPlotXYNode = archive.first_child(); newPlotXYNode ; newPlotXYNode = newPlotXYNode.next_sibling() )
    {
        newPlotXY = new PlotXYWindow(*logVariableGUIArray, messenger);
        newPlotXY->load( newPlotXYNode);
        plotXYWindows.appendElement(newPlotXY);
        newPlotXY->show();
    }
}

void PlotXYWindowManager::clearHidedWindows()
{
	//Plot XY Window
	int i = 0;
    while( i < plotXYWindows.getNumElements())
    {
        if(!plotXYWindows[i]->visible())
        {
            delete plotXYWindows[i];
            plotXYWindows.removeElement(i);            
        }
        else
		{
            ++i;
		}
    }
}

void PlotXYWindowManager::setLogVariableArray(Array< LogVariableGUI* >& pLogVariableGUIArray)
{
	logVariableGUIArray = &pLogVariableGUIArray;
}

void PlotXYWindowManager::setMessenger(guiMessenger* pMessenger)
{
	messenger = pMessenger;
}
