/* 
 * File:   LineXY.h
 * Author: root
 *
 * Created on September 4, 2009, 4:01 PM
 */

#ifndef _LINEXY_H
#define	_LINEXY_H

#include "LineBase.h"

class LineXY : public LineBase
{
public:

    /**
     * Constructor
     * Line objesi olusturur
     * @param logVar      Cizginin cizecegi LogVariableGUI
     * @param index       Cizilecek objenin indexi
     * @param logVar      Cizginin cizecegi LogVariableGUI
    */
    LineXY ( LogVariableGUI* logVar );

    /**
     * Cizgiyi ekrana cizen fonksiyon
     */
    int draw();

    /**
     * Cizgi bilgilerini matlab formatinda dosyaya kayeden fonksiyon
     * @ param pOutputFile Bilgilerin yazilacagi dosya
     */
    virtual void printLineToMatlabFile(ofstream &pOutputFile);

private :

    int logIndex;

    int logIndexXY;

};



#endif	/* _LINEXY_H */

