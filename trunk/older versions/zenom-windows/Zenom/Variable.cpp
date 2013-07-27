/*
 * Variable.cpp
 *
 *  Created on: Mar 26, 2012
 *      Author: root
 */

#include "Variable.h"

//==============================================================================
// Variable::Variable
//==============================================================================
Variable::Variable(double* pAddr, const std::string& pName, const std::string& pDesc , int pRow , int pCol)
{
    mVariableAddr = pAddr;
    mName = pName;
    mDescription = pDesc;
    mRow = pRow;
    mCol = pCol;
}

//==============================================================================
// Variable::~Variable
//==============================================================================
Variable::~Variable()
{

}

