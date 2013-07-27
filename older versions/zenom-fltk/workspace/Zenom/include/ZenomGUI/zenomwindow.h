//==============================================================================
// Zenom.h - Header File of Main Class of Zenom Project
//
// Author        : Adil Karaöz, Cüneyt Ay, Hüsnü Karaküçük
// Version       : 0.99 (Agustos 2009)
// Compatibility : FLTK, GCC
//==============================================================================

#ifndef ZENOMWINDOW_H
#define ZENOMWINDOW_H

#include <fltk/Window.h>
#include <fltk/Button.h>
#include <fltk/MenuBar.h>
#include <fltk/events.h>
#include <fltk/SharedImage.h>
#include <fltk/TiledImage.h>
#include <fltk/Divider.h>
#include <fltk/ItemGroup.h>
#include <fltk/Item.h>
#include <fltk/PackedGroup.h>
#include <fltk/FileChooser.h>
#include <fltk/ask.h>
#include <fltk/run.h>
#include <fltk/ProgressBar.h>

#include <cstring>
#include <iostream>
#include <signal.h>

#include <ThreadXp.hpp>
#include <TaskXn.hpp>
#include "TextDisplayWidget.h"

#include "SevenSegment.h"
#include "LogVariableGUI.h"
#include "Array.h"
#include "Config.h"
#include "guiMessenger.h"
#include "controlVarWindow.h"
#include "logVarWindow.h"
#include "PlotWindow.h"
#include "PlotXYWindow.h"
#include "WatchSelectWindow.h"
#include "SceneWindow.h"

#include "SceneWindowManager.h"
#include "PlotWindowManager.h"
#include "PlotXYWindowManager.h"

#include "ZPath.h"

using namespace std;
using namespace fltk;


class WindowUpdater;
class MessageHandler;



//==============================================================================
// class Zenom inherited from Window
//------------------------------------------------------------------------------
// Zenom sinifi ana pencerenin onceden belirlenen ozellklerle acilmasini 
// saglar. Projenin ana pencere classıdır
// <b>Ornek Program:</b>
//
// \include zenomwindow.cpp
//==============================================================================
class ZenomWindow : public Window
{
    friend class MessageHandler;
    friend class WindowUpdater;

public:

    // Zenom constructor
    // verilen ozelliklerde bir fltk window olusturur
    ZenomWindow( int W = 400, int H = 310, const char *title = "Zenom");

       
    // Zenom destructor
    ~ZenomWindow();

    

    // Configuration dosyasini yuklemeye yarar
    static void cbLoadConfigFile( Widget *w, void *userData );

    // Configuration dosyasini yeniden yuklemeye yarar
    static void cb_ReloadConfigFile( Widget *w, void *userData );

    // Dosya kaydedilir
    static void cbSaveFile( Widget *w, void *userData );

    // Dosya farkli kaydedilir
    static void cbSaveAsFile( Widget *w, void *userData );

    // Quit'e basildiginda cikmak icin kullanilir.
    static void cbQuit( Widget *w, void *userData );

    // yeni plotting window acilir
    static void cbPlotWindow( Widget *w, void* userData );

    static void cbPlotXYWindow( Widget *w, void* userData );

    static void cbSceneWindow( Widget *w, void* userData );

    // Control Variable Window
    static void cbControlVarWindow( Widget *w, void *userData );

    static void cbLogVarWindow( Widget *w, void *userData );

    // watch select window acilir
    static void cbWatchSelectWindow( Widget *w, void *userData );

    // İcerik yardimin penceresini acaar
    static void cb_Help_Contents( Widget *w, void *userData );

    // Hakkinda penceresini goruntuler
    static void cb_Help_About( Widget *w, void *userData );

    // start button
    static void cbStartButton( Widget *w, void *userData );

    // stop button
    static void cbStopButton( Widget *w, void *userData );

    
    static void cbUpdate(void *pZenomWindow);

        
    void printArrays();


private:

    void openConfigurationWindows();

    static void cbFreqDurUpdate( Widget *w, void *userData );

    virtual int handle(int e);

    void assignHeapPointers();

