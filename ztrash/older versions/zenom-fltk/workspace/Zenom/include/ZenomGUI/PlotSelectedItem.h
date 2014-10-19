#ifndef _PLOTSELECTEDITEM_H
#define	_PLOTSELECTEDITEM_H

#include <fltk/Window.h>
#include <fltk/Group.h>
#include <fltk/Button.h>
#include <fltk/events.h>
#include <fltk/MultiBrowser.h>
#include <fltk/ColorChooser.h>

#include "LogVariableGUI.h"
#include "GlPlotWindow.h"
#include "GlPlotXYWindow.h"

using namespace fltk;

/**
 * PlotSelectedItem class.
 * PlotXY ve Plot pencerelerinde grafiksel cizimi yapilacak log degiskenleri
 * renk degistireme, grafikten cikarma islemlerini saglayan legend elemanidir. 
 */

class PlotSelectedItem : public Group
{
public:
    /**
     * Constructor
     * Control degiskenleri ile bir pencere olusturur.
     * @param logVar      Grafiksel gosterilecek Log degiskeni
     * @param index       Grafiksel gosterilecek Log degiskeni indexi
     * @param mBrowser    Kapatilma isleminde degiskenin eklenecegi liste
     * @param gl          Renk degisimi ve grafikten silinme bilgisinin iletilecegi
     *                    gl ekrani 
     */
    PlotSelectedItem(LogVariableGUI* logVar, int index, MultiBrowser* mBrowser,
            GlPlotWindow* gl);

    /**
     * Constructor
     * Control degiskenleri ile bir pencere olusturur.
     * @param logVar      Grafiksel gosterilecek Log degiskeni
     * @param index       Grafiksel gosterilecek Log degiskeni indexi
     * @param mBrowser    Kapatilma isleminde degiskenin eklenecegi liste
     * @param gl          Renk degisimi ve grafikten silinme bilgisinin iletilecegi
     *                    gl ekrani 
     */
    PlotSelectedItem(LogVariableGUI* logVar, int index, MultiBrowser* mBrowser,
            GlPlotXYWindow* gl);
   
    /** Sistemden alinan yerler geri verilir */    
    ~PlotSelectedItem();

    /** Log degiskeninin rengini gunceller. */  
    void setColor(int r, int g, int b);

private:
    static void cbClose(Widget *o, void* userData);

    static void cbChangeColor( Widget* o, void* userData );

    virtual int handle(int e);

    Group* findParentInBrowser(const char* name);

    /** Secilen GUI log degiskeni */
    LogVariableGUI* logVarGUI;

    /** Secilen GUI log degiskeninin elemani */
    int element;

    GlPlotWindowBase* glWindow;

    MultiBrowser* selectedMBrowser;
    
    /** Renk degistirme butonu */
    Button* colorButton;

    /** Kapatma butonu */
    Button* closeButton;

    bool isPlotXY;

};

#endif	/* _PLOTSELECTEDITEM_H */

