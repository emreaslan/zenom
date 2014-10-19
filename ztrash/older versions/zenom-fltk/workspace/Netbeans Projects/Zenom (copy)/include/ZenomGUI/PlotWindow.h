#ifndef _PLOTWINDOW_H
#define	_PLOTWINDOW_H

#include "GlPlotWindow.h"
#include "PlotBaseWindow.h"


/**
 * PlotWindow class.
 * Log degiskeni degerlerinin zamana gore degisimlerini grafiksel 
 * olarak gosterir. 
 */

class PlotWindow : public PlotBaseWindow
{
public:

    /**
     * Constructor
     * Control degiskenleri ile bir pencere olusturur.
     * @param logVars     Log degiskenleri dizisi
     * @param messenger   haberlesme objesi, eger log degiskeni degerleri
     *                    NAN olursa simulasyonu bu obje ile durdurulur.  
     */
     PlotWindow( Array<LogVariableGUI*>& logVars, guiMessenger* messenger );

    /** Sistemden alinan yerler geri verilir */
    ~PlotWindow();
    

    PlotConfig save();

    void addLogVariable( Array<LogVarLine>& logVariable );

    void load(PlotConfig *config);

   
private:
    /**  Callback Fonksiyonlari */
    static void cbSelectAdd(Widget *o, void* userData);

    static void cbSelectAddAll(Widget *o, void* userData);

    static void cbSelectCancel(Widget *o, void* userData);

    /**  Browser listesini doldurur. */
    void fillList();

    /**
     * Log Degiskeni elementi ile yeni PlotSelectedItem objesi olusturur.
     * GL penceresine yeni eklenen elementi bildirir.
     * @param logVar Eklenecek log Degiskeni
     * @param element Eklenecek log degiskeni elemani
     * 
     */
    void addNewPlotItem(LogVariableGUI* logVar, int element);
};



#endif	/* _PLOTWINDOW_H */

