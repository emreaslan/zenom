/*
 * LogVariable.cpp
 *
 *  Created on: Mar 26, 2012
 *      Author: root
 */

#include "LogVariable.h"

LogVariable::LogVariable(double* pAddr, const std::string& pName, int pRow, int pCol, const std::string& pDesc)
 : Variable(pAddr, pName, pDesc, pRow, pCol)
{
    setDuration( 10 );
    setFrequency( 1 );
    setStartTime( 0 );

	counter = 5;
	createHeap();
}

LogVariable::~LogVariable()
{
	// TODO Auto-generated destructor stub
}

void LogVariable::createHeap()
{
	// (size + Time Stamp) * frequency * duration + index
	int heapSize = ((size() + 1) * frequency() * duration() + 1) * sizeof(double);

	/*
	mHeap.create( mName, heapSize );
	mHeapSizeAddr = (double*)mHeap.alloc(heapSize);

	// Heap was created successfully.
	mHeapSizeAddr[0] = 0;
	mHeapAddr = mHeapSizeAddr + 1;
	*/
	
	mHeapSizeAddr = new double[heapSize];

	// Heap was created successfully.
	mHeapSizeAddr[0] = 1;
	mHeapAddr = mHeapSizeAddr + 1;

	for (int i = 0; i < size(); ++i)
	{
		mHeapAddr[i] = 0;
	}
	counter = 5;
}

void LogVariable::deleteHeap()
{
	mHeap.free( mHeapSizeAddr );
	mHeap.deleteHeap();
}

void LogVariable::insertToHeap(double pTimeStamp)
{
	// TODO frequency log
	// pTimestamp <= (startTime() + duration()) olmali mi ?
	if( startTime() <= pTimeStamp && pTimeStamp < (startTime() + duration()) )
	{
		printf("inserted %f \n", pTimeStamp);
		size_t num = size();
		memcpy( mHeapAddr, mVariableAddr, sizeof(double) * num );	// copy variable
		mHeapAddr[num] = pTimeStamp;			// copy time stamp

		mHeapAddr += (num + 1);	// set next address
		++(*mHeapSizeAddr);	// Increase index
	}
}

void LogVariable::bindHeap()
{
    // first address is size
	mHeap.bind( mName );
	mHeapSizeAddr = (double*)mHeap.alloc( 0 );
	mHeapAddr = mHeapSizeAddr + 1;
}

void LogVariable::unbindHeap()
{
	mHeap.unbind();
}

int LogVariable::heapSize()
{
	return static_cast<int>( mHeapSizeAddr[0] );
}

double* LogVariable::heapElement(int pIndex)
{
	return &(mHeapSizeAddr[ pIndex * (size() + 1) + 1 ]);
}

double LogVariable::heapElement(int pIndex, int pVariableIndex)
{
	return heapElement(pIndex)[pVariableIndex];
}

double LogVariable::heapElement(int pIndex, int pRow, int pCol)
{
	return heapElement(pIndex, pRow * col() + pCol);
}

double* LogVariable::lastHeapElement()
{
	int index = heapSize() - 1;	// Last element index
	return heapElement(index);
}

double LogVariable::lastHeapElement(int pVariableIndex)
{
	return lastHeapElement()[pVariableIndex];
}

double LogVariable::lastHeapElement(int pRow, int pCol)
{
	return lastHeapElement(pRow * col() + pCol);
}





