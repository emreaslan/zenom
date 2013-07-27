/* 
 * File:   Config.h
 * Author: RobotLab
 *
 * Created on August 13, 2009, 4:06 PM
 */

#ifndef _CONFIG_H
#define	_CONFIG_H


#include <string.h>
#include <iostream>
#include <string.h>
#include <fstream>
#include <stdlib.h>
#include "Constants.h"
#include "Array.h"
#include "ControlVariable.h"
#include "LogVariable.h"
#include "LogVariableGUI.h"


using namespace std;

enum GUIWindows
{
    NONE,
    MAINWINDOW,
    PLOTWINDOW,
    PLOTWINDOWEND,
    PLOTXYWINDOW,
    PLOTXYWINDOWEND,
    WATCHWINDOW,
    SCENEWINDOW,
    SCENEWINDOWEND
};

struct WindowBaseConfig
{
    int x; int y; int w; int h;
};
typedef struct WindowBaseConfig WindowBaseConfig;




struct MainWindowConfig : public WindowBaseConfig
{
};
typedef struct MainWindowConfig MainWindowConfig;



struct LogVarLine
{
    LogVariableGUI* logVariable;
    int color;
    int index;

    int r;
    int g;
    int b;
};
typedef struct LogVarLine LogVarLine;

struct PlotConfig : public WindowBaseConfig
{
    Array<LogVarLine> line;
    bool isAutoScale;
    bool isAutoTranslate;
};
typedef struct PlotConfig PlotConfig;

struct PlotXYConfig : public WindowBaseConfig
{
    Array<LogVarLine> line;
    bool isAutoScale;
};
typedef struct PlotXYConfig PlotXYConfigs;

struct WatchConfig : public WindowBaseConfig
{
    int sevenSegmentColor;
    int backgroundColor;
    int precision;
    LogVariableGUI* logVariable;
};
typedef struct WatchConfig WatchConfig;

struct SceneBindVariableConfig
{
    char* vrmlFilename;
    Array<int> vrmlIndex;
    LogVariableGUI *logVariable;
    int logVarIndex;
};
typedef struct SceneBindVariableConfig SceneBindVariableConfig;

struct SceneWindowConfig : public WindowBaseConfig
{
    Array<const char*> vrmlFiles;
    Array<SceneBindVariableConfig> bindedVariable;
};

typedef struct SceneWindowConfig SceneWindowConfig;

template <class X ,class Y >
struct xenomPair
{
    xenomPair(X First = NULL,Y Second = NULL )
    {
        first = First;
        second = Second;
    }
    
    X first;
    Y second;
};

/**
 * class Config
 * --------------
 * Config objesi controlbase sinifi için gerekli LogVariable ve 
 * ControlVariable degiskenlerini configuration dosyasindan okur ve
 * ve ilk deger atamalarini yapar. Program sonlandiginda ya da kullanıcı
 * degerleri kaydetmek istediginde, degiskenlerin guncel degerlerini 
 * configuration dosyasina kaydeder. Bu objede tutulan degerler char tipindedir
 * Dosyadan okunan degerler, degisiklik yapilmadan dizilerde tutulur. Degerler
 * istenildiginde tip degisikligi yapilir ve istenilen adrese degerler yazilir
 *
 */

class Config
{
public:
    /**
     * Constructor
     * Configuration dosyasinin ismini alir, bu dosyayi okuyarak
     * degiskenlerin tutuldugu arraylari olusturur
     * @param name    Dosya ismi
     * @param GUI     Objenin GUI tarafindan olusturulma bilgisi
     */
    Config(const  char* name,bool GUI = false);

    /**
     * Destructor
     * Objenin yok edilmesini saglar ve alinan dinamik hafizalar geri verir
     */
    ~Config();
    
    
    /**
     * setValue
     * Dosyadan okunarak olusturulan degisken arraylari icinden, istenilen 
     * isimdeki degiskeni bulup, degiskenin degerini char'dan double'a ya da 
     * double dizisine cast ettikten sonra belirtilen pointer adresine degerleri
     * yazan fonksiyon.
     * 
     * @param section   Istenilen degiskenin tipi   
     * @param name      Degiskenin adi
     * @param dest      Degerin yazilacagi pointer
     * @return          Degisken dosyada bulunamazsa false return edelir
     */
    void setValue(const variableTypes section,const char* name , double *dest);

