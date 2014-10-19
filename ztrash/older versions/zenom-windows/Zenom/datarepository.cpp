#include "datarepository.h"

DataRepository* DataRepository::mInstance = NULL;


DataRepository* DataRepository::instance()
{
	if ( !DataRepository::mInstance )
	{
		DataRepository::mInstance = new DataRepository();
	}

	return DataRepository::mInstance;
}


DataRepository::DataRepository()
{
	mLogVariableList.push_back( new LogVariable(NULL, "a1") );
	mLogVariableList.push_back( new LogVariable(NULL, "a2", 2, 1) );
	mLogVariableList.push_back( new LogVariable(NULL, "a4", 2, 2) );
	mLogVariableList.push_back( new LogVariable(NULL, "a4", 1, 4) );
	mLogVariableList.push_back( new LogVariable(NULL, "a9", 3, 3) );

	mControlVariableList.push_back( new ControlVariable(new double[1], "a1") );
	mControlVariableList.push_back( new ControlVariable(new double[2], "a2", 2, 1) );
	mControlVariableList.push_back( new ControlVariable(new double[4], "a4", 2, 2) );
	mControlVariableList.push_back( new ControlVariable(new double[4], "a4", 1, 4) );
	double* temp = new double[9];
	temp[0] = 1;
	mControlVariableList.push_back( new ControlVariable(temp, "a9", 3, 3) );
}

DataRepository::~DataRepository()
{

}

LogVariable* DataRepository::findLogVariable( const QString& pName )
{
	for ( int i = 0; i < mLogVariableList.size(); ++i )
	{
		if ( mLogVariableList[i]->name() == pName.toStdString() )
		{
			return mLogVariableList[i];
		}
	}

	return NULL;
}
