#ifndef _SCENEWINDOW_H
#define	_SCENEWINDOW_H

#include <fltk/run.h>
#include <fltk/math.h>
#include <fltk/Group.h>
#include <fltk/Window.h>
#include <fltk/StatusBarGroup.h>
#include <fltk/MenuBar.h>
#include <fltk/FileChooser.h>

#include "Config.h"
#include "ZButton.h"
#include "Scene.h"

#include "LogVariableGUI.h"

using namespace fltk;

/**
 * SceneWindow class.
 * Scene penceresi
 *
 */

class SceneWindow : public Window
{
public:

    /**
     * Constructor
     * Temel ozelliklere scene penceresi olusturur.
     */
    SceneWindow(Array<LogVariableGUI*>& logVars);
    
    /**
     * Destructor
     * Sistemden alinan yerler geri verilir.
     */
    virtual ~SceneWindow();


    void update();


    void load(SceneWindowConfig *config);

    SceneWindowConfig save();

private:

    struct BindedVariable
    {
        BindedVariable(Widget* vrml, LogVariableGUI* log, int pIndex = 0)
                : vrmlVariableWidget(vrml), logVariable(log), index(pIndex)
        {
            ZParameter* vrmlVariable = static_cast<ZParameter*>(vrmlVariableWidget->user_data());
            switch(vrmlVariable->type)
            {
                case Z_DOUBLE:
                {
                    double *oldd = new double;
                    (*oldd)      = *(static_cast<double*>(vrmlVariable->variable));
                    double a = *oldd;
                    oldValue = oldd;
                    break;
                }
                case Z_INTEGER:
                {
                    int *oldi = new int;
                    (*oldi)      = *(static_cast<int*>(vrmlVariable->variable));
                    oldValue = oldi;
                    break;
                }
                case Z_BOOLEAN:
                {
                    bool *oldb = new bool;
                    (*oldb)      = *(static_cast<bool*>(vrmlVariable->variable));
                    oldValue = oldb;
                    break;
                }
            }
        }


        BindedVariable(const BindedVariable& pRight)
                : vrmlVariableWidget(pRight.vrmlVariableWidget), logVariable(pRight.logVariable), index(pRight.index)
        {
            ZParameter* vrmlVariable = static_cast<ZParameter*>(vrmlVariableWidget->user_data());
            switch(vrmlVariable->type)
            {
                case Z_DOUBLE:
                {
                    double *oldd = new double;
                    (*oldd)      = *(static_cast<double*>(vrmlVariable->variable));
                    oldValue = oldd;
                    break;
                }
                case Z_INTEGER:
                {
                    int *oldi = new int;
                    (*oldi)      = *(static_cast<int*>(vrmlVariable->variable));
                    oldValue = oldi;
                    break;
                }
                case Z_BOOLEAN:
                {
                    bool *oldb = new bool;
                    (*oldb)      = *(static_cast<bool*>(vrmlVariable->variable));
                    oldValue = oldb;
                    break;
                }
            }
        }

        ~BindedVariable()
        {
            ZParameter* vrmlVariable = static_cast<ZParameter*>(vrmlVariableWidget->user_data());
            switch(vrmlVariable->type)
            {
                case Z_DOUBLE:
                {
                    delete static_cast<double*>(oldValue);
                    break;
                }
                case Z_INTEGER:
                {
                    delete static_cast<int*>(oldValue);
                    break;
                }
                case Z_BOOLEAN:
                {
                    delete static_cast<bool*>(oldValue);
                    break;
                }
            }
        }