    /**
     * setValue
     * Dosyadan okunarak olusturulan degisken arraylari icinden, istenilen
     * isimdeki degiskeni bulup, degiskenin degerini char'dan double'a ya da
     * double dizisine cast ettikten sonra belirtilen pointer adresine degerleri
     * yazan fonksiyon.
     *
     * @param dest      Degerin yazilacagi objelerin dizisi
     * @return          Degisken dosyada bulunamazsa false return edelir
     */
    void setValue( Array<LogVariable *> &dest );

    /**
     * setValue
     * Dosyadan okunarak olusturulan degisken arraylari icinden, istenilen
     * isimdeki degiskeni bulup, degiskenin degerini char'dan double'a ya da
     * double dizisine cast ettikten sonra belirtilen pointer adresine degerleri
     * yazan fonksiyon.
     *
     * @param dest      Degerin yazilacagi objelerin dizisi
     * @return          Degisken dosyada bulunamazsa false return edelir
     */
    void setValue( Array<ControlVariable *> &dest );

    /**
     * setValueGUI
     * Dosyadan okunarak olusturulan degisken arraylari icinden, istenilen
     * isimdeki degiskeni bulup, degiskenin degerini char'dan double'a ya da
     * double dizisine cast ettikten sonra belirtilen pointer adresine degerleri
     * yazan fonksiyon.
     *
     * @param dest      Degerin yazilacagi objelerin dizisi
     * @return          Degisken dosyada bulunamazsa false return edelir
     */
    void setValueGUI( Array<ControlVariable *> &dest );


    /**
     * setValueGUI
     * Dosyadan okunarak olusturulan degisken arraylari icinden, istenilen
     * isimdeki degiskeni bulup, degiskenin degerini char'dan double'a ya da
     * double dizisine cast ettikten sonra belirtilen pointer adresine degerleri
     * yazan fonksiyon.
     *
     * @param dest      Degerin yazilacagi objelerin dizisi
     * @return          Degisken dosyada bulunamazsa false return edelir
     */
    void setValueGUI( Array<LogVariableGUI *> &dest );



    /**
     * setValue
     * Dosyadan okunarak olusturulan degisken arraylari icinden, istenilen
     * isimdeki degiskeni bulup, degiskenin degerini char'dan double'a ya da
     * double dizisine cast ettikten sonra belirtilen pointer adresine degerleri
     * yazan fonksiyon.
     *
     * @param dest      Degerin yazilacagi obje
     * @return          Degisken dosyada bulunamazsa false return edelir
     */
    void setValue( LogVariable &dest );

    /**
     * setValue
     * Dosyadan okunarak olusturulan degisken arraylari icinden, istenilen
     * isimdeki degiskeni bulup, degiskenin degerini char'dan double'a ya da
     * double dizisine cast ettikten sonra belirtilen pointer adresine degerleri
     * yazan fonksiyon.
     *
     * @param dest      Degerin yazilacagi objenin adresi
     * @return          Degisken dosyada bulunamazsa false return edelir
     */
    void setValue( LogVariable *dest );

    /**
     * setValue
     * Dosyadan okunarak olusturulan degisken arraylari icinden, istenilen
     * isimdeki degiskeni bulup, degiskenin degerini char'dan double'a ya da
     * double dizisine cast ettikten sonra belirtilen pointer adresine degerleri
     * yazan fonksiyon.
     *
     * @param dest      Degerin yazilacagi obje
     * @return          Degisken dosyada bulunamazsa false return edelir
     */
    void setValue( ControlVariable &dest );

    /**
     * setValue
     * Dosyadan okunarak olusturulan degisken arraylari icinden, istenilen
     * isimdeki degiskeni bulup, degiskenin degerini char'dan double'a ya da
     * double dizisine cast ettikten sonra belirtilen pointer adresine degerleri
     * yazan fonksiyon.
     *
     * @param dest      Degerin yazilacagi objenin adresi
     * @return          Degisken dosyada bulunamazsa false return edelir
     */
    void setValue( ControlVariable *dest );

    
    /**
     * saveToFile
     * Guncel degerleri dosyaya kaydeden fonksiyon
     * 
     * @return          Dosyaya yazma islemi basarisiz olursa false return eder
     */
    bool saveToFile();

    
     /**
     * updateVariable - ControlVariable
     * Program tarafindan guncellenen degerleri alip, karakter dizilerini 
     * guncelleyen fonksiyon
     *
     * @param source      Guncel degerlerin tutuldugu dizi
     */
    void updateVariable(Array<ControlVariable*> &source);
    
