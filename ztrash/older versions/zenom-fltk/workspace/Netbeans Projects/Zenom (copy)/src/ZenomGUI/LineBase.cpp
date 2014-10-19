#include "LineBase.h"


//==============================================================================
// CantrolVariable.cpp - ControlVariable implementasyonu
//
// Author        :
// Version       :
// Compatibility : GCC
//==============================================================================

#include <fltk/ask.h>

#include "LineBase.h"

//==============================================================================
// LineBase::LineBase
//==============================================================================
LineBase::LineBase(LogVariableGUI* logVar )
{
    UpperBound = 1000000000;
    LowerBound = -UpperBound;
    logVariableGUI = logVar;

}


//==============================================================================
// LineBase::setColor
//==============================================================================
void LineBase::setColor(int R, int G, int B)
{
    r = (float)R / 255; g = (float)G / 255; b = (float) B /255 ;
}

//==============================================================================
// LineBase::setTimeRange
//==============================================================================
void LineBase::setTimeRange(double begin, double end)
{
    rangeBegin = begin;
    rangeEnd = end;
}

//==============================================================================
// LineBase::findHeapIndex
//==============================================================================
int LineBase::findHeapIndex ( double timeBegin, double timeEnd,int &rangeBegin , int& rangeEnd )
{
    int heapEndIndex = logVariableGUI->getHeapElement(0);

    if((int)timeBegin <= 0 )
        timeBegin = 0;

    rangeBegin = (int)timeBegin * logVariableGUI->getFrequency() * (logVariableGUI->getSize()+1)  + 1 ;

    if(logVariableGUI->getHeapElement( heapEndIndex + logVariableGUI->getSize()) < timeEnd )
        rangeEnd = heapEndIndex - (logVariableGUI->getSize()+1);
    else
        rangeEnd = (int)timeEnd * (logVariableGUI->getFrequency()-1) * (logVariableGUI->getSize()+1) + 1 ;

    /*if(rangeBegin < 1)
        rangeBegin = 1;
    if(rangeEnd > heapEndIndex)
        rangeEnd = heapEndIndex - (LogVariableGUI->getSize()+1);*/
    return 0;
}


