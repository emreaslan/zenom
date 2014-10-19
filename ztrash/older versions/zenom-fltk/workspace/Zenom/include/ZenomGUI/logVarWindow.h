#ifndef _LOGVARWINDOW_H
#define _LOGVARWINDOW_H

#include <fltk/Window.h>
#include <fltk/IntInput.h>
#include <fltk/Group.h>
#include <fltk/ask.h>
#include <fltk/Button.h>
#include <fltk/ScrollGroup.h>

#include "Array.h"
#include "LogVariableGUI.h"

#include <iostream>

using namespace fltk;
using namespace std;

/**
 * LogVarWindow class.
 * Log degiskenlerini degistermeyi saglayan arayuz penceresidir.
 * Bu arayuz penceresi, log degiskenlerinin kayit edilme zamanlari ve
 * frekanslarini degistirme olanigi verir.
 */


class LogVarWindow : public Window
{

public:

    /**
     * Constructor
     * Log degiskenleri ile bir pencere olusturur.
     * @param logVars Log degiskenleri dizisi
     * @param mainfrequency Programin calisma frekansi
     * @param mainduration  Programin calisma suresi
     */
    LogVarWindow( Array<LogVariableGUI*>& logVars, int mainfrequency, int mainduration );

    /** Sistemden alinan yerler geri verilir */
    ~LogVarWindow();

    /**
     * Frekans veya Zaman bilgisi degistigi zaman bilgiler guncellenir.
     * @param mainfrequency Programin calisma frekansi
     * @param mainduration  Programin calisma suresi
     */
    void update(int mainfrequency, int mainduration);

private:
    /**
     * Log Variable dizisine gore pencere doldurulur.
     */
    void fillWindow();

    /**
     * Log Variable bulunmuyorsa yaratilacak pencereyi olusturan
     * fonksiyondur.
     */
    void emptyWindow();

    /**
     * Log degiskenlerinde degisiklik yapildigi zaman calisan fonksiyondur
     * @param userData Dizi icersinde degisen control degiskeninin indexi
     */
    static void cbChangeInput(Widget *o, long userData);

    /**
     * FloatInput penceresinden degerler okunur, indexteki log variable'a
     * degerler atanir.
     * @param index Bilgileri guncellenecek control degiskeni
     */
    void changeInput(int index);
    
    /**
     * indexteki log variable degerleri FloatInput penceresine yazar.
     * @param index Bilgileri guncellenecek element
     */
    void controlInputValue( int index );

    /** Log degiskenleri dizisini tutan pointer */
    Array<LogVariableGUI*>* LogVariableGUIs;

    /** Log degiskenlerinin FloatInput ve grouplarini iceren dizi */
    Array<Group*> LogVariableGUIsGroups;

    Button* sortByName;

    Widget* frequency;

    Widget* startTime;

    Widget* duration;

    int mainFrequency;

    int mainDuration;

    /** Pencere yeniden boyutlandiriligi olusan scroll alani*/
    ScrollGroup* scrollGroup;

    /** Objelerin yerlestirilecegi alan*/
    Group* gbox;
};

#endif
