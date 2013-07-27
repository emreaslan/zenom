/* 
 * File:   ControlBase.h
 * Author: casper
 *
 * Created on August 13, 2009, 3:55 PM
 */

#ifndef _CONTROLBASE_H
#define	_CONTROLBASE_H

#include <RowVector.hpp>
#include <ColumnVector.hpp>
#include "Array.h"
#include "Config.h"
#include "ControlVariable.h"
#include "LogVariable.h"


class RTMessage;



class ControlBase
{

public:

    double frequency;
    
    double period;
    
    double duration;
    
    long int elapsedTimeNano;

    long int elapsedTimeMiliSecond;

    double elapsedTimeSecond;
    
    int elapsedTicks;
    
    bool isStartMessageReceived;
    
    /** Constructor
     * Obje olusturur ve ilk atamalari yapar
     *
     * @param argc  Arguman sayisi
     * @param argc  Argumanlar
     */
    ControlBase(int argc = 0, char*argv[] = 0);

    /** Destructor
     * Obje yok eden fonksiyon
     *
     */
    ~ControlBase();
    
    /** Programi calistirir. */
    void run();
    
    /**
     * Configurasyon dosyasindaki bilgiler okunur, degiskenler guncellenir.
     *
     * @return Yukleme basarili olursa ise true, olmazsa false getirir.
     */
    bool loadConfigFile();
     
  
    /**
     * Log edilecek degiskenleri programa kaydeden fonksiyon
     *
     * @param variable  Kaydedilecek degisken
     * @param nm        Degiskenin ismi
     * @param desc      Degiskenin aciklamasi
     */
    void registerLogVariable(double &variable,const char* nm , const char* desc= "" );

    /**
     * Log edilecek degiskenleri programa kaydeden fonksiyon
     *
     * @param variable  Kaydedilecek degisken
     * @param nm        Degiskenin ismi
     * @param desc      Degiskenin aciklamasi
     */
    void registerLogVariable(double *variable,const char* nm , const char* desc= "",int row = 1 , int col = 1  );

    /**
     * Log edilecek degiskenleri programa kaydeden fonksiyon
     *
     * @param variable  Kaydedilecek degisken
     * @param nm        Degiskenin ismi
     * @param desc      Degiskenin aciklamasi
     */
    void registerLogVariable(double **variable,const char* nm , const char* desc= "",int row = 1 , int col = 1  );

    /**
     * Log edilecek degiskenleri programa kaydeden fonksiyon
     *
     * @param variable  Kaydedilecek degisken
     * @param nm        Degiskenin ismi
     * @param desc      Degiskenin aciklamasi
     */
    void registerLogVariable(int **variable,const char* nm , const char* desc= "",int row = 1 , int col = 1  );

    /**
     * Log edilecek degiskenleri programa kaydeden fonksiyon
     *
     * @param variable  Kaydedilecek degisken
     * @param nm        Degiskenin ismi
     * @param desc      Degiskenin aciklamasi
     */
    void registerLogVariable(int *variable,const char* nm , const char* desc= "",int row = 1 , int col = 1  );

    /**
     * Log edilecek degiskenleri programa kaydeden fonksiyon
     *
     * @param variable  Kaydedilecek degisken
     * @param nm        Degiskenin ismi
     * @param desc      Degiskenin aciklamasi
     */
    void registerLogVariable(int &variable,const char* nm , const char* desc= "",int row = 1 , int col = 1  );


    /**
     * Log edilecek degiskenleri programa kaydeden fonksiyon
     *
     * @param varArray  Kaydedilecek degisken dizisi
     * @param nm        Degiskenin ismi
     * @param desc      Degiskenin aciklamasi
     */
    void registerLogVariable(MatrixBase<double> &varMatrix,const char* nm , const char* desc= "" );

    /**
     * Log edilecek degiskenleri programa kaydeden fonksiyon
     *
     * @param varArray  Kaydedilecek degisken dizisi
     * @param nm        Degiskenin ismi
     * @param desc      Degiskenin aciklamasi
     */
    void registerLogVariable(MatrixBase<int> &varMatrix,const char* nm , const char* desc= "" );

    /**
     * Programi kontrol edecek degiskenleri programa kaydeden fonksiyon
     *
     * @param variable  Kaydedilecek degisken
     * @param nm        Degiskenin ismi
     * @param desc      Degiskenin aciklamasi
     */
    void registerControlVariable(double &variable,const char* nm , const char* desc= "" );

    /**
     * Programi kontrol edecek degiskenleri programa kaydeden fonksiyon
     *
     * @param variable  Kaydedilecek degisken
     * @param nm        Degiskenin ismi
     * @param desc      Degiskenin aciklamasi
     */
    void registerControlVariable(double *variable,const char* nm , const char* desc= "",int row = 1 , int col = 1 );


