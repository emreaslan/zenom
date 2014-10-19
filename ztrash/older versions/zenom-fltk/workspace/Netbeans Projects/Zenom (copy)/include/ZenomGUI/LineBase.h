/* 
 * File:   LineBase.h
 * Author: root
 *
 * Created on September 4, 2009, 3:49 PM
 */

#ifndef _LINEBASE_H
#define	_LINEBASE_H

#include <fltk/glut.h>
#include <fltk/gl.h>
#include <fltk/Color.h>
#include <math.h>
#include "guiMessenger.h"
#include "LogVariableGUI.h"
#include "Constants.h"
#include <iostream>
#include <fstream>

using namespace std;


class LineBase
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
    LineBase ( LogVariableGUI* logVar );

    /**
     * Cizginin rengini ayarlayan fonksiyon
     *
     * @param R   Kirmizi renk miktari
     * @param G   Yesil renk miktari
     * @param B   Mavi renk miktari
    */
    void setColor( int R, int G, int B );

    int getColor() { return fltk::color(r,g,b); }
    int getR(){ return r*255;}
    int getG(){ return g*255;}
    int getB(){ return b*255;}

    /**
     * Cizginin cizilecegi zaman dilimini ayarlar
     *
     * @param begin  Cizime baslama zamani
     * @param end    Cizimin bitme zamani
    */
    void setTimeRange(double begin,double end);

    /**
     * Plot edilen degerler arasinda guncel en buyuk degeri donduren fonksiyon
     *
     * @return plot edilen degerler arasinda guncel en buyuk deger
     */
    double getMaxValueX(){return valueMaxX;}

    /**
     * Plot edilen degerler arasinda guncel en kucuk degeri donduren fonksiyon
     *
     * @return plot edilen degerler arasinda guncel en kucuk deger
     */
    double getMinValueX(){return valueMinX;}


    /**
     * Plot edilen degerler arasinda guncel en buyuk degeri donduren fonksiyon
     *
     * @return plot edilen degerler arasinda guncel en buyuk deger
     */
    double getMaxValueY(){return valueMaxY;}

    /**
     * Plot edilen degerler arasinda guncel en kucuk degeri donduren fonksiyon
     *
     * @return plot edilen degerler arasinda guncel en kucuk deger
     */
    double getMinValueY(){return valueMinY;}



    /**
     * Plot edilen LogVariableGUI objesini donduren fonksiyon
     *
     * @return plot edilen LogVariableGUI
     */
    LogVariableGUI* getLogVariableGUI(){return logVariableGUI;};


    /**
     * Cizgiyi ekrana cizen fonksiyon
     */
    int draw();

    /**
     * Hata durumunda hatayi gonderen messsenger objesi
     */
    inline void setMessengerObj(guiMessenger* messenger){guiComQueueSender=messenger;}

    /**
     * Cizgi bilgilerini matlab formatinda dosyaya kayeden fonksiyon
     * @ param pOutputFile Bilgilerin yazilacagi dosya
     */
    virtual void printLineToMatlabFile(ofstream &pOutputFile) = 0;


protected:

    /** Zaman araliklarina gore LogVariableGUI icindeki heap icinde,
     baslangic ve bitis araliklarini bulmak icin kullanilan fonksiyon */
    int findHeapIndex ( double timeBegin ,double timeEnd, int & bginIndex,int &endIndex  );

    
    double valueMaxY,valueMinY;
    double valueMaxX,valueMinX;

    float r,g,b;

    LogVariableGUI *logVariableGUI;

    double rangeBegin,rangeEnd;

    guiMessenger * guiComQueueSender;

    double UpperBound;
    double LowerBound;


};


#endif	/* _LINEBASE_H */

