#include "LineXY.h"

//==============================================================================
// LineXY::LineXY
//==============================================================================
LineXY::LineXY(LogVariableGUI* logVar  ) : LineBase (logVar)
{
    logIndex = 0;
    logIndexXY = 1;

}

//==============================================================================
// Line::draw()
//==============================================================================
int LineXY::draw()
{
    if( logVariableGUI->isBind() )
    {

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

         diff = (diff / (logVariableGUI->getSize()+1) / 1000) + 1 ;
         for (int counter = beginIndex ; counter < ( endIndex - ( (logVariableGUI->getSize()+1) * diff) ) ; counter += ( (logVariableGUI->getSize()+1) * diff) )
         {
             double firstY = logVariableGUI->getHeapElement(counter + logIndex);
             double firstX = logVariableGUI->getHeapElement(counter + logIndexXY );
             glVertex3f( firstX, firstY,0 );

             double secondY = logVariableGUI->getHeapElement(counter + logIndex + ( (logVariableGUI->getSize()+1) * diff) );
             double secondX = logVariableGUI->getHeapElement(counter + logIndexXY + ( (logVariableGUI->getSize()+1) * diff) );

             glVertex3f( secondX ,secondY,0);

            
             if( firstY > valueMaxY )
                 valueMaxY = firstY;
             if( firstY < valueMinY )
                 valueMinY = firstY;

             if( secondY > valueMaxY )
                 valueMaxY = secondY;
             if( secondY < valueMinY )
                 valueMinY = secondY;

             if( firstX > valueMaxX )
                 valueMaxX = firstX;
             if( firstX < valueMinX )
                 valueMinY = firstY;

             if( secondX > valueMaxX )
                 valueMaxX = secondX;
             if( secondX < valueMinX )
                 valueMinX = secondX;
         }

         glEnd();

         if( logVariableGUI->getMouseOver(logIndex) )
             glLineWidth(1);

    }

    return 0;
}

void LineXY::printLineToMatlabFile(ofstream &pOutputFile)
{
    int lineDataCount = 0;
    pOutputFile << "%" << logVariableGUI->getName() << " X - Y - Time data array" << endl;
    pOutputFile << logVariableGUI->getName() << "I" << logIndex << " =[" ;

    for (int counter = 1; counter <= logVariableGUI->getHeapElement(0)  ; counter += (logVariableGUI->getSize() + 1) )
    {
        double y = logVariableGUI->getHeapElement(counter  + logIndex);
        double x = logVariableGUI->getHeapElement(counter + logIndexXY);
        double t = logVariableGUI->getHeapElement(counter + logVariableGUI->getSize() ) ;

        if( y > UpperBound || y < LowerBound  || x > UpperBound || x < LowerBound)
            continue;

        pOutputFile << y << "," << x << "," << t <<";";

        ++lineDataCount;
        if ( (lineDataCount % 10) == 0 )
            pOutputFile << endl;
    }
    pOutputFile << "]" << endl << endl << endl;

    return ;
}

