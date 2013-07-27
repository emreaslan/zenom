/* 
 * File:   Variable.h
 * Author: casper
 *
 * Created on August 13, 2009, 9:45 AM
 */

#ifndef _VARIABLE_H
#define	_VARIABLE_H

#include <cstring>

/**
 * class Variable
 * --------------
 * Variable objesi controlbase sinifi icin gerekli LogVariable ve 
 * ControlVariable siniflari icin, temel siniftir.
 *
 */


class Variable
{
public:
    
    /**
     * Constructor
     * Adres ve isim ile Variable objesi yaratilir.
     * @param addr        Degisken adresi
     * @param nm          Degisken ismi
     * @param nElements   Vector eleman sayisi
     * @param desc        Degiskenin tanimi
     */
    Variable(double* addr,const char* nm, const char* desc = NULL , int nRow = 1, int nCol = 1 );

    /**
     * Constructor
     * Adres ve isim ile Variable objesi yaratilir.
     * @param addr        Degisken adresi
     * @param nm          Degisken ismi
     * @param nElements   Vector eleman sayisi
     * @param desc        Degiskenin tanimi
     */
    Variable(int* addr,const char* nm, const char* desc = NULL ,int nRow = 1, int nCol = 1 );
    
    /**
     * Destructor
     * Sistemden alinan yerler geri verilir.
     */
    ~Variable();
    
    // ----- ACCESSORS
    
    /**
     * Degiskenin ismini getirir.
     * @return Degisken ismi
     */
    inline const char* getName(){ return name; }
            
    /**
     * Degisken boyutunu getirir.
     * @return Degisken boyutu
     */
    inline int getSize(){ return size; }
    
    /**
     * Degiskenin satır sayısını getirir.
     * @return Degisken satır sayısı
     */
    inline int getRows(){ return rows; }

    /**
     * Degiskenin sütun sayısını getirir.
     * @return Degisken sütun sayısı
     */
    inline int getCols(){ return cols; }

    /**
     * Degiskenin tipini veren fonksiyon
     * @return int olup olmama bilgisi
     */
    inline bool isInteger(){ return isInt; }

    /**
     * Indexteki elemani gunceller.
     * @param index Guncellenecek index
     * @param value Yeni deger
     */
    void setElement(int index, double value);

    /**
     * Degisken degerlerini gunceller.
     * @param row Guncellenecek verinin satir numarasi
     * @param col Guncellenecek verinin sutun numarasi
     * @param Yeni deger
     */
    void setElement(int row, int col, double value);

    /**
     * Indexteki elemani getirir.
     * @param index Dizi indeksi
     * @return Indexteki eleman
     */
    inline double getElement(int index)
    {
        if(isInt)
            return (double)intAddress[index];
        else
            return address[index];
    }


    /**
     * Indexteki elemani getirir.
     * @param row Istenilen elementin satir sayisi
     * @param col Istenilen elementin sutun sayisi
     * @return Indexteki eleman
     */
    inline double getElement(int row, int col){ return address[row*cols+col]; }
    
    /**
     * Degiskenin tanimini getirir.
     * @return Degisken tanimi
     */
    inline const char* getDescription(){ return description; }
    
    /**
     * Degiskenin tanimini gunceller.
     * @param desc Yeni degisken tanimi
     */  
    void setDescription (const char *desc);

    /**
     * Degiskenin tanimini gunceller.
     * @return Bilgilerin tutuldugu dizi pointeri
     */
    inline double* getElementPtr (){return address;}

    /**
     * Degiskenin tanimini gunceller.
     * @return Bilgilerin tutuldugu dizi pointeri
     */
    inline int* getIntElementPtr (){return intAddress;}

    /**
     * Degiskenin hafizada tuttugu yeri dondurur.
     * @return Hafizada tutulan byte sayisi
     */
    inline size_t getSizeOf () { return sizeof (double ) * rows * cols; }

protected:
        
    /** Degisken adresi */
    double* address;

    /** Degisken adresi */
    int* intAddress;

    /** int olup olmama bilgisi */
    bool isInt;
    
    /** Degisken ismi */
    char* name;

    /** Degisken boyutu */
    int size;

    /** Degisken satir sayisi */
    int rows;

    /** Degisken sutun sayisi */
    int cols;

    /** Degisken tanimi */
    char* description;
    
};

#endif	/* _VARIABLE_H */

