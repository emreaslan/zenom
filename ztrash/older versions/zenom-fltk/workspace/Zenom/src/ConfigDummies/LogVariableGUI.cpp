//==============================================================================
// LogVariable.cpp - LogVariable implementasyonu
//
// Author        :
// Version       :
// Compatibility : GCC
//==============================================================================


#include "LogVariableGUI.h"
#include <iostream>
using namespace std;


//==============================================================================
// LogVariable::LogVariable
//==============================================================================
LogVariableGUI::LogVariableGUI(double* addr,const  char* name, const char* desc , int nRow , int nCol )
: LogVariableBase( addr, name, desc , nRow , nCol)
{
    bind = false;

    char buffer[255];

    mouseOver= new bool[nRow*nCol];
    subNames = new char*[nRow*nCol];
    for(int row = 0; row < nRow; ++row)
    {
        for(int col = 0; col < nCol; ++col)
        {
            snprintf(buffer,255,"%s(%d)(%d)",name,row,col);
            subNames[row*nCol+col] = new char[strlen(buffer)];
            strcpy(subNames[row*nCol+col],buffer);           
            
            mouseOver[row*nCol+col] = false;
        }
    }
}


//==============================================================================
// LogVariable::LogVariable
//==============================================================================
LogVariableGUI::LogVariableGUI(int* addr,const  char* name, const char* desc , int nRow , int nCol )
: LogVariableBase( addr, name, desc, nRow ,nCol )
{
    bind = false;
    char buffer[255];

    mouseOver= new bool[nRow*nCol];
    subNames = new char*[nRow*nCol];
    for(int row = 0; row < nRow; ++row)
    {
        for(int col = 0; col < nCol; ++col)
        {
            snprintf(buffer,255,"%s(%d)(%d)",name,row,col);
            subNames[row*nCol+col] = new char[strlen(buffer)];
            strcpy(subNames[row*nCol+col],buffer);           
            
            mouseOver[row*nCol+col] = false;
        }
    }
}

//==============================================================================
// LogVariable::LogVariable
//==============================================================================
LogVariableGUI::LogVariableGUI(double& addr,const char* name, const char* desc, int nRow , int nCol )
: LogVariableBase( &addr, name, desc , nRow , nCol)
{
    bind = false;
}

//==============================================================================
// LogVariable::~LogVariable
//==============================================================================
LogVariableGUI::~LogVariableGUI()
{
    for(int i = 0; i < rows*cols; ++i)
        delete subNames[i];
    delete subNames;
}



