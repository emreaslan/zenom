/* 
 * File:   ControlBase.h
 * Author: casper
 *
 * Created on August 13, 2009, 3:55 PM
 */

#ifndef _CONTROLBASE_H
#define	_CONTROLBASE_H

#include <sys/mman.h>
#include <TaskXn.hpp>
#include <HeapXn.hpp>
#include <ThreadXp.hpp>
#include <native/timer.h>
#include <RowVector.hpp>
#include <ColumnVector.hpp>

#include "Array.h"
#include "Config.h"
#include "guiMessenger.h"
#include "ControlVariable.h"
#include "LogVariable.h"

#include "RTMessage.h"
#include "RTMessageSend.h"
#include "RTMessageRecv.h"

#include <rtdk.h>



class LoggerTask;
class LoopTask;
class MessengerThread;
class RTMessageTask;
class RTMessageListener;


class ControlBase
{
    friend class LoggerTask;
    friend class LoopTask;
    friend class MessengerThread;
    friend class RTMessageTask;
    friend class RTMessageListener;


    
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
     * Configurasyon dosyasindaki bilgiler dosyaya kayit edilir.
     *
     * @return Kayit basarili olursa ise true, olmazsa false getirir.
     */
    bool saveConfigFile();

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

    /** Benzetimi Arayuz ile yuruten fonksiyon */
    bool runWithGUI( );

    /** Benzetimi Console ile yuruten fonksiyon */
    bool runWithConsole( );

    /** Stop isleminden sonra heapleri temizler */
    void cleanLoggerHeaps( );
    
    /** update edilen config (temp) ile kullanicinin configini degistirir */
    void changeConfig();
    
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
    
    /** Programin config dosyasi uretmesi icin calistirildigi bilgisi */
    bool isConfig;
    
  
    
    /** Programin gui ile calistirildigi bilgisi */
    stateTypes zenomState;

    /** Loop isleminde hesaplanan degerlerin yazilacagi heap */
    HeapXn *controlHeap;

    /** ControlHeap baslangic adresi */
    double *controlHeapAddress;

    /** Programin calistiracagi main task */
    LoopTask *loopTask;

    /** Heapdeki degerleri log edecek task */
    LoggerTask *logTask;

    /** Programin calistiracagi main task */
    RTMessageTask *rtMessageTask;
    
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

    /** GUI ile mesaj alisverisi yapan thread */
    MessengerThread *messengerThread;

    /** GUI ile haberlesmeyi saglayan mesaj kuyrugu */
    guiMessenger *guiComQueueReceiver;

    /** GUI ile haberlesmeyi saglayan mesaj kuyrugu */
    guiMessenger *guiComQueueSender;
    
    /** GUI ile RTNET arasindaki mesajlasmayi saglayan kuyruk */
    guiMessenger *rtnetComQueueSender;

    /** RTNet ile haberlesmeyi yapacak olan objeleri tutan dizi */
    Array<RTMessage *> messengerArray;
    
    /** Overrun sayisini tutan degisken*/
    unsigned long mOverrunCount;
    
    
    
    
    
    
    UDPXn rtnetUDPXn;
    RTMessageListener* rtnetListener;
    
    
};



/**
 * class LoopTask
 * --------------
 * ControlBase sinifinda kullanicinin implement ettigi doloop fonksiyonu
 * periyodik olarak calistirir, hesaplanan degerleri heape kopyalar.
 *
 */
class LoopTask : public TaskXn
{

public:
    LoopTask( ControlBase* cntrlBase )
    {
        controlBase = cntrlBase;
    }

private:
    ControlBase* controlBase;

    void run()
    {
        bool infinite = false;
        RTIME now, previous;

        rt_printf("controlBase start working\n");
        if(!controlBase->duration)
            infinite = true;

        this->setPeriodic( TM_NOW , ONESECOND / controlBase->frequency );
        previous = rt_timer_read();

        do
        {
            this->waitPeriod( &(controlBase->mOverrunCount) );
            
            if( controlBase->zenomState != PAUSE )
            {
                controlBase->doloop();
                controlBase->copyToSourceHeap();

                //rt_printf("Time : %f\n",controlBase->elapsedTimeSecond);
                //rt_printf("Sine : %f\n",controlBase->logVariableArray.getElement(1)->getElementPtr()[0]);
                //rt_printf("DSine : %f\n",controlBase->logVariableArray.getElement(2)->getElementPtr()[0]);

                now = rt_timer_read();
                controlBase->elapsedTimeSecond +=  ( (double)(now - previous) / ONESECOND );
                previous = now;
            }
            else
            {
                now = rt_timer_read();
                previous = now;
            }

            if ( controlBase->zenomState == STOP )
                break;
              

        }while( infinite || controlBase->elapsedTimeSecond <= (controlBase->duration ) );
       
        // Diger tasklar sonlanir.
        controlBase->zenomState = STOP;
       
    }
};


/**
 * class LoggerTask
 * ----------------
 * Heapden alinan verileri degiskenlerin icindeki heaplere kopyalar.
 */
class LoggerTask : public TaskXn
{
private:
    ControlBase* controlBase;

public:
    LoggerTask( ControlBase* cntrlBase )
    {
        controlBase = cntrlBase;

    }

