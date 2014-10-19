

#include <fltk/run.h>
#include "SceneWindow.h"


#include "LogVariableGUI.h"
#include "Array.h"


void timeout_callback(void* v)
{
    SceneWindow* sw = (SceneWindow*)v;
    sw->update();
    sw->redraw();


    fltk::repeat_timeout(1.0/20,timeout_callback,v);
}


int main(int argc, char **argv)
{
    
    Array<LogVariableGUI*> logVariables;

    double dValue = 2;
    LogVariableGUI* temp = new LogVariableGUI(dValue, "1x1", "", 1, 1);
    logVariables.appendElement(temp);

    double* dValueArray = new double[3];
    temp = new LogVariableGUI(dValueArray, "1x3", "", 1, 3);
    logVariables.appendElement(temp);

    dValueArray = new double[3];
    temp = new LogVariableGUI(dValueArray, "3x1", "", 3, 1);
    logVariables.appendElement(temp);

    dValueArray = new double[15];
    temp = new LogVariableGUI(dValueArray, "5x3", "", 5, 3);
    logVariables.appendElement(temp);

    dValueArray = new double[18];
    temp = new LogVariableGUI(dValueArray, "6x3", "", 6, 3);
    logVariables.appendElement(temp);

    dValueArray = new double[22];
    temp = new LogVariableGUI(dValueArray, "22x1", "", 22, 1);
    logVariables.appendElement(temp);

    dValueArray = new double[23];
    temp = new LogVariableGUI(dValueArray, "23x1", "", 23, 1);
    logVariables.appendElement(temp);

    dValueArray = new double[15];
    temp = new LogVariableGUI(dValueArray, "3x5", "", 3, 5);
    logVariables.appendElement(temp);

    dValueArray = new double[4];
    temp = new LogVariableGUI(dValueArray, "2x2", "", 2, 2);
    logVariables.appendElement(temp);

    SceneWindowConfig config;
    config.x = 30;
    config.y = 30;
    config.w = 800;
    config.h = 600;

    config.vrmlFiles.appendElement("/home/CuneyT/Desktop/son/scenewindow/test/snowman.wrl");

    SceneBindVariableConfig bindedVrmlVariable;
    bindedVrmlVariable.logVarIndex = 2;
    bindedVrmlVariable.logVariable = temp;
    bindedVrmlVariable.vrmlFilename = "snowman.wrl";
    bindedVrmlVariable.vrmlIndex.appendElement(0);
    bindedVrmlVariable.vrmlIndex.appendElement(4);
    bindedVrmlVariable.vrmlIndex.appendElement(5);
    bindedVrmlVariable.vrmlIndex.appendElement(1);
    bindedVrmlVariable.vrmlIndex.appendElement(0);

    config.bindedVariable.appendElement(bindedVrmlVariable);
    
    SceneWindow scene(logVariables);

    //scene.load(&config);

    scene.show();

    return fltk::run();
}