    /**
     * updateVariable - LogVariable
     * Program tarafindan guncellenen degerleri alip, karakter dizilerini 
     * guncelleyen fonksiyon
     *
     * @param source      Guncel degerlerin tutuldugu dizi
     */
    void updateVariable(Array<LogVariable*> &source);

    /**
     * updateVariable - ControlVariable
     * Program tarafindan guncellenen degerleri alip, karakter dizilerini
     * guncelleyen fonksiyon
     *
     * @param source      Guncel degerlerin tutuldugu dizi
     */
    void updateVariable(ControlVariable &source);

    /**
     * updateVariable - LogVariable
     * Program tarafindan guncellenen degerleri alip, karakter dizilerini
     * guncelleyen fonksiyon
     *
     * @param source      Guncel degerlerin tutuldugu dizi
     */
    void updateVariable(LogVariable &source);
    

     /**
     * updateVariable - GeneralVariable
     * Program tarafindan guncellenen degerleri alip, karakter dizilerini 
     * guncelleyen fonksiyon
     *
     * @param frequency     Guncel frekans bilgisi
     * @param duration      Guncel duration bilgisi
     */
    void updateVariable(const double frequency,const double duration);


    /**
     * updateSceneWindows
     * Obje icindeki SceneWindow bilgilerini guncelleyen fonksiyon
     *
     * @param sceneWindow     Guncel sceneWindow bilgileri
     */
    void updateSceneWindows(Array<SceneWindowConfig>& sceneWindow);

    /**
     * updatePlotWindows
     * Obje icindeki PlotWindow bilgilerini guncelleyen fonksiyon
     *
     * @param plotWindow     Guncel plotwindow bilgileri
     */
    void updatePlotWindows(Array< PlotConfig> &plotWindow);

    /**
     * updatePlotWindows
     * Obje icindeki PlotWindow bilgilerini guncelleyen fonksiyon
     *
     * @param plotWindow     Guncel plotwindow bilgileri
     */
    void updatePlotXYWindows(Array< PlotXYConfig> &plotXYWindow);

    /**
     * updateWatchWindows
     * Obje icindeki WatchWindow bilgilerini guncelleyen fonksiyon
     *
     * @param watchWindow     Guncel plotwindow bilgileri
     */
    void updateWatchWindows(Array< WatchConfig> &watchWindow );

     /**
     * updateMainWindow
     * Obje icindeki mainWindow bilgilerini guncelleyen fonksiyon
     *
     * @param mainWin   Guncel plotwindow bilgileri
     */
    void updateMainWindow(MainWindowConfig &mainWin );


    /**
     * getWatchWindows
     * WatchWindow bilgilerini donduren fonksiyon
     *
     * @return dosyadan okunan watchwindow bilgileri
     */
    Array< WatchConfig> *getWatchWindows();


    /**
     * getPlotWindows
     * PlothWindow bilgilerini donduren fonksiyon
     *
     * @return dosyadan okunan plotWindow bilgileri
     */
    Array< PlotConfig> *getPlotWindows();

    /**
     * getPlotXYWindows
     * PlothWindow bilgilerini donduren fonksiyon
     *
     * @return dosyadan okunan plotWindow bilgileri
     */
    Array< PlotXYConfig> *getPlotXYWindows();
     
    /**
     * getMainWindow
     * mainWindow bilgilerini donduren fonksiyon
     *
     * @return dosyadan okunan mainwindow bilgileri
     */
    MainWindowConfig getMainWindow();


    /**
     * getSceneWindows
     * sceneWindow bilgilerini donduren fonksiyon
     *
     * @return dosyadan okunan scenewindow bilgileri
     */
    Array< SceneWindowConfig >* getSceneWindows();

   
    /**
     * setFileName
     * Dosya adini set eden fonksiyon
     *
     * @param name          Dosya adi
     */
    bool setFileName(const char* name);
    
    inline char *getFileName() const{ return fileName; };

    void resetArrays();

    /**
     * loadFileGUI
     * Dosyayadan GUI icin gerekli degerleri okuyan fonksiyon
     *
     * @return          Dosyadan okuma islemi basarisiz olursa false return eder
     */
    bool loadFileGUI();