    /**
     * Programi kontrol edecek degiskenleri programa kaydeden fonksiyon
     *
     * @param varArray  Kaydedilecek degisken dizisi
     * @param nm        Degiskenin ismi
     * @param desc      Degiskenin aciklamasi
     */
    void registerControlVariable(MatrixBase<double> &varMatrix ,const char* nm , const char* desc= "" );


     /**
     * RTNET ile haberlesme yapacak objeleri kaydeden fonksiyon
     *
     * @param messenger Mesajlasma objesi
     */
    void registerMessageObject( RTMessage &messenger );

    /**
     * Program yuklendigi zaman cagrilir. Arayuz(GUI) kullaniyorken, kullanici
     * programa dosyayi yukledigi zaman cagrilir.
     *
     * @return Başarılı olursa 0, olmazsa sıfır olmayan değer getirir.
     */
    virtual int initialize(){return 0;}
    
    /**
     * Program calistigi zaman cagrilir. Arayuz(GUI) kullanilmadiysa initialize
     * fonksiyonunda hemen sonra calisir. Eger arayuz kullanildi ise, 
     * kullanicinin start butonuna basması beklenir.
     * 
     * @return Başarılı olursa 0, olmazsa sıfır olmayan değer getirir.
     */    
    virtual int start(){return 0;}
    
     /**
     * Tanimlanan frekans araliginda cagrilacak olan fonksiyondur. 
     * 
     * @return Başarılı olursa 0, olmazsa sıfır olmayan değer getirir.
     */    
    virtual int doloop(){return 0;}
    
    /**
     * Program durduruldugu zaman cagrilir. Program calısma surecini 
     * doldurdugunda veya arayuzden(GUI) stop butonuna basildigi zaman
     * cagrilir.
     * 
     * @return Başarılı olursa 0, olmazsa sıfır olmayan değer getirir.
     */  
    virtual int stop(){return 0;}
    
    /**
     * Program bittiği zaman cagrilir. Arayuzde(GUI) yeni dosya yuklendigi
     * veya arayuz kapatildigi zaman cagrilir.
     * 
     * @return Başarılı olursa 0, olmazsa sıfır olmayan değer getirir.
     */ 
    virtual int terminate(){return 0;}


    /**
     * Bilgileri heap'e kopyalayan fonksiyon
     *
     */
    void copyToSourceHeap();

    /**
     * Bİlgilerin kaydedilecegi dosyanin adini degistirir
     *
     * @param nm Dosya ismi
     */
    inline void setConfigFileName(char *nm){config->setFileName(nm);}


private:
    void fillControlVarsWithZero();

    /** Benzetimi Arayuz ile yuruten fonksiyon */
    bool runWithGUI( );

    /** Benzetimi Console ile yuruten fonksiyon */
    bool runWithConsole( );

    /** Stop isleminden sonra heapleri temizler */
    void cleanLoggerHeaps( );
    
      
    /** Program calisirken set edilen control degerlerini gunceller */
    bool createLoggerHeaps( );

    /** Program calisirken set edilen control degerlerini gunceller */
    void updateVariablesFromHeap( bool isStart = false );

    /** Programin urettigi ve kullandigi verileri yazdigi paylasilabilen 
     * hafizayi olusturan fonksiyon 
     */
    bool createControlHeap();

    /** Parametreyi dosya ismine kaydeden fonksiyon */
    void copyConfigFileName(char *);

    /** Programin nasil calistirilacagini ekrana yazan fonksiyon*/
    void showUsage();

    /** Programin yardim bilgilerini ekrana yazan fonksiyon*/
    void showHelp();

    /** ControlBase ismi */
    char* applicationName;

    /** ControlBase ismi */
    char* configFileName;

    /** Programin gui ile calistirildigi bilgisi */
    bool isGUI;
       
  
    
    /** Programin gui ile calistirildigi bilgisi */
    stateTypes zenomState;


    /** ControlHeap baslangic adresi */
    double *controlHeapAddress;

   
    
    /** Control degiskenleri tutuan array */
    Array<ControlVariable*> controlVariableArray;

    /** Log degiskenleri tutuan array */
    Array<LogVariable*> logVariableArray;

    /** Configuration dosyasini okuyup yazan obje */
    Config *config;

    /** Default constructor kullanilmamasi icin */
    ControlBase();

    /** LogVariable bilgilerini ekrana yazan fonksiyon */
    void printLogVariable();

    /** ControlVariable bilgilerini ekrana yazan fonksiyon */
    void printControlVariable();
  

    /** RTNet ile haberlesmeyi yapacak olan objeleri tutan dizi */
    Array<RTMessage *> messengerArray;
    
    /** Overrun sayisini tutan degisken*/
    unsigned long mOverrunCount;
};
#endif


