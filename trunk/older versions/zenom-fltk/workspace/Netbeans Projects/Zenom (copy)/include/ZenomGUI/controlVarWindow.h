#ifndef _CONTROLVARWINDOW_H
#define _CONTROLVARWINDOW_H

#include <fltk/Window.h>
#include <fltk/FloatInput.h>
#include <fltk/Group.h>
#include <fltk/ask.h>
#include <fltk/ScrollGroup.h>

#include "Array.h"
#include "ControlVariable.h"
#include "ZButton.h"

using namespace fltk;

/**
 * ControlVarWindow class.
 * Control degiskenlerini degistermeyi saglayan arayuz penceresidir.
 * Bu arayuz penceresi, kullanici control parametrelerini
 * simulasyonun calisma esnasinda degistirme olanagi verir.
 */


class ControlVarWindow : public Window
{

public:

    /**
     * Constructor
     * Control degiskenleri ile bir pencere olusturur.
     * @param controlVars Control degiskenleri dizisi
     */
    ControlVarWindow( Array<ControlVariable*>& controlVars );

    /** Sistemden alinan yerler geri verilir */
    ~ControlVarWindow();
    
private:

    /**
     * Control degiskenlerinde degisiklik yapildigi zaman Apply ve Cancel
     * butonu aktif yapar.
     */
    static void cbChangeInput(Widget *o, long);

    /**
     * Yapilan control degiskeni degerleri guncellenir.
     */
    static void cbApply(Widget *o, long);

    /**
     * Yapilan control degiskeni degisikligi geri alinir.
     */
    static void cbCancel(Widget *o, long);

    /**
     * Control Variable dizisine gore pencere doldurulur.
     */
    void fillWindow();

    /**
     * Control Variable bulunmuyorsa yaratilacak pencereyi olusturan
     * fonksiyondur.
     */
    void emptyWindow();

    /** Control degiskenleri dizisini tutan pointer */
    Array<ControlVariable*>* controlVariables;

    /** Control degiskenlerinin FloatInput ve grouplarini iceren dizi */
    Array<Group*> controlVariablesGroups;

    /** Control Variable degisiklik onay butonu */
    ZButton* applyButton;

    /** Control Variable degisiklik iptal butonu */
    ZButton* cancelButton;

    /** Pencere yeniden boyutlandiriligi olusan scroll alani*/
    ScrollGroup* scrollGroup;

    /** Objelerin yerlestirilecegi alan*/
    Group* gbox;
};

#endif
