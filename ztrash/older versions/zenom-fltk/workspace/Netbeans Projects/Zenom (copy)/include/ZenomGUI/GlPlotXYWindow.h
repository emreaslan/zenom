/* 
 * File:   GlPlotWindowXY.h
 * Author: root
 *
 * Created on September 4, 2009, 3:31 PM
 */

#ifndef _GLPLOTXYWINDOW_H
#define	_GLPLOTXYWINDOW_H

#include "LineXY.h"
#include "GlPlotWindowBase.h"
#include "Config.h"

class GlPlotXYWindow : public GlPlotWindowBase
{

public:
    GlPlotXYWindow(int x,int y,int w,int h,const char *l=0);


    /**
   * Plot edilecek olan LogVariableGUI ve cizilecek olan indexini set eder
   *
   * @param logVar  set edilecek LogVariableGUI
   * @param logVar  cizilecek olan indexi
   */
   void addLogVariableGUI( LogVariableGUI *logVar );

    /**
   * Plot edilen cizginin rengini degistiren fonksiyon
   *
   * @param logVar  rengi degistirelecek variable
   * @param index   rengi degistirelecek variable indexi
   * @param r       kirmizi renk degeri
   * @param b       mavi renk degeri
   * @param g       yesil renk degeri
   */
   void changeLogColor(LogVariableGUI* logVar,int r,int b ,int g);


    /**
   * Plot edilen LogVariableGUIli plot isleminden cikartan fonksiyon
   *
   * @param logVar  cikartilacak olan LogVariableGUI
   * @param logVar  cizimi yapilan index
   */
   void removeLogVariableGUI( LogVariableGUI *logVar  );

    void draw();

    Array< LogVarLine > save();

    /**
   * Plot Ekranindaki Degerleri Matlab Formatinda kaydeder
   *
   * @param pOutputFile bilgilerin yazılacağı dosya
   */
   virtual void printLinesToMatlabFile( ofstream &pOutputFile );


private:

    Array< LineXY *> lineXYarray;

    double timeEnd ;
    double timeBegin;

    double valueEnd ;
    double valueBegin ;

};




#endif	/* _GLPLOTWINDOWXY_H */

