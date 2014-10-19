#ifndef _PLOTXYWINDOW_H
#define	_PLOTXYWINDOW_H

#include "GlPlotXYWindow.h"
#include "PlotBaseWindow.h"

/**
 * PlotXYWindow class.
 * Log degiskeni degerlerini grafik olarak gosterir. Plot Window zamana 
 * gore degisimi grafige dokerken, PlotXY iki log degiskeninin birbirlerine
 * gore degisimini cizer. Sadece (1)(2) ve (2)(1) vektorler grafiksel 
 * gosterilir.
 */

class PlotXYWindow : public PlotBaseWindow
{
public:

    /**
     * Constructor
     * Control degiskenleri ile bir pencere olusturur.
     * @param logVars     Log degiskenleri dizisi
     * @param messenger   haberlesme objesi, eger log degiskeni degerleri
     *                    NAN olursa simulasyonu bu obje ile durdurulur.  
     */
     PlotXYWindow( Array<LogVariableGUI*>& logVars, guiMessenger* messenger );

    /** Sistemden alinan yerler geri verilir */
    ~PlotXYWindow();

    void enable();

    void disable();

    void save(pugi::xml_node pPlotXYWindowNode);

    void load(pugi::xml_node pPlotXYWindowNode);

    void addLogVariable( Array<LogVarLine>& logVariable );

private:
    /**  Callback Fonksiyonlari */
    static void cbSelectAdd(Widget *o, void* userData);

    static void cbSelectAddAll(Widget *o, void* userData);

    static void cbSelectCancel(Widget *o, void* userData);

    /**  Browser listesini doldurur. */
    void fillList();
};


#endif	/* _PLOTXYWINDOW_H */

