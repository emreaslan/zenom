#ifndef DATAREPOSITORY_H
#define DATAREPOSITORY_H

#include <vector>
#include "LogVariable.h"
#include "ControlVariable.h"
#include "utilities/projectfileinfo.h"


typedef std::vector<LogVariable*> LogVariableList;
typedef std::vector<ControlVariable*> ControlVariableList;

class DataRepository
{
public:
	static DataRepository* instance();

	DataRepository();

	~DataRepository();

	LogVariable* findLogVariable(const QString& pName);

	LogVariableList mLogVariableList;
	ControlVariableList mControlVariableList;

	// Project Info
	ProjectFileInfo mProjectFileInfo;

	void tick()
	{
		for ( int i = 0; i < mLogVariableList.size(); ++i )
		{
			mLogVariableList[i]->random();
		}
	}

private:
	static DataRepository* mInstance;
	

};

#endif // DATAREPOSITORY_H