    void run()
    {

        this->setPeriodic(TM_NOW, ONESECOND / controlBase->frequency );

        do
        {

            this->waitPeriod();
            
            if(controlBase->isGUI)
                controlBase->updateVariablesFromHeap();

            if( controlBase->zenomState == START )
            {
                for(int i = 0; i < controlBase->logVariableArray.getNumElements(); ++i)
                {
                    controlBase->logVariableArray.getElement(i)->copyFromSourceHeap();
                   
                }
            }

        }while( controlBase->zenomState != STOP );
        
    }
};


/**
 * class messengerTask
 * ----------------
 * GUI ile haberlesmeyi saglayan mesaj alim ve gonderim objesi
 */
class MessengerThread : public TaskXn
{
private:
    ControlBase* controlBase;

public:
    MessengerThread( ControlBase* cntrlBase )
    {
        controlBase = cntrlBase;

    }

    void run()
    {
        char msgBuf[MAXARRAYSIZE];
        char buffer[128];

        this->setPeriodic(TM_NOW, ONESECOND / controlBase->frequency/5 );
        
        while ( controlBase->zenomState != STOP )
        {
            this->waitPeriod();
            
            controlBase->guiComQueueReceiver->receiveMessage( msgBuf );
            if( !strcmp ( QUEUESTART , msgBuf ) )
            {
                snprintf(msgBuf,MAXARRAYSIZE," ");              
                controlBase->zenomState = START;
                strcpy(buffer,"--start");
                for(int i = 0; i < controlBase->messengerArray.getNumElements(); ++i)
                    controlBase->rtnetUDPXn.send(buffer, sizeof(char)*128,0, controlBase->messengerArray.getElement(i)->getIp()); 
            }
            else if( !strcmp ( QUEUEPAUSE , msgBuf ) )
            {
                snprintf(msgBuf,MAXARRAYSIZE," ");
                controlBase->zenomState = PAUSE ;
                strcpy(buffer,"--pause");
                for(int i = 0; i < controlBase->messengerArray.getNumElements(); ++i)
                    controlBase->rtnetUDPXn.send(buffer, sizeof(char)*128,0, controlBase->messengerArray.getElement(i)->getIp());                
                
            }
            else if( !strcmp ( QUEUESTOP , msgBuf ) )
            {
                snprintf(msgBuf,MAXARRAYSIZE," ");
                controlBase->zenomState = STOP ;
                strcpy(buffer,"--stop");
                for(int i = 0; i < controlBase->messengerArray.getNumElements(); ++i)
                    controlBase->rtnetUDPXn.send(buffer, sizeof(char)*128,0, controlBase->messengerArray.getElement(i)->getIp());               
                
            }
        }
    } 


};


/**
 * class RTMessageTask
 * ----------------
 * RTNet ile haberlesmeyi saglayan fonksiyonlari frekansa gore calistirir
 */
class RTMessageTask : public TaskXn
{
private:
    ControlBase* controlBase;

public:
    RTMessageTask( ControlBase* cntrlBase )
    {
        controlBase = cntrlBase;

    }

    void run()
    {

        rt_printf("RTMessageTask started\n");
        this->setPeriodic(TM_NOW, ONESECOND / 200 );

        do
        {

            this->waitPeriod();

            if( controlBase->zenomState == START )
            {

                for(int i = 0; i < controlBase->messengerArray.getNumElements() ; ++i)
                {
                    controlBase->messengerArray.getElement(i)->communicate();
                }
            }

        }while( controlBase->zenomState != STOP );

    }
};


/**
 * class RTMessageTask
 * ----------------
 * RTNet ile haberlesmeyi saglayan fonksiyonlari frekansa gore calistirir
 */
class RTMessageListener : public TaskXn
{

    friend class LoopTask;
private:
    ControlBase* controlBase;
    bool runFlag;
    stateTypes prevState;
    
public:
    RTMessageListener( ControlBase* cntrlBase )
    {
        controlBase = cntrlBase;
        runFlag = true;
        prevState = STOP;
    }
    
    
    void setState(stateTypes state)
    {
        prevState = state;
    }
    

    void run()
    {
        char buffer[128];
        
        rt_printf("RT Message Listener started\n");
        this->setPeriodic(TM_NOW, ONESECOND );

        do
        {
            this->waitPeriod();

            if(controlBase->rtnetUDPXn.recv(buffer,128 * sizeof(char),0) == -1)
            {
                rt_printf("Message EchoTask: %s\n", strerror(controlBase->rtnetUDPXn.getErrnoError()));            
            }
            else
            {
                rt_printf("Gelen Message: %s\n", buffer);
                if(!strcmp(buffer,"--start") && prevState!= START )
                {
                    rt_printf("Message: START geldi\n");
                    controlBase->rtnetComQueueSender->sendStartMessage();
                    prevState = START;
                }
                else if(!strcmp(buffer,"--pause") && prevState != PAUSE )
                {
                    rt_printf("Message: PAUSE geldi\n");
                    controlBase->rtnetComQueueSender->sendPauseMessage();
                    prevState = PAUSE;
                }
                else if(!strcmp(buffer,"--stop") && prevState != STOP )
                {
                    rt_printf("Message: STOP geldi\n");
                    controlBase->rtnetComQueueSender->sendStopMessage();
                    prevState = STOP;
                }
                else
                    rt_printf("Message: %s\n", buffer);
            }

        }while( runFlag );

    }
    
    void stopThread()
    {
        runFlag = false;
    }
};


#endif	/* _CONTROLBASE_H */


