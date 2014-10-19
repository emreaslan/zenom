/* 
 * File:   LogVariableGUI.h
 * Author: root
 *
 * Created on September 4, 2009, 10:24 AM
 */

#ifndef _LOGVARIABLEGUI_H
#define	_LOGVARIABLEGUI_H

#include "LogVariableBase.h"

class LogVariableGUI : public LogVariableBase
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
    LogVariableGUI(double* addr,const char* name, const char* desc = NULL, int nRow = 1 , int nCol = 1 );

    /**
     * Constructor
     * Adres ve isim ile LogVariable objesi yaratilir.
     * @param addr        Degisken adresi
     * @param nm          Degisken ismi
     * @param nElements   Vector eleman sayisi
     * @param desc        Degiskenin tanimi
     */
    LogVariableGUI(int* addr,const char* name, const char* desc = NULL,int nRow = 1 , int nCol = 1 );


    /**
     * Constructor
     * Adres ve isim ile LogVariable objesi yaratilir.
     * @param addr        Degisken adresi
     * @param nm          Degisken ismi
     * @param nElements   Vector eleman sayisi
     * @param desc        Degiskenin tanimi
     */
    LogVariableGUI(double& addr,const char* name, const char* desc = NULL, int nRow = 1 , int nCol = 1 );


    /**
     * Destructor
     *
     */
    ~LogVariableGUI();

    /**
     */
    void copyTFSDtoHeap();


    int bindHeap();

    int unbindHeap();

    inline bool isBind() { return bind; }

    /**
     * Log degiskeni icindeki elementin ismini getirir.
     * @param element Ismi getirilecek log degiskeni element indexi
     */
    inline char* getSubNames(int element) { return subNames[element]; }

    /**
     * Log degiskeni icindeki elementin ismini getirir.
     * @param row Ismi getirilecek log degiskeni elementin bulundugu satir
     * @param col Ismi getirilecek log degiskeni elementin bulundugu satir
     */
    inline char* getSubNames(int row, int col) { return subNames[row*cols+col];}
    

    inline bool getMouseOver(int element) { return mouseOver[element]; }

    inline bool getMouseOver(int row, int col) { return mouseOver[row*cols+col];}

    inline void setMouseOver(int element, bool value) { mouseOver[element] = value; }

    inline void setMouseOver(int row, int col, bool value) { mouseOver[row*cols+col] = value;}

private:

    bool bind;

    bool isInt;

    /** log degiskeni eleman(lar)inin isimlerini tutar*/
    char** subNames;

    /** Plot ekraninda secili log degiskeni elemaninin degeri true olur*/
    bool* mouseOver;
};



#endif	/* _LOGVARIABLEGUI_H */

