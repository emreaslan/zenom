#ifndef _WATCHSELECTWINDOW_H
#define _WATCHSELECTWINDOW_H


#include <fltk/Window.h>
#include <fltk/MultiBrowser.h>
#include <fltk/Group.h>
#include <fltk/TabGroup.h>

#include "WatchWindow.h"
#include "LogVariableGUI.h"
#include "Array.h"
#include "ZButton.h"

using namespace fltk;

/**
 * WatchSelectWindow class.
 * 7 Segment penceresinde gosterilecek log degiskenlerini secim yapmayi 
 * saglayan arayuz penceresidir.
 */

class WatchSelectWindow : public Window
{

public:
    /**
     * Constructor
     * Log degiskenlerini secim penceresi
     * @param logVarGUIArray Log degiskenleri dizisi
     */
    WatchSelectWindow( Array< LogVariableGUI* >& logVarGUIArray );

    ~WatchSelectWindow();

    /** Watch Pencerelerini kapatir */
    void hideAllWatchs();

    /** 7Segmentte heapdeki verileri yazar.*/
    void updateSevenSegments();

    /** 7Segmentleri resetler.
     * Bu fonksiyon 7Segmentler nan deger gosterdigi zaman eski renk bilgilerini
     * geri almak icin gereklidir.
     */
    void resetSevenSegments();

    void load(pugi::xml_node pWatchWindowsNode);

    void save(pugi::xml_node pWatchWindowsNode);

private:
    /** Callback Fonksiyonlari */
    static void cbWatch(Widget* w, void* arg);

    static void cbWatchAll(Widget* w, void* arg);

    static void cbCancel(Widget* w, void* arg);

    /** Watch Window */
    Array< WatchWindow* > watchWindows;

    /** Log degiskenlerini tutan dizi */
    Array< LogVariableGUI* >* logVariableGUIArray;

    /** Gorsellik icin */
    Group* gbox;

    /** Secme tablosu */
    MultiBrowser* selectionBrowser;

    /** Izle Butonu */
    ZButton *watchButton;

    /** Hepsini izle Butonu */
    ZButton *watchAllButton;

    /** iptal Butonu */
    ZButton *cancelButton;
};

#endif /* _WATCHSELECTWINDOW_H */
