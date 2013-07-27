//==============================================================================
// LogVariableBase.cpp - LogVariable implementasyonu
//
// Author        :
// Version       :
// Compatibility : GCC
//==============================================================================

#include "LogVariableBase.h"



//==============================================================================
// LogVariableBase::LogVariableBase
//==============================================================================
LogVariableBase::LogVariableBase(double* addr,const  char* name, const char* desc , int nRow , int nCol )
: Variable( addr, name, desc , nRow , nCol)
{
    setDuration( 100 );
    setFrequency( 1000 );
    setStartTime( 0 );
    logHeap = new HeapXn;
}


//==============================================================================
// LogVariable::LogVariable
//==============================================================================
LogVariableBase::LogVariableBase(int* addr,const  char* name, const char* desc , int nRow , int nCol )
: Variable( addr, name, desc, nRow ,nCol )
{
    setDuration( 100 );
    setFrequency( 1000 );
    setStartTime( 0 );
    logHeap = new HeapXn;
}

//==============================================================================
// LogVariable::LogVariable
//==============================================================================
LogVariableBase::LogVariableBase(double& addr,const char* name, const char* desc, int nRow , int nCol )
: Variable( &addr, name, desc , nRow , nCol)
{
    setDuration( 100 );
    setFrequency( 1000 );
    setStartTime( 0 );
    logHeap = new HeapXn;
}

//==============================================================================
// LogVariable::~LogVariable
//==============================================================================
LogVariableBase::~LogVariableBase()
{
    delete logHeap;
}


//==============================================================================
// LogVariableBase::setFrequency
//==============================================================================
void LogVariableBase::setFrequency(double Logfrequency)
{
    if( Logfrequency > 0 )
        frequency = Logfrequency;
}

//==============================================================================
// LogVariableBase::setDuration
//==============================================================================
void LogVariableBase::setDuration(double logDuration)
{
    if( logDuration >= 0 )
        duration = logDuration;
}

//==============================================================================
// LogVariableBase::setStartTime
//==============================================================================
void LogVariableBase::setStartTime(double logStartTime)
{
    if( logStartTime >= 0 )
        startTime = logStartTime;
}

//==============================================================================
// LogVariableBase::setSourceAddress
//==============================================================================
void LogVariableBase::setSourceAddress(double* sourceAddress)
{
    sourceHeapAddress = sourceAddress;
}

//==============================================================================
// LogVariableBase::setTimeAddress
//==============================================================================
void LogVariableBase::setTimeAddress(double* timeAddress)
{
    timeHeapAddress = timeAddress;
}


//==============================================================================
// LogVariableBase::getLastHeapElement
//==============================================================================
double LogVariableBase::getLastHeapElement(int row, int column)
{
    int lastIndex = logHeapBeginAddr[0];

    return logHeapBeginAddr[ lastIndex + row * column + column ];
}

//==============================================================================
// LogVariableBase::getLastHeapElement
//==============================================================================
double LogVariableBase::getLastHeapElement(int index)
{
    int lastIndex = logHeapBeginAddr[0];

    return logHeapBeginAddr[ lastIndex + index ];
}



