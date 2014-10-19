/*
 * PlotWindowManager.h
 *
 *  Created on: Dec 14, 2010
 *      Author: root
 */

#ifndef PLOTWINDOWMANAGER_H
#define PLOTWINDOWMANAGER_H

#include "PlotWindow.h"
#include "Config.h"

class PlotWindowManager
{
public:
	PlotWindowManager();
	PlotWindowManager(Array< LogVariableGUI* >& pLogVariableGUIArray);
	~PlotWindowManager();
	void newPlotWindow();
	void closeAllWindows();
	void enableWindows();
	void disableWindows();
	void save(pugi::xml_node archive);
	void load(pugi::xml_node archive);
	void setLogVariableArray(Array< LogVariableGUI* >& pLogVariableGUIArray);
	void setMessenger(guiMessenger* pMessenger);

private:
	void clearHidedWindows();
	Array< PlotWindow* > plotWindows;
	guiMessenger* messenger;	//TODO silinecek
	Array< LogVariableGUI* >* logVariableGUIArray;
};

#endif /* PLOTWINDOWMANAGER_H */
