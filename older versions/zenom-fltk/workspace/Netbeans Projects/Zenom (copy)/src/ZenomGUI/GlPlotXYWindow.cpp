
#include "GlPlotXYWindow.h"


//==============================================================================
// GlPlotXYWindow::GlPlotXYWindow
//==============================================================================
GlPlotXYWindow::GlPlotXYWindow(int x,int y,int w,int h,const char *l) : GlPlotWindowBase(x,y,w,h,l)
{
  timeEnd = 10 ;
  timeBegin = 0 ;

  valueEnd = 5;
  valueBegin = -5 ;

  scaleX = 0.1;
  scaleY = 0.1;
  translateX = 10;
  translateY = 0;



}


//==============================================================================
// GlPlotWindowXY::addLogVariableGUI
//==============================================================================
void GlPlotXYWindow::addLogVariableGUI(LogVariableGUI* logVar)
{
    LineXY *lineXYptr = new LineXY(logVar);
    lineXYarray.appendElement(lineXYptr);
}


//==============================================================================
// GlPlotWindowXY::removeLogVariableGUI
//==============================================================================
void GlPlotXYWindow::removeLogVariableGUI(LogVariableGUI* logVar)
{
    for(int counter = 0 ; counter < lineXYarray.getNumElements() ; ++counter)
        if(lineXYarray.getElement(counter)->getLogVariableGUI() == logVar )
        {
            lineXYarray.removeElement(counter);
            break;
        }
}

//==============================================================================
// GlPlotWindowXY::changeLogColor
//==============================================================================
void GlPlotXYWindow::changeLogColor(LogVariableGUI* logVar,int r,int g,int b)
{

    for(int counter = 0 ; counter < lineXYarray.getNumElements() ; ++counter)
    {
        if(lineXYarray.getElement(counter)->getLogVariableGUI() == logVar )
            lineXYarray.getElement(counter)->setColor(r,g,b);
    }

}

//==============================================================================
// GlPlotXYWindow::draw
//==============================================================================
void GlPlotXYWindow::draw()
{
   
// the valid() property may be used to avoid reinitializing your
// GL transformation for each redraw:
  if (!valid())
  {
    valid(1);
    glLoadIdentity();
    glMatrixMode(GL_PROJECTION_MATRIX);
    glViewport(0,0,w(),h());
    glDisable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);
  }

  glPushMatrix();




  if( ((autoTranslate || autoScale) && (lineXYarray.getNumElements() != 0) ) && (lineXYarray.getElement(0)->getLogVariableGUI()->isBind() ))
  {
      double maxY = -1000000000;
      double minY =  1000000000;
      double maxX = -1000000000;
      double minX =  1000000000;

      for (int counter = 0 ; counter < lineXYarray.getNumElements() ; ++counter )
      {
          if(maxY < lineXYarray.getElement(counter)->getMaxValueY() )
              maxY = lineXYarray.getElement(counter)->getMaxValueY();

          if(minY > lineXYarray.getElement(counter)->getMinValueY() )
              minY = lineXYarray.getElement(counter)->getMinValueY();

          if(maxX < lineXYarray.getElement(counter)->getMaxValueX() )
              maxX = lineXYarray.getElement(counter)->getMaxValueX();

          if(minX > lineXYarray.getElement(counter)->getMinValueX() )
              minX = lineXYarray.getElement(counter)->getMinValueX();
      }

      double rangeY = maxY+minY;
      double rangeX = maxX+minX;

      /*cout << "MaxX :" << maxX << endl;
      cout << "MaxY :" << maxY << endl;
      cout << "MinX :" << minX << endl;
      cout << "MinY :" << minY << endl;*/


      if(autoTranslate)
      {
          translateX = rangeX/2;
          scaleX = 1;
      }
      else
      {
          translateX = rangeX/2 ;
          scaleX = 1 / ( (maxX-minX/1.80) );
      }

      if (maxY == minY)
          scaleY = 1/1.70;
      else
          scaleY = 1/((maxY-minY)/1.70);


      translateY = rangeY/2;


  }

  glScalef(scaleX,scaleY,0);
  glTranslatef(-translateX,-translateY,0);


  double timeRange = 1 / scaleX ;
  double valueRange = 1 / scaleY ;

  timeEnd = translateX + timeRange ;
  timeBegin = translateX - timeRange ;

  valueEnd = translateY + valueRange;
  valueBegin = translateY  - valueRange ;



  drawGrid(timeEnd,timeBegin,valueEnd,valueBegin);


  for (double counter = 0 ; counter < lineXYarray.getNumElements() ; ++counter )
  {
      if(autoScale)
          lineXYarray.getElement(counter)->setTimeRange(-1000,1000);
      else
          lineXYarray.getElement(counter)->setTimeRange(timeBegin-1,timeEnd+1);
      if(lineXYarray.getElement(counter)->draw() )
          lineXYarray.removeElement(counter);
  }

  glPopMatrix();

}


//==============================================================================
// GlPlotXYWindow::save
//==============================================================================
Array< LogVarLine > GlPlotXYWindow::save()
{
    Array< LogVarLine > rValue;
    LogVarLine line;

    for (int i = 0 ; i < lineXYarray.getNumElements() ; ++i )
    {
        line.logVariable = lineXYarray.getElement(i)->getLogVariableGUI();
        line.r = lineXYarray.getElement(i)->getR();
        line.g = lineXYarray.getElement(i)->getG();
        line.b = lineXYarray.getElement(i)->getB();
        rValue.appendElement(line);
    }

    return rValue;
}

//==============================================================================
// GlPlotWindow::printLinesToMatlabFile
//==============================================================================
void GlPlotXYWindow::printLinesToMatlabFile( ofstream &pOutputFile )
{
    for (int i = 0 ; i < lineXYarray.getNumElements() ; ++i )
        lineXYarray.getElement(i)->printLineToMatlabFile(pOutputFile);
}