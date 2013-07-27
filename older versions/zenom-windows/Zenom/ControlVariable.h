/*
 * ControlVariable.h
 *
 *  Created on: Apr 9, 2012
 *      Author: root
 */

#ifndef CONTROLVARIABLE_H_
#define CONTROLVARIABLE_H_

#include "Variable.h"
#include <string.h>

class ControlVariable: public Variable
{
public:
	ControlVariable(double* pAddr, const std::string& pName, int pRow = 1, int pCol = 1, const std::string& pDesc = "");
	virtual ~ControlVariable();

	void setData( double* pData );

	double* data() { return mVariableAddr; }
};

#endif /* CONTROLVARIABLE_H_ */
