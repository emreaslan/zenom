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
#include "pugixml.hpp"


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
    char* path;
    LogVariableGUI *logVariable;
    int index;
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
    void updateVariable(Array<LogVariableGUI*> &source);
    void updateVariable(Array<LogVariable*> &source);

      

     /**
     * updateVariable - GeneralVariable
     * Program tarafindan guncellenen degerleri alip, karakter dizilerini 
     * guncelleyen fonksiyon
     *
     * @param frequency     Guncel frekans bilgisi
     * @param duration      Guncel duration bilgisi
     */
    void updateVariable(const double frequency,const double duration);


    pugi::xml_node appendChild(const char *pChildName);
    pugi::xml_node getChild(const char *pChildName);
     void resetXMLFile(bool pIsConfig = false);


     
    /**
     * setFileName
     * Dosya adini set eden fonksiyon
     *
     * @param name          Dosya adi
     */
    bool setFileName(const char* name);
    
    inline char *getFileName() const{ return fileName; }

    int getDuration();
    int getFrequency();  
private:
   
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

    Array< SceneWindowConfig > sceneWindowsVec;

    pugi::xml_document mConfigXML;
};


class Utils
{
public:
    static ControlVariable* findControlVariable(const char *pName)
    {
        for (int i = 0; i < mControlVars->getNumElements(); ++i )
            if ( strcmp(pName, mControlVars->getElement(i)->getName()) == 0)
                return mControlVars->getElement(i);
        return NULL;
    }


    static LogVariable* findLogVariable(const char *pName)
    {
        for (int i = 0; i < mLogVars->getNumElements(); ++i )
            if ( strcmp(pName, mLogVars->getElement(i)->getName()) == 0)
                return mLogVars->getElement(i);
        return NULL;
    }

    
    static LogVariableGUI* findLogVariableGUI(const char *pName)
    {
        for (int i = 0; i < mLogVarsGUI->getNumElements(); ++i )
            if ( strcmp(pName, mLogVarsGUI->getElement(i)->getName()) == 0)
                return mLogVarsGUI->getElement(i);
        return NULL;
    }

    static void setControlVariableVec(Array<ControlVariable*> *pControlVars){ mControlVars = pControlVars; }
    static void setLogVariableVec(Array<LogVariable*> *pLogVars){ mLogVars = pLogVars; }
    static void setLogVariableGUIVec(Array<LogVariableGUI*> *pLogVarsGUI){ mLogVarsGUI = pLogVarsGUI;}

private:
    static Array<LogVariable*> *mLogVars;
    static Array<LogVariableGUI*> *mLogVarsGUI;
    static Array<ControlVariable*> *mControlVars;
};
#endif	/* _CONFIG_H */

