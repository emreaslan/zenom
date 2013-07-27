//==============================================================================
// CantrolVariable.cpp - ControlVariable implementasyonu
//
// Author        : 
// Version       : 
// Compatibility : GCC
//==============================================================================

#include "ControlVariable.h"

//==============================================================================
// ControlVariable::ControlVariable
//==============================================================================
ControlVariable::ControlVariable(double* addr,const char* name, const char* desc , int nRow , int nCol)
: Variable( addr, name , desc , nRow , nCol){}

//==============================================================================
// ControlVariable::ControlVariable
//==============================================================================
ControlVariable::ControlVariable(double& addr,const char* name, const char* desc)
: Variable( &addr, name, desc){}

//==============================================================================
// ControlVariable::setSourceHeapAddress
//==============================================================================
void ControlVariable::setSourceHeapAddress(double* sourceAddr)
{ 
    sourceHeapAddress=sourceAddr;
}

//==============================================================================
// ControlVariable::copyToHeap
//==============================================================================
void ControlVariable::copyToHeap()
{
    double* controlAddr = address;
    double* srcHeapAddr = sourceHeapAddress;
    
    // source heapdeki veri, degisken heap alanina yazilir.
    for(int i = 0; i < size; ++i)
    {
        *srcHeapAddr = *controlAddr;
        ++controlAddr;
        ++srcHeapAddr;
    }
}
