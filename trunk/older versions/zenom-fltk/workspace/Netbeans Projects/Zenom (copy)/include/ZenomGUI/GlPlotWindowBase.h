/* 
 * File:   GlPlotWindowBase.h
 * Author: root
 *
 * Created on September 4, 2009, 3:21 PM
 */

#ifndef _GLPLOTWINDOWBASE_H
#define	_GLPLOTWINDOWBASE_H


#include <fltk/run.h>
#include <fltk/Slider.h>
#include <fltk/math.h>
#include <fltk/draw.h>
#include <fltk/glut.h>
#include <fltk/events.h>
#include <vector>
#include <iostream>
#include <fltk/gl.h>
#include <fltk/GlWindow.h>
#include "LogVariableGUI.h"
#include "guiMessenger.h"
#include "Array.h"
#include "PlotRectangle.h"
#include <cmath>

using namespace fltk;
using namespace std;

#define HAVE_GL 1

class GlPlotWindowBase : public GlWindow
{
public:

  void setTranslateX(float x)
  {
      translateX = x;
  }

  void setTranslateY(float y)
  {
      translateY = y;
  }

  void setZoomX(float x)
  {
      if((3.65147e-10 < x) && (5000 > x) )
        scaleX = x;
  }

  void setZoomY(float y)
  {
      if((3.65147e-10 < y) && (5000 > y))
          scaleY = y;
  }


  inline double getZoomX(){return scaleX;}

  inline double getZoomY(){return scaleY;}

  inline double getTranslateX(){return translateX;}

  inline double getTranslateY(){return translateY;}

  GlPlotWindowBase(int x,int y,int w,int h,const char *l=0);




  /**
   * Plot isleminde otomatik olceklemeyi aktif deaktif eden fonksiyon
   *
   * @param aScale  olcekleme aktif deakftif degeri
   */
   void setAutoScale( bool aScale ){ autoScale = aScale; }

   /**
   * Plot isleminde otomatik kaydirmayi aktif deaktif eden fonksiyon
   *
   * @param aTranslate  kaydirma aktif deakftif degeri
   */
   void setAutoTranslate( bool aTranslate ){ autoTranslate = aTranslate; }

   /**
   * Plot Ekranindaki Degerleri Matlab Formatinda kaydeder
   *
   * @param pOutputFile bilgilerin yazılacağı dosya
   */
   virtual void printLinesToMatlabFile( ofstream &pOutputFile ) = 0;

   inline void setMessengerObj(guiMessenger* messenger){guiComQueueSender=messenger;}

   void calculateDiffAxis(double &diff);

   double calculateBeginValue (double beginRange , double diff );

   double calculateX();
   double calculateY();



protected:

    double calculateTransDiffX(int);
    double calculateTransDiffY(int);

    virtual int handle(int e);

    int mousePosX();

    int mousePosY();

    void drawGrid(double xRangeMax , double xRangeMin , double yRangeMax , double yRangeMin);


    float translateX,translateY;

    float scaleX,scaleY;

    int zoomX,zoomY;

    Array < LogVariableGUI *> *LogVariableGUIArray;

    bool autoScale;

    bool autoTranslate;

    guiMessenger* guiComQueueSender;

    PlotRectangle *selectRectangle;

    int preMousePosX,preMousePosY;
    
};



#endif	/* _GLPLOTWINDOWBASE_H */

