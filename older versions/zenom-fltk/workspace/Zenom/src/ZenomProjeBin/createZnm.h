#ifndef CREATE_ZNM_H
#define CREATE_ZNM_H

#include <iostream>
#include <cstring>
#include <cstdlib>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <fcntl.h>
#include <fstream>
#include <unistd.h>

using namespace std;

class CreateZnm{

public:

	CreateZnm( int argc, char *argv[] );
	~CreateZnm();
	void start();
	
private:

	int checkTypo( int argc, char *argv[] );
	int createFolder();
	int createCpp();
	int createMakefile();
	int init( char *name );
	
	char *eventName;
	char *path;
	char *folderPath;
	const static char tirnak = '"';
	char *cppFile;
	char *className;
	char *oFile;
	char *oXmlFile;
	char *makeFile;
	char *objectName;
	char *xmlFile; 
	
	char *makeMdfFile;
	char *cppMdfFile;
	char *cfgMdfFile;
	
	static const int lineLength = 1024;
		
};

#endif
