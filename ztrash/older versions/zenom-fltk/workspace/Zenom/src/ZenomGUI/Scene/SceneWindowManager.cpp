/*
 * SceneWindowManager.cpp
 *
 *  Created on: Dec 14, 2010
 *      Author: root
 */

#include "SceneWindowManager.h"

SceneWindowManager::SceneWindowManager()
: logVariableGUIArray(NULL)
{

}

SceneWindowManager::SceneWindowManager(Array< LogVariableGUI* >& pLogVariableGUIArray)
: logVariableGUIArray(&pLogVariableGUIArray)
{

}

SceneWindowManager::~SceneWindowManager()
{
	closeAllWindows();
}

void SceneWindowManager::newSceneWindow()
{
	clearHidedWindows();

	SceneWindow* newScene;
    newScene = new SceneWindow(*logVariableGUIArray);
    newScene->show();
    sceneWindows.appendElement(newScene);
}

void SceneWindowManager::closeAllWindows()
{
	for(int i = 0; i < sceneWindows.getNumElements(); ++i)
	{
		sceneWindows[i]->hide();
		delete sceneWindows[i];
	}
	sceneWindows.removeAllElements();
}

void SceneWindowManager::enableWindows()
{
	clearHidedWindows();

    for (int i = 0; i < sceneWindows.getNumElements() ; ++i)
    {
        sceneWindows[i]->enable();
    }
}

void SceneWindowManager::disableWindows()
{
    for (int i = 0; i < sceneWindows.getNumElements() ; ++i)
    {
        sceneWindows[i]->disable();
    }
}

void SceneWindowManager::save(pugi::xml_node archive)
{
	clearHidedWindows();

    for (int i = 0; i < sceneWindows.getNumElements() ; ++i)
    {
        sceneWindows[i]->save(archive.append_child("SceneWindow"));
    }
}

void SceneWindowManager::load(pugi::xml_node archive)
{
    cout << "Opening Scene windows" << endl;
    SceneWindow* newScene;
    for (pugi::xml_node newSceneNode = archive.first_child(); newSceneNode; newSceneNode = newSceneNode.next_sibling())
    {
        newScene = new SceneWindow(*logVariableGUIArray);

        newScene->load( newSceneNode );
        newScene->show();

        sceneWindows.appendElement(newScene);
    }
}

void SceneWindowManager::clearHidedWindows()
{
	int i = 0;
	while( i < sceneWindows.getNumElements())
	{
		if(!sceneWindows[i]->visible())
	    {
			delete sceneWindows[i];
			sceneWindows.removeElement(i);
	    }
		else
		{
			++i;
	    }
	}
}

void SceneWindowManager::update()
{
	for( int i = 0; i < sceneWindows.getNumElements(); ++i)
		sceneWindows[i]->update();
}

void SceneWindowManager::setLogVariableArray(Array< LogVariableGUI* >& pLogVariableGUIArray)
{
	logVariableGUIArray = &pLogVariableGUIArray;
}
