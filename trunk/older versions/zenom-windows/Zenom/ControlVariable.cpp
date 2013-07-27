/*
 * ControlVariable.cpp
 *
 *  Created on: Apr 9, 2012
 *      Author: root
 */

#include "ControlVariable.h"

ControlVariable::ControlVariable(double* pAddr, const std::string& pName, int pRow, int pCol, const std::string& pDesc)
: Variable(pAddr, pName, pDesc, pRow, pCol)
{
	// TODO Auto-generated constructor stub

}

ControlVariable::~ControlVariable()
{
	// TODO Auto-generated destructor stub
}

void ControlVariable::setData( double* pData )
{
	memcpy( mVariableAddr, pData, sizeof(double) * size() );	// copy variable
}