    /**
     * storeFileGUI
     * Dosyayadan GUI icin gerekli degerleri depolayan fonksiyon
     *
     * @return          Dosyadan okuma islemi basarisiz olursa false return eder
     */
    bool storeFileGUI();

    /**
     * printFileGUI
     * Dosyayan GUI icin gerekli degerleri yazan fonksiyon
     *
     * @return          Dosyaya yazma islemi basarisiz olursa false return eder
     */
    bool printFileGUI(ofstream &outputfile);

    /*** Window bilgilerinin tutulduğu arraylari temizler*/
    void clearWindowVecs();
    
private:


    /*** Plot ekran bilgisini okuyan fonksiyon */
    void readPlotLine(Array<char *> &);

    /*** Plot ekran bilgisini okuyan fonksiyon */
    void readPlotXYLine(Array<char *> &);

    /*** Watch ekran bilgilerini okuyan fonksiyon */
    void readWatchLine(char *);

    /*** Main window bilgilerini okuyan fonksiyon */
    void readMainWindowLine(char *);

    /*** Scene ekran bilgilerini okuyan fonksiyon */
    void readSceneLine(Array<char *> &);

    /**
     * saveToFileGUI
     * GUI bilgilerini dosyaya yazan fonksiyon
     *
     * @param outputfile Yazilacak dosyanin objesi
     * @return          Dosyaya yazma islemi basarisiz olursa false return eder
     */
    bool saveToFileGUI(ofstream &outputfile);
    
    /**
     * loadFile
     * Dosyayadan simulasyon icin gerekli degerleri okuyan fonksiyon
     * 
     * @return          Dosyadan okuma islemi basarisiz olursa false return eder
     */
    bool loadFile();
    

     /**
     * findVariable
     * Karakter dizileri icinde istenilen isimdeki degiskenin degerler dizisini
     * veren fonksiyon
     * 
     * @param section   Aranan degerlerin tipi
     * @param name      Aranan degerlerin degisken adi
     * @return          Degerlerin tutuldugu karakter dizisi
     */
    char* findVariable(const variableTypes section,const char *name);
    
    
    /**
     * charToValue
     * Karakter dizisini double ya da double dizisine donusturup, degerleri
     * belirtilen pointer adresine yazan fonksiyon 
     * 
     * @param values    Degerlerin yazili oldugu karakter dizisi
     * @param dest      Donusturulen degerlerin yazilacagi adres
     * @return          Dosyadan okuma islemi basarisiz olursa false return eder
     */
    bool charToValue( char* values , double* dest );

    /** İsme göre degisken aramasi yapan fonksiyon */
    LogVariableGUI* findLogVariableGUI(string);
    
    
    /**
     * generalArray
     * Programin genel parametrelerin tutuldugu dizi
     */
    Array< xenomPair< char* , char* > > generalArray;
    
    /**
     * logArray
     * Log degiskenlerinin tutuldugu dizi
     */
    Array< xenomPair< char* , char* > > logArray;
    
    /**
     * controlArray
     * Control degiskenlerinin tutuldugu dizi
     */
    Array< xenomPair< char* , char* > > controlArray;
    
    /**
     * fileName
     * Configuration dosyasinin ismi
     */
    char *fileName;

    /**
     * isGUI
     * Objenin GUI tarafindan olusturulma bilgisi
     */
    bool isGUI;


    /**
     * arrayVec
     * Degiskenlerin tutuldugu arraylere kolay erisim saglar
     */
    Array< xenomPair< char* , char* > > *arrayVec[3];


    /**
     * arrayGUI
     * Degiskenlerin tutuldugu arraylere kolay erisim saglar
     */
    Array < Array< xenomPair< char* , char* > > * >  *arrayGUI;

    /** Log degiskenlerinin tutuldugu dizi */
    Array< LogVariableGUI* > *logVariableGUIArray;

    Array< PlotConfig > plotWindowsVec;

    Array< PlotXYConfig > plotXYWindowsVec;

    Array< WatchConfig > watchWindowsVec;

    Array< SceneWindowConfig > sceneWindowsVec;

    Array< char *> guiConfigFileStorage;

    MainWindowConfig mainWindow;    
};



#endif	/* _CONFIG_H */