        void reset()
        {
            ZParameter* vrmlVariable = static_cast<ZParameter*>(vrmlVariableWidget->user_data());
            switch(vrmlVariable->type)
            {
                case Z_DOUBLE:
                {
                    double* vrmld = static_cast<double*>(vrmlVariable->variable);
                    *vrmld = *static_cast<double*>(oldValue);
                    break;
                }
                case Z_INTEGER:
                {
                    int* vrmli = static_cast<int*>(vrmlVariable->variable);
                    *vrmli = *static_cast<int*>(oldValue);
                    break;
                }
                case Z_BOOLEAN:
                {
                    bool* vrmlb = static_cast<bool*>(vrmlVariable->variable);
                    *vrmlb = *static_cast<bool*>(oldValue);
                    break;
                }
            }
        }        
        
        Widget* vrmlVariableWidget;
        LogVariableGUI *logVariable;
        int index;
        void* oldValue;
    };

    void disableButtons();

    void enableButtons();
        
    static void cbLoad(Widget *o, void* userData);
    int loadVRMLFile(const char* filename);

    static void cbChangeMode(Widget* w, void* arg);

    static void cbBind(Widget *o, void* userData);

    static void cbRotate(Widget *o, void* userData);

    static void cbHeadlight(Widget *o, void* userData);
    void headlight();

    /** Pencere border icin kutu */
    Group* gbox;

    /** Plot Penceresi menu */
    MenuBar* menu;

    /** Menudeki vrml yukleme butonu*/
    Button* loadButton;

    /** Menudeki vrml-log degiskeni baglama butonu*/
    Button* bindButton;

    /** Alttaki status bar */
    StatusBarGroup* statusBar;


    Group* buttonGroup;

    /** Navigasyon group */
    Group* navigateGroup;
    ZButton *rotateLeftButton;
    ZButton *rotateRightButton;
    ZButton *rotateUpButton;
    ZButton *rotateDownButton;
    ZButton *rotateCenterButton;
    ZButton *rotateButton;
    ZButton *panButton;

    /** Camera group */
    Group* cameraGroup;
    ZButton *nextCameraButton;
    ZButton *prevCameraButton;
    
    ZButton *headlightButton;

    /** opengl ekrani */
    Scene* scene;

    bool isPanMode;

    /** Log degiskenleri dizisini tutan pointer */
    Array<LogVariableGUI*>& LogVariablesGUI;


    Array<const char*> bindedVariableName;

    Array<BindedVariable*> bindedVariable;
    
    Array<BindedVariable*> bindedVariableNotApply;



    
    /** SCENE BIND WINDOW */
    /** Vrml - Log degiskenleri baglamaya yarayan arayuz penceresidir */
    Window* sceneBindWindow;

    /** Gorsellik icin */
    Group* gboxSelect;

    /** Vrml Secme tablosu */
    Browser* vrmlVariableList;

    /** Log Secme tablosu */
    Browser* logVariableList;

    /** Log degiskeni ile vrml objesini baglar */
    ZButton *bindVariableButton;

    /** Log degiskeni ile vrml objesi bagini kaldirir */
    ZButton *unbindVariableButton;

    /** Butun Log degiskeni ile vrml objesi bagini kaldirir */
    ZButton *unbindAllVariableButton;

    /** Log degiskeni ile vrml objesini baglari onaylanir */
    ZButton *oKBindButton;

    /** Log degiskeni ile vrml objesi baglari onaylanmaz */
    ZButton *cancelBindButton;

    /** Callback Fonksiyonlari */
    static void cbBindVariable(Widget* w, void* arg);
    void bindVariable(Widget* wrmlVariableWidget, Widget* logVariableWidget);

    static void cbUnbindVariable(Widget* w, void* arg);
    void unbindVariable(Widget* vrmlWidget);
    void removeUnbindVariable(Widget* vrmlWidget);

    static void cbUnbindAllVariable(Widget* w, void* arg);

    static void cbCancelBindVariable(Widget* w, void* arg);

    static void cbOkBindVariable(Widget* w, void* arg);

    static void cbChangedVrmlList(Widget* w, void* arg);

    void fillLogVariableList();

    void updateLogVariableBrowser();    

    /** SCENE SELECT WINDOW */

};

#endif	/* _SCENEWINDOW_H */
