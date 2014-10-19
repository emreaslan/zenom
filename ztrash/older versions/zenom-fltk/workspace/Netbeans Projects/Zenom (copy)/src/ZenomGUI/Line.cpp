#include "Line.h"

using namespace std;

//==============================================================================
// Line::Line
//==============================================================================
Line::Line(LogVariableGUI* logVar , int index ) : LineBase (logVar)
{
    logIndex = index;
}

//==============================================================================
// Line::draw()
//==============================================================================
int Line::draw()
{
    if( logVariableGUI->isBind() )
    {
      //glEnable( GL_LineBase_SMOOTH );
      //glHint(GL_LineBase_SMOOTH_HINT, GL_NICEST);
      // Enable Blending
      //glEnable(GL_BLEND);
      // Specifies pixel arithmetic
      //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

      int beginIndex,endIndex;
      findHeapIndex(rangeBegin,rangeEnd,beginIndex,endIndex);

      int diff = endIndex - beginIndex;

      if (diff <= 0)
          return 0;


      if( logVariableGUI->getMouseOver(logIndex) )
          glLineWidth(4);
      
      glColor3f(r,g,b);
      glBegin(GL_LINES);

      valueMaxY = -1000000000;
      valueMinY =  1000000000;
      valueMaxX = -1000000000;
      valueMinX =  1000000000;


      diff = (diff / (logVariableGUI->getSize()+1) / 5000) + 1 ;

      double firstY = logVariableGUI->getHeapElement(beginIndex + logIndex);


      if( isnan(firstY) || isinf(firstY) )
      {
          /*
          if( fltk::ask("NaN or Inf value detected\nDo you want to stop plotting") )
              this->guiComQueueSender->sendStopMessage();
          else
              return 1;
           * */
      }

      for (int counter = beginIndex ; counter <= ( endIndex - ( (logVariableGUI->getSize()+1) * diff) ) ; counter += ( (logVariableGUI->getSize()+1) * diff) )
      {
          double firstY = logVariableGUI->getHeapElement(counter + logIndex);
          double firstX = ( logVariableGUI->getHeapElement(counter + logVariableGUI->getSize() ) ) ;

          if( firstY > UpperBound || firstY < LowerBound )
              continue;

          glVertex2f( firstX, firstY );



          double secondY = logVariableGUI->getHeapElement(counter + logIndex + ( (logVariableGUI->getSize()+1) * diff) );
          double secondX = logVariableGUI->getHeapElement(counter + logVariableGUI->getSize() + ( (logVariableGUI->getSize()+1) * diff) ) ;

          /*if( isnan(secondY) || isinf(secondY) )
          {
              //this->guiComQueueSender->sendPauseMessage();
              if( fltk::ask("NaN or Inf value detected\nDo you want to stop plotting") )
              {
                  //this->guiComQueueSender->sendStopMessage();
                  return 0;
              }
              else
              {
                  //this->guiComQueueSender->sendStartMessage();
                  return 1;
              }

          }*/

          if( secondY > UpperBound || secondY < LowerBound )
              continue;

          glVertex2f( secondX ,secondY);

          if( firstY > valueMaxY )
              valueMaxY = firstY;
          if( secondY > valueMaxY )
              valueMaxY = secondY;

          if( firstY < valueMinY )
              valueMinY = firstY;
          if( secondY < valueMinY )
              valueMinY = secondY;

      }
      glEnd();

      if( logVariableGUI->getMouseOver(logIndex) )
            glLineWidth(1);


      //glDisable(GL_LineBase_SMOOTH); // Smooth out LineBases
      //glDisable(GL_BLEND);
    }

    return 0;
}

void Line::printLineToMatlabFile(ofstream &pOutputFile)
{
    int lineDataCount = 0;
    pOutputFile << "%" << logVariableGUI->getName() << " - Time data array - Index value : " << logIndex << endl;
    pOutputFile << logVariableGUI->getName() << "I" << logIndex << " =[" ;

    for (int counter = 1; counter <= logVariableGUI->getHeapElement(0); counter += (logVariableGUI->getSize() + 1) )
    {
  
        double y = logVariableGUI->getHeapElement(counter + logIndex);
        double x = logVariableGUI->getHeapElement(counter + logVariableGUI->getSize() ) ;
        double index  = logVariableGUI->getHeapElement(0);

        if( y > UpperBound || y < LowerBound )
            continue;

        pOutputFile << y << "," << x << ";";

        ++lineDataCount;
        if ( (lineDataCount % 10) == 0 )
            pOutputFile << endl;
    }
    pOutputFile << "]" << endl << endl << endl;

    return ;
}
