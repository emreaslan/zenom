/* 
 * File:   ControlVariable.h
 * Author: casper
 *
 * Created on August 13, 2009, 10:02 AM
 */

#ifndef _CONTROLVARIABLE_H
#define	_CONTROLVARIABLE_H

#include "Variable.h"

/**
 * class ControlVariable
 *---------------
 * controlbase sinifi icin gerekli ControlVariable bilgilerini iceren siniftir.
 *
 */


class ControlVariable : public Variable
{   
    
public:
    /**
     * Constructor
     * Adres ve isim ile ControlVariable objesi yaratilir.
     * @param addr        Degisken adresi
     * @param nm          Degisken ismi
     * @param nElements   Vector eleman sayisi
     * @param desc        Degiskenin tanimi
    */
    ControlVariable(double* addr, const char* name,const char* desc = NULL,int nRow = 1 , int nCol = 1);
        
    /**
     * Constructor
     * Adres ve isim ile ControlVariable objesi yaratilir.
     * @param addr        Degisken adresi
     * @param nm          Degisken ismi
     * @param nElements   Vector eleman sayisi
     * @param desc        Degiskenin tanimi
    */
    ControlVariable(double& addr, const char* name,const char* desc = NULL);
            
    // ----- MANIPULATORS
    
    /**
     * Source Heapdeki veriyi sinif icersindeki heape kopyalar.
     */
    void copyToHeap();

    /*
     * Source Heapdeki veriyi sinif icersindeki heape kopyalar.
     * @param sourceAddr Heapteki control bilgisinin adresi
     */
    void setSourceHeapAddress(double* sourceAddr);

    /**
     * Source Heapdeki veriyi sinif icersindeki heape kopyalar.
     * @return Bilginin heapteki adresi
     */
    inline double* getSourceHeapAddress(){ return sourceHeapAddress; }

private:

    /** Bilginin alinacagi baslangic adresi */
    double* sourceHeapAddress;    
};

#endif	/* _ControlVariable_H */

