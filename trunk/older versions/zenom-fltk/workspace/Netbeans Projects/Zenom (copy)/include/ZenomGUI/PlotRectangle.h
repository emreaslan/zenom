/* 
 * File:   Rectangle.h
 * Author: root
 *
 * Created on September 14, 2009, 9:44 AM
 */

#ifndef _PLOTRECTANGLE_H
#define	_PLOTRECTANGLE_H


#include <fltk/run.h>
#include <fltk/math.h>
#include <fltk/draw.h>
#include <fltk/glut.h>
#include <vector>
#include <iostream>
#include <fltk/gl.h>

using namespace std;

class PlotRectangle
{
public:

    PlotRectangle(int x,int y);

    void setStartPoint(int x, int y);

    void setLastPoint (int x,int y);

    void draw();

    void setRanges( double XrangeMin, double XrangeMax,double YrangeMin, double YrangeMax );

    void setWindowSize(int x, int y);

    double getScaleX();

    double getScaleY();

    double getTranslateX();

    double getTranslateY();

private:

    int beginX,beginY,currentX,currentY;

    double rangeMinX, rangeMaxX, rangeMinY, rangeMaxY;

    int winSizeX,winSizeY;

     double beginPointX;
     double beginPointY;
     double endPointX;
     double endPointY;
};



#endif	/* _RECTANGLE_H */

