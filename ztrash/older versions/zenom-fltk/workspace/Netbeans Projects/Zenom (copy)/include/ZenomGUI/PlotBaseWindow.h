#ifndef _PLOTBASEWINDOW_H
#define	_PLOTBASEWINDOW_H

#include <fltk/run.h>
#include <fltk/math.h>
#include <fltk/Group.h>
#include <fltk/Window.h>
#include <fltk/Button.h>
#include <fltk/ThumbWheel.h>
#include <fltk/MenuBar.h>
#include <fltk/MultiBrowser.h>
#include <fltk/ColorChooser.h>
#include <fltk/CheckButton.h>
#include <fltk/ScrollGroup.h>
#include <fltk/events.h>
#include <fltk/StatusBarGroup.h>
#include <fltk/FileChooser.h>

#include "Array.h"
#include "LogVariableGUI.h"
#include "guiMessenger.h"
#include "GlPlotWindowBase.h"
#include "PlotSelectedItem.h"
#include "ZButton.h"
#include "Config.h"

#include <cstring>
#include <cstdlib>
#include <fstream>

using namespace fltk;


/**
 * PlotBaseWindow class.
 * Log degiskeni degerlerini grafik olarak gosterecek Plot ve PlotXY
 * pencereleri icin temel siniftir.
 */

class PlotBaseWindow : public Window
{
public:

    /**
     * Constructor
     * Control degiskenleri ile bir pencere olusturur.
     * @param logVars Log degiskenleri dizisi
     * @param name    Pencere ismi
     */
    PlotBaseWindow( Array<LogVariableGUI*>& logVars, char* name );
    
    /** Sistemden alinan yerler geri verilir */
    virtual ~PlotBaseWindow();

protected:

    virtual int handle(int e);

    static void cbTranslateX (Widget* widget, void* );
    
    static void cbZoomY (Widget* widget, void* );

    static void cbTranslateY (Widget* widget, void* );

    static void cbZoomX (Widget* widget, void* );

    static void cbAutoScale(Widget* o, long userData);

    static void cbAutoTranslate( Widget* o, long userData );

    static void cbSelectWindow(Widget *o, void* userData);

    static void cbExportAsMatlab(Widget *o, void*);

    /** Pencere border icin kutu */
    Group* gbox;

    /** Plot Penceresi menu */
    MenuBar* menu;

    /** Menudeki ekleme butonu*/
    Button* addButton;

    /** Menude matlab butonu */
    Button *exportAsMatlab;

    /** GL ekraninda X ekseninde zoom yapilmasini sayglayan thumbwheel*/
    ThumbWheel *zoomXthumb;

    /** GL ekraninda Y ekseninde zoom yapilmasini sayglayan thumbwheel*/
    ThumbWheel *zoomYthumb;

    /** GL ekraninda X ekseninde oteleme yapilmasini sayglayan thumbwheel*/
    ThumbWheel *translateXthumb;

    /** GL ekraninda Y ekseninde oteleme yapilmasini sayglayan thumbwheel*/
    ThumbWheel *translateYthumb;

    /** GL ekraninda grafikin otomatik boyutlandirma secenegi icin checkbox*/
    CheckButton* autoScale;

    /** GL ekraninda grafikin otomatik oteleme secenegi icin checkbox*/
    CheckButton* autoTranslate;

    /** Grafik gosterimi icin GL ekrani */
    GlPlotWindowBase* glWindow;
    
    /** Alttaki status bar */
    StatusBarGroup* statusBar;

    //  ----- Plot Select Window -----

    /** Plot window icin Log Degskeni secim penceresi*/
    Window* selectLogVarWindow;

    /** Degisken secim penceresindeki browser */
    MultiBrowser* selectMBrowser;

    /** Degisken secim penceresindeki  ekleme butonu*/
    ZButton* selectAddButton;

    /** Degisken secim penceresindeki  hepsini ekle butonu*/
    ZButton* selectAddAllButton;

    /** Degisken secim penceresindeki  iptal butonu*/
    ZButton* selectCancelButton;

    //  ----- Plot Select Window -----

    LogVariableGUI* findLogVariableGUI(const char* name);

    /** Grafikte cizilen bir log degiskeni silinmesi durumunda 
     *  legend yapisini siralar.
     */
    void reallignSelected();
        
    /** Log degiskenleri dizisini tutan pointer */
    Array<LogVariableGUI*>* LogVariablesGUI;

    /** Grafikte cizilen log degiskenleri */
    Array< PlotSelectedItem* > selectedLogVars;

    ScrollGroup* selectedGroup;

    int colorIndex;

    const static int colorSize = 6;

    /** Renklerin tutuldugu dizi */
    const static int colorArray[PlotBaseWindow::colorSize][3];

    /** Onceki verileri tutan deger */
    double preZoomX;
    double preZoomY;
    double preTranslateX;
    double preTranslateY;

    /** Onceki verileri tutan deger */
    double currentZoomX;
    double currentZoomY;
    double currentTranslateX;
    double currentTranslateY;
};

#endif	/* _PLOTBASEWINDOW_H */

