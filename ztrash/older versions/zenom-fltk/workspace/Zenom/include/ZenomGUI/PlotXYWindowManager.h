/*
 * PlotWindowManager.h
 *
 *  Created on: Dec 14, 2010
 *      Author: root
 */

#ifndef PLOTXYWINDOWMANAGER_H
#define PLOTXYWINDOWMANAGER_H

#include "PlotXYWindow.h"
#include "Config.h"

class PlotXYWindowManager
{
public:
	PlotXYWindowManager();
	PlotXYWindowManager(Array< LogVariableGUI* >& pLogVariableGUIArray);
	~PlotXYWindowManager();
	void newPlotXYWindow();
	void closeAllWindows();
	void enableWindows();
	void disableWindows();
	void save(pugi::xml_node archive);
	void load(pugi::xml_node archive);
	void setLogVariableArray(Array< LogVariableGUI* >& pLogVariableGUIArray);
	void setMessenger(guiMessenger* pMessenger);

private:
	void clearHidedWindows();
	Array< PlotXYWindow* > plotXYWindows;
	guiMessenger* messenger;	//TODO silinecek
	Array< LogVariableGUI* >* logVariableGUIArray;
};

#endif /* PLOTXYWINDOWMANAGER_H */
