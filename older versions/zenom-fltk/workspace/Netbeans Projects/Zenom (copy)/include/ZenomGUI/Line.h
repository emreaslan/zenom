/* 
 * File:   Line.h
 * Author: root
 *
 * Created on August 25, 2009, 12:07 PM
 */

#ifndef LINE_H
#define	LINE_H

#include "LineBase.h"


class Line : public LineBase
{
public:

    /**
     * Constructor
     * Line objesi olusturur
     * @param logVar      Cizginin cizecegi LogVariableGUI
     * @param index       Cizilecek objenin indexi
     * @param logVar      Cizginin cizecegi LogVariableGUI
     * @param index       Cizilecek objenin indexi
    */
    Line ( LogVariableGUI* logVar , int index );

    /**
     * Plot edilen indexi donduren fonksiyon
     *
     * @return plot edilen index
     */
    int getLogIndex(){return this->logIndex;};


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
};


#endif	/* _LINE_H */

