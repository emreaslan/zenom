#include "GlPlotWindow.h"
#include "Config.h"


//==============================================================================
// GlPlotWindow::GlPlotWindow
//==============================================================================
GlPlotWindow::GlPlotWindow(int x,int y,int w,int h,const char *l) : GlPlotWindowBase(x,y,w,h,l)
{

}




//==============================================================================
// GlPlotWindow::addLogVariableGUI
//==============================================================================
void GlPlotWindow::addLogVariableGUI(LogVariableGUI* logVar, int index)
{
    Line *linePtr = new Line(logVar,index);
    lineArray.appendElement(linePtr);
}


//==============================================================================
// GlPlotWindow::removeLogVariableGUI
//==============================================================================
void GlPlotWindow::removeLogVariableGUI(LogVariableGUI* logVar, int index)
{
    for(int counter = 0 ; counter < lineArray.getNumElements() ; ++counter)
    {
        if(lineArray.getElement(counter)->getLogVariableGUI() == logVar )
            if(lineArray.getElement(counter)->getLogIndex() == index )
            {
                lineArray.removeElement(counter);
                break;
            }
    }

}

//==============================================================================
// GlPlotWindow::changeLogColor
//==============================================================================
void GlPlotWindow::changeLogColor(LogVariableGUI* logVar, int index,int r,int g,int b)
{

    for(int counter = 0 ; counter < lineArray.getNumElements() ; ++counter)
    {
        if(lineArray.getElement(counter)->getLogVariableGUI() == logVar )
            if(lineArray.getElement(counter)->getLogIndex() == index )
            {
                lineArray.getElement(counter)->setColor(r,g,b);
                break;
            }
    }

}


//==============================================================================
// GlPlotWindow::draw
//==============================================================================
void GlPlotWindow::draw()
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




  if( ((autoTranslate || autoScale) && (lineArray.getNumElements() != 0) ) && (lineArray.getElement(0)->getLogVariableGUI()->isBind() ))
  {
      double time = lineArray.getElement(0)->getLogVariableGUI()->
                    getHeapElement(lineArray.getElement(0)->getLogVariableGUI()->
                    getHeapElement(0) + lineArray.getElement(0)->
                    getLogVariableGUI()->getSize() );

      double max = -1000000000;
      double min =  1000000000;

      for (int counter = 0 ; counter < lineArray.getNumElements() ; ++counter )
      {
          if(max < lineArray.getElement(counter)->getMaxValueY() )
              max = lineArray.getElement(counter)->getMaxValueY();

          if(min > lineArray.getElement(counter)->getMinValueY() )
              min = lineArray.getElement(counter)->getMinValueY();
      }

      double range = max+min;

      if(autoTranslate)
      {
          translateX = time;
          scaleX = 1;
      }
      else
      {
          translateX = time / 1.80;
          scaleX = 1 / (time/1.80);
      }

      if (max == min)
          scaleY = 1/1.70;
      else
          scaleY = 1/((max-min)/1.70);
      
      translateY = range/2;


  }

  glScalef(scaleX,scaleY,0);
  glTranslatef(-translateX,-translateY,0);


  double timeRange = 1 / scaleX ;
  double valueRange = 1 / scaleY ;

  double timeEnd = translateX + timeRange ;
  double timeBegin = translateX - timeRange ;

  double valueEnd = translateY + valueRange;
  double valueBegin = translateY  - valueRange ;



  drawGrid(timeEnd,timeBegin,valueEnd,valueBegin);


  for (double counter = 0 ; counter < lineArray.getNumElements() ; ++counter )
  {
      lineArray.getElement(counter)->setTimeRange(timeBegin-1,timeEnd+1);
      if(lineArray.getElement(counter)->draw() )
          lineArray.removeElement(counter);
  }

  glPopMatrix();

}

//==============================================================================
// GlPlotWindow::save
//==============================================================================
void GlPlotWindow::save(pugi::xml_node pLineNodes)
{
    for (int i = 0 ; i < lineArray.getNumElements() ; ++i )
    {
        pugi::xml_node line = pLineNodes.append_child("Line");
        line.append_attribute("LogVariable") = lineArray.getElement(i)->getLogVariableGUI()->getName();
        line.append_attribute("Index") = lineArray.getElement(i)->getLogIndex();
        line.append_attribute("R") = lineArray.getElement(i)->getR();
        line.append_attribute("G") = lineArray.getElement(i)->getG();
        line.append_attribute("B") = lineArray.getElement(i)->getB();
     }
    
    return ;
}



//==============================================================================
// GlPlotWindow::printLinesToMatlabFile
//==============================================================================
void GlPlotWindow::printLinesToMatlabFile( ofstream &pOutputFile )
{
    for (int i = 0 ; i < lineArray.getNumElements() ; ++i )
        lineArray.getElement(i)->printLineToMatlabFile(pOutputFile);
}
