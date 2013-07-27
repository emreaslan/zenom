/*
 * File:   LogVariableBase.h
 * Author: husu
 *
 * Created on August 13, 2009, 10:02 AM
 */

#ifndef _LOGVARIABLEBASE_H
#define	_LOGVARIABLEBASE_H

#include "Variable.h"
#include "Array.h"


/**
 * class LogVariable
 *---------------
 * controlbase sinifi icin gerekli LogVariable bilgilerini iceren siniftir.
 *
 */

class LogVariableBase : public Variable
{

public:
    /**
     * Constructor
     * Adres ve isim ile LogVariable objesi yaratilir.
     * @param addr        Degisken adresi
     * @param nm          Degisken ismi
     * @param nElements   Vector eleman sayisi
     * @param desc        Degiskenin tanimi
     */
    LogVariableBase(double* addr,const char* name, const char* desc = NULL, int nRow = 1 , int nCol = 1 );

    /**
     * Constructor
     * Adres ve isim ile LogVariable objesi yaratilir.
     * @param addr        Degisken adresi
     * @param nm          Degisken ismi
     * @param nElements   Vector eleman sayisi
     * @param desc        Degiskenin tanimi
     */
    LogVariableBase(int* addr,const char* name, const char* desc = NULL,int nRow = 1 , int nCol = 1 );


    /**
     * Constructor
     * Adres ve isim ile LogVariable objesi yaratilir.
     * @param addr        Degisken adresi
     * @param nm          Degisken ismi
     * @param nElements   Vector eleman sayisi
     * @param desc        Degiskenin tanimi
     */
    LogVariableBase(double& addr,const char* name, const char* desc = NULL, int nRow = 1 , int nCol = 1 );


    /**
     * Destructor
     *
     */
    ~LogVariableBase();




    // ----- ACCESSORS

    /**
     * Heap icersindeki elemani getirir.
     * @param index Index
     * @return Heapdeki index sirasindaki eleman
     */
    inline double getHeapElement(int index){ return logHeapBeginAddr[index]; }

     /**
     * Heap icersindeki en son elemani getirir.
     * @param row
     * @param column
     * @return Heapdeki row column degerindeki son eleman
     */
    double getLastHeapElement(int row, int column);

     /**
     * Heap icersindeki en son elemani getirir.
     * @param index 
     * @return Heapdeki index degerindeki son eleman
     */
    double getLastHeapElement(int index);

    /**
     * Log degiskeni frekansini getirir.
     * @return Degisken frekansi
     */
    inline double getFrequency(){ return frequency; }

    /**
     * Log degiskeni frekansini gunceller.
     * @param Logfrequency  Yeni frekans
     */
    void setFrequency(double Logfrequency);

    /**
     * Log degiskeninin devam edecegi sureyi getirir.
     * @return Degisken süreci
     */
    inline double getDuration(){ return duration; }

    /**
     * Log degiskeninin devam edecegi sureyi gunceller.
     * @param logDuration  Yeni sürec
     */
    void setDuration(double logDuration);

    /**
     * Log degiskenin baslayacagi sureyi getirir.
     * @return Degiskenin baslangic zamani
     */
    inline double getStartTime(){ return startTime; }

    /**
     * Log degiskenin baslayacagi sureyi gunceller.
     * @param logStartTime  Yeni baslangic zamani
     */
    void setStartTime(double logStartTime);

    /**
     * Bilginin alindigi adresi getirir.
     * @return Bilginin alindigi adres
     */
    inline double* getSourceAddress(){ return sourceHeapAddress; }

    /**
     * Bilginin alindigi adresi gunceller.
     * @param sourceAddress  Bilginin alinacagi yeni adres
     */
    void setSourceAddress(double* sourceAddress);

    /**
     * Bilginin islenme zamninin alindigi adresi gunceller.
     * @param timeAddress  Bilginin islenme zamanini iceren yeni adres
     */
    void setTimeAddress(double* timeAddress);

    /**
     * LogVariable icin heapte set edilecek degerlerin adresi
     * @param addr  Set edilecek bilgilerin adresi
     */
    void setHeapTFSDaddr(double *addr)
    {
        heapTFSDaddr = addr;
    }

    /**
     * LogVariable icin heapteki degiskenin adresi veren fonksiyon
     * @return  Set edilecek bilgilerin adresi
     */
    inline double* getHeapTFSDaddr(){return heapTFSDaddr;}

    

    


protected:

    /** Log degiskeni frekansini */
    double frequency;

    /** Log degiskeni devam etme süresi */
    double duration;

    /** Log degiskeni baslangic zamani */
    double startTime;

    /** Log degiskeninin verilerinin tutulacagi adres*/
    double* logHeapBeginAddr;

    /** Log degiskeninin verilerinin tutulacagi adres*/
    double* logHeapIndex;

    /** Bilginin alinacagi baslangic adresi */
    double* sourceHeapAddress;

    /** Bilginin alinacagi baslangic adresi */
    double* timeHeapAddress;

    /** Heapte set edilecek bilgilerin tutuldugu adres */
    double* heapTFSDaddr;



};

#endif	/* _LOGVARIABLE_H */

