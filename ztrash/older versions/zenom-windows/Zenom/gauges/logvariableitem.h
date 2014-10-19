#ifndef LOGVARIABLEITEM_H
#define LOGVARIABLEITEM_H

#include "logvariable.h"

struct LogVariableItem
{
public:
	LogVariableItem(LogVariable* pLogVariable = NULL, int pRow = -1, int pCol = -1);

	~LogVariableItem();

	LogVariable* mLogVariable;
	int mRow;
	int mCol;
};

#endif // LOGVARIABLEITEM_H
