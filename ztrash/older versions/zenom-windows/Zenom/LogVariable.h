/*
 * LogVariable.h
 *
 *  Created on: Mar 26, 2012
 *      Author: Cuneyt AY
 */

#ifndef LOGVARIABLE_H_
#define LOGVARIABLE_H_

#include "Variable.h"
#include "HeapXn.h"
//#include <rtdk.h>

class LogVariable: public Variable
{
public:
	LogVariable(double* pAddr, const std::string& pName, int pRow = 1, int pCol = 1, const std::string& pDesc = "");

	virtual ~LogVariable();

    /**
     * Log degiskeni frekansini getirir.
     * @return Degisken frekansi
     */
    inline double frequency(){ return mFrequency; }

    /**
     * Log degiskeni frekansini gunceller.
     * @param Logfrequency  Yeni frekans
     */
    void setFrequency(double pFrequency) { mFrequency = pFrequency; }

    /**
     * Log degiskeninin devam edecegi sureyi getirir.
     * @return Degisken süreci
     */
    inline double duration(){ return mDuration; }

    /**
     * Log degiskeninin devam edecegi sureyi gunceller.
     * @param logDuration  Yeni sürec
     */
    void setDuration(double pDuration) { mDuration = pDuration; }

    /**
     * Log degiskenin baslayacagi sureyi getirir.
     * @return Degiskenin baslangic zamani
     */
    inline double startTime(){ return mStartTime; }

    /**
     * Log degiskenin baslayacagi sureyi gunceller.
     * @param logStartTime  Yeni baslangic zamani
     */
    void setStartTime(double pStartTime) { mStartTime = pStartTime; }

    // Write Data
    void createHeap();

    void deleteHeap();

    void insertToHeap(double pTimeStamp);

    // Read Data
    void bindHeap();

    void unbindHeap();

    int heapSize();

    double* heapElement(int pIndex);

    double heapElement(int pIndex, int pVariableIndex);

    double heapElement(int pIndex, int pRow, int pCol);

    double* lastHeapElement();

    double lastHeapElement(int pVariableIndex);

    double lastHeapElement(int pRow, int pCol);

    void dumpHeap()
    {
    	int heapSize = ((size() + 1) * frequency() * duration() + 1);
    	printf("Index : %f\n", mHeapSizeAddr[0]);
		for (int i = 1; i < heapSize; ++i)
		{
			printf("%f ", mHeapSizeAddr[i]);
		}

		printf("\n Last Elements:");
		double* temp = lastHeapElement();
		for (int i = 0; i < size(); ++i)
		{
			printf("%f ", temp[i]);
		}

		printf("\n First Elements:");
		temp = heapElement(0);
		for (int i = 0; i < size(); ++i)
		{
			printf("%f ", temp[i]);
		}
		printf("\n");
    }

	void random()
	{
		for (int i = 0; i < size(); ++i)
		{
			if ( mHeapAddr[i] == 150 )
			{
				counter = -5;
			}
			else if ( mHeapAddr[i] == -150 )
			{
				counter = 5;
			}

			mHeapAddr[i] += counter;
		}		
	}
	double counter;

protected:

    /** Log degiskeni frekansini */
    double mFrequency;

    /** Log degiskeni devam etme süresi */
    double mDuration;

    /** Log degiskeni baslangic zamani */
    double mStartTime;

    HeapXn mHeap;
    double* mHeapSizeAddr;
    double* mHeapAddr;
};

#endif /* LOGVARIABLE_H_ */
