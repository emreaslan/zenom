#include "PlotRectangle.h"




//==============================================================================
// PlotRectangle::PlotRectangle()
//==============================================================================

PlotRectangle::PlotRectangle(int x, int y):beginX(x),beginY(y),currentX(-1),currentY(-1)
{

}


//==============================================================================
// PlotRectangle::setLastPoint()
//==============================================================================
void PlotRectangle::setLastPoint(int x, int y)
{
    currentX = x;
    currentY = y;
}


//==============================================================================
// PlotRectangle::setStartPoint()
//==============================================================================
void PlotRectangle::setStartPoint(int x, int y)
{
    beginX = x;
    beginY = y;
}

//==============================================================================
// PlotRectangle::setWindowSize()
//==============================================================================
void PlotRectangle::setWindowSize(int x, int y)
{
    winSizeX = x;
    winSizeY = y;

}

//==============================================================================
// PlotRectangle::setRanges()
//==============================================================================
void PlotRectangle::setRanges( double XrangeMin, double XrangeMax,double YrangeMin, double YrangeMax )
{
    rangeMaxX = XrangeMax;
    rangeMaxY = YrangeMax;

    rangeMinX = XrangeMin;
    rangeMinY = YrangeMin;
}

//==============================================================================
// PlotRectangle::getScaleX()
//==============================================================================
double PlotRectangle::getScaleX()
{
    double diff = fabs(beginPointX - endPointX);

    return 2.0/diff;
}

//==============================================================================
// PlotRectangle::getScaleY()
//==============================================================================
double PlotRectangle::getScaleY()
{
    double diff = fabs(beginPointY - endPointY);

    return 2.0/diff;
}


//==============================================================================
// PlotRectangle::getTranslateX()
//==============================================================================
double PlotRectangle::getTranslateX()
{
    double diff = beginPointX + endPointX;

    return diff/2;
}


//==============================================================================
// PlotRectangle::getTranslateY()
//==============================================================================
double PlotRectangle::getTranslateY()
{
    double diff = beginPointY + endPointY;

    return diff/2;
}

//==============================================================================
// PlotRectangle::draw()
//==============================================================================
void PlotRectangle::draw()
{
    if( (currentX != -1) && (currentY != -1) )
    {
        beginPointX = rangeMinX + ( (rangeMaxX-rangeMinX)/winSizeX * beginX );
        beginPointY = rangeMaxY - ( (rangeMaxY-rangeMinY)/winSizeY * beginY );

        endPointX = rangeMinX + ( (rangeMaxX-rangeMinX)/winSizeX * currentX );
        endPointY = rangeMaxY - ( (rangeMaxY-rangeMinY)/winSizeY * currentY );


        glColor3f(0,0,1);
        glBegin(GL_LINES);


            glVertex2f( beginPointX ,beginPointY);
            glVertex2f( endPointX ,beginPointY);

            glVertex2f( beginPointX, beginPointY);
            glVertex2f( beginPointX, endPointY);

            glVertex2f( endPointX , beginPointY);
            glVertex2f( endPointX , endPointY);

            glVertex2f( beginPointX ,endPointY);
            glVertex2f( endPointX , endPointY);

        glEnd();
    }
}
