#ifndef _WATCHWINDOW_H
#define	_WATCHWINDOW_H

#include <fltk/Window.h>
#include <fltk/PopupMenu.h>
#include <fltk/ValueInput.h>
#include <fltk/ColorChooser.h>
#include <fltk/events.h>
#include <fltk/Color.h>

#include <cstring>
#include <math.h>

#include "SevenSegment.h"
#include "LogVariableGUI.h"
#include "Array.h"
#include "ZButton.h"
#include "Config.h"


using namespace std;
using namespace fltk;

/**
 * WatchWindow class.
 * Log degiskeni degerlerini 7 segment ekraninda gosteren gorsel 
 * arayuz penceresidir. 
 */

class WatchWindow : public Window
{
public:
    /**
     * Constructor
     * LogVariable objesi ile watch window acar.
     * @param logVar  Watch window acilacak LogVariable objesidir.
     */
    WatchWindow( LogVariableGUI* logVar );

    
    /**
     * Destructor
     * Sistemden alinan yerler geri verilir.
     */
    ~WatchWindow();

    /**
     * 7Segmentteki degeri LogVariable heapden alinan veri ile gunceller.
     */
    void updateSevenSegment();

    /**
     * 7Segmentte renk bilgileri resetlenir.
     * Bu fonksiyon 7Segment nan deger gosterdigi zaman eski renk bilgilerini
     * geri almak icin gereklidir.
     */
    void resetSevenSegment();

    /**
     * 7Segment arka plan rengini degistirir.
     */
    void setBackgroundColor(int pColor);

    /**
     * 7Segment rengini degistirir.
     */
    void setSevenSegmentColor(int pColor);

    /**
     * 7Segment hassaslik degerini degistirir.
     */
    void setPrecision(int r);

    /**
     * Pencere bilgilerini getirir.
     */
    WatchConfig save();

private:
    static void cbEditWindow(Widget *o, void* userData);

    static void cbEditWindowOK(Widget *o, void* userData);

    static void cbEditWindowCancel(Widget *o, void* userData);

    static void cbChangeColor(Widget *o, long userData);

    int handle(int e);
    
    /** Watch Windowda degerleri gosterilen LogVariable objesi*/
    LogVariableGUI *logVariable;

    /** LogVariable objesinin 7Segment objeleri */
    Array<SevenSegment *> sevenSegments;

    /** Edit Pencere secimi saglayan popup menu*/
    PopupMenu* popupMenu;

    /** 7Segmentde noktadan sonra gosterilecek rakam sayisi*/
    int precision;

    //  ----- Edit Window -----
    /** 7Segmentler icin edit penceresi */
    Window* editWindow;

    /** Gorsellik icin box */
    Group* editGbox;

    /** Arka plan rengi degistirme butonu*/
    Button* editBGColorButton;

    /** 7 Segment rengi degistirme butonu*/
    Button* edit7SColorButton;

    /** 7 Segment hassaslik butonu*/
    ValueInput* precisionInput;

    /** Edit pencere iptal butonu */
    ZButton* editCancel;

    /** Edit pencere tamam butonu */
    ZButton* editOK;
    //  ----- Edit Window -----
};

#endif	/* _WATCHWINDOW_H */
