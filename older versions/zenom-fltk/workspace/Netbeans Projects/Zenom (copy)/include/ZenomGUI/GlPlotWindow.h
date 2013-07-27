/* 
 * File:   PlotWindow.h
 * Author: RobotLab
 *
 * Created on August 6, 2009, 2:43 PM
 */

#ifndef _GLPLOTWINDOW_H
#define	_GLPLOTWINDOW_H

#include "GlPlotWindowBase.h"
#include "Line.h"
#include "Config.h"

using namespace fltk;
using namespace std;



class GlPlotWindow : public GlPlotWindowBase
{
public :

   GlPlotWindow(int x,int y,int w,int h,const char *l=0);

   /**
   * Plot edilecek olan LogVariableGUI ve cizilecek olan indexini set eder
   *
   * @param logVar  set edilecek LogVariableGUI
   * @param logVar  cizilecek olan indexi
   */
   void addLogVariableGUI( LogVariableGUI *logVar , int index );

    /**
   * Plot edilen cizginin rengini degistiren fonksiyon
   *
   * @param logVar  rengi degistirelecek variable
   * @param index   rengi degistirelecek variable indexi
   * @param r       kirmizi renk degeri
   * @param b       mavi renk degeri
   * @param g       yesil renk degeri
   */
   void changeLogColor(LogVariableGUI* logVar, int index,int r,int b ,int g);


    /**
   * Plot edilen LogVariableGUIli plot isleminden cikartan fonksiyon
   *
   * @param logVar  cikartilacak olan LogVariableGUI
   * @param logVar  cizimi yapilan index
   */
   void removeLogVariableGUI( LogVariableGUI *logVar , int index );


    void draw();

    Array< LogVarLine > save();

    /**
   * Plot Ekranindaki Degerleri Matlab Formatinda kaydeder
   *
   * @param pOutputFile bilgilerin yazılacağı dosya
   */
   virtual void printLinesToMatlabFile( ofstream &pOutputFile ) ;


private:

    Array< Line *> lineArray;


};
  
  




#endif	/* _PLOTWINDOW_H */

