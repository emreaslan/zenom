/* 
 * File:   LogVariable.h
 * Author: casper
 *
 * Created on August 13, 2009, 10:02 AM
 */

#ifndef _LOGVARIABLE_H
#define	_LOGVARIABLE_H

#include "LogVariableBase.h"


/**
 * class LogVariable
 *---------------
 * controlbase sinifi icin gerekli LogVariable bilgilerini iceren siniftir.
 *
 */

class LogVariable : public LogVariableBase
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
    LogVariable(double* addr,const char* name, const char* desc = NULL, int nRow = 1 , int nCol = 1 );

    /**
     * Constructor
     * Adres ve isim ile LogVariable objesi yaratilir.
     * @param addr        Degisken adresi
     * @param nm          Degisken ismi
     * @param nElements   Vector eleman sayisi
     * @param desc        Degiskenin tanimi
     */
    LogVariable(int* addr,const char* name, const char* desc = NULL,int nRow = 1 , int nCol = 1 );

        
    /**
     * Constructor
     * Adres ve isim ile LogVariable objesi yaratilir.
     * @param addr        Degisken adresi
     * @param nm          Degisken ismi
     * @param nElements   Vector eleman sayisi
     * @param desc        Degiskenin tanimi
     */
    LogVariable(double& addr,const char* name, const char* desc = NULL, int nRow = 1 , int nCol = 1 );
      

    /**
     * Destructor
     * 
     */
    ~LogVariable();
      
     /**
     * Programin kac dongude bir calisacagini set eden fonksiyon
     * @param dongu sayisi
     */
    void setLogPeriod(const int period)
    {
        logPeriod = period;
        logPeriodCounter = 0;
    }



private:

    bool isInt;

    int logPeriod;

    int logPeriodCounter;

};

#endif	/* _LOGVARIABLE_H */

