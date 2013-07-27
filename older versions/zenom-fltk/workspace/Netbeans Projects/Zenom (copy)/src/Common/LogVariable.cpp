//==============================================================================
// LogVariable.cpp - LogVariable implementasyonu
//
// Author        :
// Version       :
// Compatibility : GCC
//==============================================================================


#include "LogVariable.h"

//==============================================================================
// LogVariable::LogVariable
//==============================================================================
LogVariable::LogVariable(double* addr,const  char* name, const char* desc , int nRow , int nCol )
: LogVariableBase( addr, name, desc , nRow , nCol)
{
    isInt = false;
    logPeriodCounter = 0;

}


//==============================================================================
// LogVariable::LogVariable
//==============================================================================
LogVariable::LogVariable(int* addr,const  char* name, const char* desc , int nRow , int nCol )
: LogVariableBase( addr, name, desc, nRow ,nCol )
{
    isInt = true;
    logPeriodCounter = 0;

}

//==============================================================================
// LogVariable::LogVariable
//==============================================================================
LogVariable::LogVariable(double& addr,const char* name, const char* desc, int nRow , int nCol )
: LogVariableBase( &addr, name, desc , nRow , nCol)
{
    isInt = false;
    logPeriodCounter = 0;
}

//==============================================================================
// LogVariable::~LogVariable
//==============================================================================
LogVariable::~LogVariable()
{

}


//==============================================================================
// LogVariable::deleteHeap
//==============================================================================
int LogVariable::deleteHeap()
{
    logHeap->deleteHeap();
    return logHeap->getErrnoError();
}

#include <iostream>
using namespace std;
//==============================================================================
// LogVariableBase::copyFromSourceHeap
//==============================================================================
void LogVariable::copyFromSourceHeap()
{
    //cout << name <<" S: " << startTime << " D: " << duration << " T: "<<*timeHeapAddress << endl;
    
    double time = *timeHeapAddress;
    if( startTime <= time)
        if( (startTime + duration) > time )
    {
        
        if( logPeriodCounter == logPeriod )
        {

            double* beginSource = sourceHeapAddress;

            // source heapdeki veri, degisken heap alanina yazilir.
            for(int i = 0; i < size; ++i)
            {
                *logHeapIndex = *beginSource;
                //rt_printf("copyFrom sourceHeap %s %p\n",this->name, logHeapBeginAddr);
                ++beginSource;
                ++logHeapIndex;
            }

            // Verinin islendigi zaman bilgisi heape yazilir
            *logHeapIndex = *timeHeapAddress;
            ++logHeapIndex;

            // Heapdeki eleman sayaci olan ilk eleman arttirilir.
            *logHeapBeginAddr += size + 1;

            logPeriodCounter = 0;
        }
	++logPeriodCounter;
    }

    
}



//==============================================================================
// LogVariableBase::createHeap
//==============================================================================
int LogVariable::createHeap(int heapsize)
{
    // ilk adres heapde bulunan eleman sayisidir
    logHeapBeginAddr = (double*)logHeap->create(name,heapsize);
    
    int err = logHeap->getErrnoError();
    if(err)
        return err;
    logHeapIndex = logHeapBeginAddr + 1;
    (*logHeapBeginAddr) = -size;

    return 0;
}
