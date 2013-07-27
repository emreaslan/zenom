/*
 * SceneWindowManager.h
 *
 *  Created on: Dec 14, 2010
 *      Author: root
 */

#ifndef SCENEWINDOWMANAGER_H
#define SCENEWINDOWMANAGER_H

#include "SceneWindow.h"
#include "Config.h"

class SceneWindowManager
{
public:
	SceneWindowManager();
	SceneWindowManager(Array< LogVariableGUI* >& pLogVariableGUIArray);
	~SceneWindowManager();
	void newSceneWindow();
	void closeAllWindows();
	void enableWindows();
	void disableWindows();
	void save(pugi::xml_node archive);
	void load(pugi::xml_node archive);
	void update();
	void setLogVariableArray(Array< LogVariableGUI* >& pLogVariableGUIArray);

private:
	void clearHidedWindows();
	Array< SceneWindow* > sceneWindows;
	Array< LogVariableGUI* >* logVariableGUIArray;
};

#endif /* SCENEWINDOWMANAGER_H */
