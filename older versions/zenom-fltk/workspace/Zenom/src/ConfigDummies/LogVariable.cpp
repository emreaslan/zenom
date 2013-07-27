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