    void printGUI(char* text, int errCode);

    int runControl();

    int unload();

    /** LogVariableGUI Heape baglanir */
    int bindLogVarHeap();

    /** LogVariableGUI Heapleri serbest birakilir */
    int unbindLogVarHeap();

    // ana pencerenin ve olustutulan yan pencerelerin baslangic ozelliklerini
    // ayarlar
    void initialize();

    // Zaman ve Tarih fonksiyonu
    //  return 	Zamani ve tarihi string olarak geri dondurur
    //           formati gun / ay / saat / yil
//    const char *getDateAndTime();

    /**
     * Dosya yuklu olmadiginda pasif olmasi gereken elemanlari kapatir.
     * Buton, menu ... elemanlarini pasif yapar.
     */
    void deactiveItems();

    /**
     * Dosya yuklu oldugunda aktif olmasi gereken elemanlari acar.
     * Buton, menu ... elemanlarini aktif yapar.
     */
    void activeItems();



    //--------------------------------------------------------------------------
    // beginning of callback functions------------------------------------------


    int loadConfigFile();


    void start();
    void pause();
    void stop();


    // logo resmini barindirir
    Widget *logoBox;

    // basla ve dur butonlari
    Button *startButton;
    Button *stopButton;


    // frekans ve islem suresini tutar
    IntInput *frequencyInput;
    IntInput *durationInput;

    int frequency;
    int duration;

    // ana menu
    MenuBar *main_menu;
    ItemGroup *programs;
    ItemGroup *windows;
    ItemGroup *help;

    ProgressBar* progressBar;

    /** Watch Window LogVariableGUI Listesi*/
    WatchSelectWindow* selectWatch;


    // Program logosunu tutar
    Image *logo;

    ZPath mProjectPath;
    ZPath mProjectConfigPath;

    /** Log degiskenlerini tutan dizi */
    Array< LogVariableGUI* > logVariableGUIArray;

    /** Control degiskenlerini tutan dizi */
    Array< ControlVariable* > controlVariableArray;

    PlotWindowManager plotWindowManager;
    PlotXYWindowManager plotXYWindowManager;
    SceneWindowManager sceneWindowManager;

    /** Watch Windowlarda bulunan 7Segmentleri gunceller */
    WindowUpdater* watchUpdater;

    /** Control Degiskenlerini degistermeyi imkan saglayan pencere */
    ControlVarWindow* controlVarWindow;

    /** Log Degiskenlerini degistermeyi imkan saglayan pencere */
    LogVarWindow* logVarWindow;

    stateTypes state;

    Config* confGUI;

    guiMessenger* guiComQueueReceiver;

    guiMessenger* guiComQueueSender;
    
    guiMessenger* rtnetComQueueReceiver;

    MessageHandler* messageHandler;

    pid_t child;

    HeapXn* controlHeap;

    double* controlHeapAddress;

    bool firstRun;

    bool load;
};



#endif  // ZENOMWINDOW_H


//==============================================================================
// WINDOWUPDATER
//==============================================================================


#ifndef _WINDOWUPDATER_H
#define	_WINDOWUPDATER_H

class WindowUpdater : public TaskXn
{
public:
    /**
     * Constructor
     * Progam calirken pencerelerdeki bilgileri gunceller
     * @param zenom  Zenom penceresi
     *
     **/
    WindowUpdater( ZenomWindow* zenom );


    virtual void run();



    /**
     * executeInThread sonlandirilir, thread cancel edilir.
     *
     **/
    void stopThread();

private:

    ZenomWindow* zenom;

    stateTypes state;

    bool runFlag;

};

#endif	/* _WINDOWUPDATER_H */


#ifndef _MESSAGEHANDLER_H
#define	_MESSAGEHANDLER_H

class MessageHandler : public TaskXn
{
public:

    MessageHandler( ZenomWindow* zenom );


    virtual void run();

    /**
     * executeInThread sonlandirilir, thread cancel edilir.
     *
     **/
    void stopThread();

private:

    ZenomWindow* zenom;

    char timeInfo[255];

    bool runFlag;

};

#endif	/* _MESSAGEHANDLER_H */
