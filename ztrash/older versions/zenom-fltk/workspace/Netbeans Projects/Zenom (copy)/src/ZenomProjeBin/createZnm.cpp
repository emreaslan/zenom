#include "createZnm.h"

#define XENOM_FILE "<XENOM_FILE>"
#define GENERAL "<GENERAL>"
#define LOG_VARIABLES "<LOG_VARIABLES>"
#define CONTROL_VARIABLES "<CONTROL_VARIABLES>"
#define GUI "<GUI>"

CreateZnm::CreateZnm( int argc, char *argv[] ){

	eventName = NULL;
	
	char *temp = new char[1024];

	temp = getcwd( temp, 1024 );
	
	if( temp != NULL ){
		
		path = new char[strlen( temp ) + 1];
		strcpy( path, temp );
		
		if( checkTypo( argc, argv ) == 0)
			init( argv[1] );
		
	}
	else
		perror("Error:");
}

CreateZnm::~CreateZnm(){

	if( eventName != NULL )
		delete eventName;

}

void CreateZnm::start(){

	if( eventName != NULL ){
	
		if( createFolder() != 0 )
			return;
	
		if( createCfg() != 0 )
			return;
	
		if( createCpp() != 0 )
			return;
	
		if( createMakefile() != 0 )
			return;
	
		//cout << "success" << endl;
		
	}

}

int CreateZnm::init( char *name ){

	int len = strlen( name ) + 1;
	
	eventName = new char[len];
	strcpy( eventName, name );
	
	cppFile = new char[len + 4];
	snprintf( cppFile, len + 4, "%s.cpp", eventName );
	
	className = new char[len];
	strcpy( className, eventName );
	className[0] = toupper( className[0] );
	
	oFile = new char[len + 2];
	snprintf( oFile, len + 2, "%s.o", eventName );
	
	makeFile = new char[len + 4];
	snprintf( makeFile, len + 4, "%s.znm", eventName );
	
	objectName = new char[len];
	strcpy( objectName, className );
	objectName[0] = tolower( className[0] );
	
	makeMdfFile = new char[44];
	snprintf(makeMdfFile, 44, "/usr/local/zenom/bin/modification/make.mdf" );
	
	cppMdfFile = new char[42];
	snprintf( cppMdfFile, 42, "/usr/local/zenom/bin/modification/cpp.mdf" );
	
	cfgMdfFile = new char[42];
	snprintf( cfgMdfFile, 42, "/usr/local/zenom/bin/modification/cfg.mdf" );

}

int CreateZnm::createFolder(){
	
	int len = strlen( path ) + strlen(eventName) + 2;
	folderPath = new char[len];
	
	if( folderPath == NULL ){
	
		cout << "Error: " << strerror(12) << endl;
		return 12;
		
	}
	
	snprintf( folderPath, len, "%s/%s", path, eventName );
	
	if( mkdir( folderPath, S_IRWXU|S_IRWXG|S_IRWXO  ) != 0 ){
	
		perror("Folder can not be created");
		return 1;
	
	}
	
	return 0;

}

int CreateZnm::createCfg(){
	
	int len = strlen(folderPath) + strlen(eventName) + 6;
	
	char *configPath = new char[len];
	
	if( configPath == NULL ){
	
		cout << "Error: " << strerror(12) << endl;
		return 1;
		
	}
	
	snprintf(configPath, len, "%s/%s.cfg", folderPath, eventName );
	
	FILE *cfgFPtr;
	
	cfgFPtr = fopen( configPath, "w" );
	
	if( cfgFPtr == NULL ){
	
		cout << eventName << ".cfg can not be created" << endl;
		return 1;
			
	}
	
	ifstream cfgMdfFPtr;
	
	cfgMdfFPtr.open( cfgMdfFile, ios::in );
	
	if( ! cfgMdfFPtr.is_open()  ){
	
		fwrite( XENOM_FILE, 12, 1, cfgFPtr );
		fwrite( "\n\n", 2, 1, cfgFPtr );
		fwrite( GENERAL, 9, 1, cfgFPtr );
		fwrite( "\n" , 1, 1, cfgFPtr );
		fwrite( "Frequency 1000\n", 15, 1, cfgFPtr );
		fwrite( "Duration 200\n\n", 14, 1, cfgFPtr );
		fwrite( LOG_VARIABLES, 15, 1, cfgFPtr );
		fwrite( "\n" , 1, 1, cfgFPtr );
		fwrite( "\n\n", 2, 1, cfgFPtr );
		fwrite( CONTROL_VARIABLES, 19, 1, cfgFPtr );
		fwrite( "\n" , 1, 1, cfgFPtr );
		fwrite( "\n\n", 2, 1, cfgFPtr );
		fwrite( GUI, 5, 1, cfgFPtr );
		
	}
	else{
	
		char textLine[lineLength];
		while( ! cfgMdfFPtr.eof() ){
			
			cfgMdfFPtr.getline( textLine, lineLength );
			fprintf( cfgFPtr, "%s\n", textLine );
		
		}
	
	}
	
	fclose( cfgFPtr );

	return 0;

}

int CreateZnm::createCpp(){
	
	int len = strlen(folderPath) + strlen(eventName) + 6;
	
	char *cppPath = new char[len];
	
	if( cppPath == NULL ){
	
		cout << "Error: " << strerror(12) << endl;
		return 1;
		
	}
	
	snprintf(cppPath, len, "%s/%s.cpp", folderPath, eventName );
	
	FILE *cppFPtr;
	
	cppFPtr = fopen( cppPath, "w" );
	
	if( cppFPtr == NULL ){
	
		cout << eventName << ".cpp can not be created" << endl;
		return 1;
			
	}
	
	ifstream cppMdfFPtr;
	
	cppMdfFPtr.open( cppMdfFile, ios::in );
	
	if( cppMdfFPtr.is_open()  ){
	
		char textLine[lineLength];
		
		cppMdfFPtr.getline( textLine, lineLength );
		
		while( strcmp( textLine, "MAIN" ) != 0 ){
			
			if( strcmp( textLine, "UST_YORUM" ) == 0 ){
				
				fprintf( cppFPtr, "// ============================================================================\n"
                                                  "//  Zenom - Gercek zamanli Hardware-In-the-Loop Simulasyon\n"
				                  "//  \n"
				                  "// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"
				                  "//  Control Program : %s\n"
				                  "//  Description     : \n", cppFile );
				
                                // Modifiye dosyasindaki UST_YORUM kismi tamamen alinir
				cppMdfFPtr.getline( textLine, lineLength );
				while( strcmp( textLine, "INITIALIZE" ) != 0 ){
					
					fprintf( cppFPtr, "//  %s\n", textLine );
					cppMdfFPtr.getline( textLine, lineLength );
                                }
				
				fprintf( cppFPtr, "//  Start Date      : \n"
                                                  "// ============================================================================\n"
				                  "\n\n");

				// class tanimlamasi
				char *bigName = new char[len - 2];
	
				for( int i = 0; eventName[i] != 0; ++i )
					bigName[i] = toupper( eventName[i] );
	
				fprintf( cppFPtr, "#ifndef _%s_H\n"
				                  "#define _%s_H\n\n", bigName, bigName );
	
				fprintf( cppFPtr, "#include \"ControlBase.h\" \n\n");
	
				fprintf( cppFPtr, "class %s : public ControlBase {\n\n", className );
				fprintf( cppFPtr, "public:\n\n");
	
				fprintf( cppFPtr, "    // Constructor\n"
				                  "    // Ozel durumlar haric bu fonksiyonu doldurmaya gerek yoktur.\n"
				                  "    %s( int argc = 0, char*argv[] = 0 ) : ControlBase(argc, argv){}\n\n", className );
	
				fprintf( cppFPtr, "    // Destructor\n"
				                  "    // Ozel durumlar haric bu fonksiyonu doldurmaya gerek yoktur.\n"
				                  "    ~%s() {}\n\n", className );

				fprintf( cppFPtr, "    // Program bla bla\n"
				                  "    virtual int initialize();\n"
				                  "    virtual int start();\n"
				                  "    virtual int doloop();\n"
				                  "    virtual int stop();\n"
				                  "    virtual int terminate();\n\n");

				    
    				fprintf( cppFPtr, "private:\n\n" );
				fprintf( cppFPtr, "    // ----- Log Variables -----\n\n\n"
				                  "    // ----- Control Variables -----\n\n\n");

    				fprintf( cppFPtr, "};\n\n" );
    				fprintf( cppFPtr, "#endif\n\n" );	
			
			}
			
			if( strcmp( textLine, "INITIALIZE" ) == 0 ){
			
				// initialize fonksiyonu
				fprintf( cppFPtr, "// ============================================================================\n"
				                  "//  %s::initialize\n", className);
				fprintf( cppFPtr, "// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");

				cppMdfFPtr.getline( textLine, lineLength );
				while( strcmp( textLine, "START" ) != 0 ){					
					fprintf( cppFPtr, "//  %s\n", textLine );
					cppMdfFPtr.getline( textLine, lineLength );				
				}
                                fprintf( cppFPtr, "// ============================================================================\n");

				fprintf( cppFPtr, "int %s::initialize()\n"
                                                  "{\n\n"
                                                  "    return 0;\n"
                                                  "}\n\n", className );
			}
			
			if( strcmp( textLine, "START" ) == 0 ){
			
				// start fonksiyonu
				fprintf( cppFPtr, "// ============================================================================\n"
				                  "//  %s::start\n", className);
				fprintf( cppFPtr, "// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");

				cppMdfFPtr.getline( textLine, lineLength );
				while( strcmp( textLine, "DOLOOP" ) != 0 ){					
					fprintf( cppFPtr, "//  %s\n", textLine );
					cppMdfFPtr.getline( textLine, lineLength );				
				}

                                fprintf( cppFPtr, "// ============================================================================\n");

				fprintf( cppFPtr, "int %s::start()\n"
                                                  "{\n\n"
                                                  "    return 0;\n"
                                                  "}\n\n", className );
			
			}
			
			if( strcmp( textLine, "DOLOOP" ) == 0 ){
			
				// doloop fonksiyonu
				fprintf( cppFPtr, "// ============================================================================\n"
				                  "//  %s::doloop\n", className);
				fprintf( cppFPtr, "// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
				
				cppMdfFPtr.getline( textLine, lineLength );
				while( strcmp( textLine, "STOP" ) != 0 ){					
					fprintf( cppFPtr, "//  %s\n", textLine );
					cppMdfFPtr.getline( textLine, lineLength );				
				}
				
                                fprintf( cppFPtr, "// ============================================================================\n");

				fprintf( cppFPtr, "int %s::doloop()\n"
                                                  "{\n\n"
                                                  "    return 0;\n"
                                                  "}\n\n", className );
			
			}
			if( strcmp( textLine, "STOP" ) == 0 ){
			
				// stop fonksiyonu
				fprintf( cppFPtr, "// ============================================================================\n"
				                  "//  %s::stop\n", className);
				fprintf( cppFPtr, "// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
				
				cppMdfFPtr.getline( textLine, lineLength );
				while( strcmp( textLine, "TERMINATE" ) != 0 ){					
					fprintf( cppFPtr, "//  %s\n", textLine );
					cppMdfFPtr.getline( textLine, lineLength );				
				}
				
                                fprintf( cppFPtr, "// ============================================================================\n");

				fprintf( cppFPtr, "int %s::stop()\n"
                                                  "{\n\n"
                                                  "    return 0;\n"
                                                  "}\n\n", className );			
			}
			
			if( strcmp( textLine, "TERMINATE" ) == 0 ){
			
				// terminate fonksiyonu
				fprintf( cppFPtr, "// ============================================================================\n"
				                  "//  %s::terminate\n", className);
				fprintf( cppFPtr, "// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
				
				cppMdfFPtr.getline( textLine, lineLength );
				while( strcmp( textLine, "MAIN" ) != 0 ){					
					fprintf( cppFPtr, "//  %s\n", textLine );
					cppMdfFPtr.getline( textLine, lineLength );				
				}
				
                                fprintf( cppFPtr, "// ============================================================================\n");

				fprintf( cppFPtr, "int %s::terminate()\n"
                                                  "{\n\n"
                                                  "    return 0;\n"
                                                  "}\n\n", className );		
			}
		
		}		
		cppMdfFPtr.close();
	
	}
	else{
	
		// ilk aciklama
		fprintf( cppFPtr, "// =================================================================================\n \
                                   //  Zenom - Gercek zamanli Hardware-In-the-Loop Simulasyon\n \
                                   //  (c) 2000 QRTS\n \
                                   // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n \
                                   //  Control Program : %s.cpp\n \
                                   //  Description     : \n \
                                   //  Author          : \n \
                                   //  Start Date      : \n \
                                   // =================================================================================\n \
                                   \n\n", cppFile );
	
		// class tanimlamasi
		char *bigName = new char[len - 2];
	
		for( int i = 0; eventName[i] != 0; ++i )
			bigName[i] = toupper( eventName[i] );
	
		fprintf( cppFPtr, "#ifndef _%s_H\n \
                                   #define _%s_H\n\n", bigName, bigName );
	
		fprintf( cppFPtr, "#include \"ControlBase.h\" \n\n");
	
		fprintf( cppFPtr, "class %s : public ControlBase {\n\npublic:\n\n", className );

                fprintf( cppFPtr, "public:\n");
	
		fprintf( cppFPtr, "    // Constructor\n \
                                       // Ozel durumlar haric bu fonksiyonu doldurmaya gerek yoktur.\n \
                                       %s( int argc = 0, char*argv[] = 0 );\n\n", className );
	
		fprintf( cppFPtr, "/** Destructor\n\t* Obje yok eden fonksiyon\n\t*\n\t**/\n\t" );
		fprintf( cppFPtr, "~%s();\n\n\t", className );
	
		fprintf( cppFPtr, "/**\n\t"
   		"* Program yuklendigi zaman cagrilir. Arayuz(GUI) kullaniyorken, kullanici"
    		"\n\t* programa dosyayi yukledigi zaman cagrilir.\n\t*\n\t"
  		"* @return Başarılı olursa 0, olmazsa sıfır olmayan değer getirir.\n\t*/\n\t" );
  		fprintf( cppFPtr, "virtual int initialize();\n\n\t" );
     
  		fprintf( cppFPtr, "/**\n\t"
  		"* Program calistigi zaman cagrilir. Arayuz(GUI) kullanilmadiysa initialize\n\t"
  		"* fonksiyonunda hemen sonra calisir. Eger arayuz kullanildi ise, \n\t"
 		"* kullanicinin start butonuna basması beklenir.\n\t*\n\t" 
    		"* @return Başarılı olursa 0, olmazsa sıfır olmayan değer getirir.\n\t*/\n\t");
  		fprintf( cppFPtr, "virtual int start();\n\n\t" );
     
    		fprintf( cppFPtr, "/**\n\t"
    		"* Tanimlanan frekans araliginda cagrilacak olan fonksiyondur.\n\t*\n\t" 
    		"* @return Başarılı olursa 0, olmazsa sıfır olmayan değer getirir.\n\t*/\n\t" );
    		fprintf( cppFPtr, "virtual int doloop();\n\n\t" );
    
    		fprintf( cppFPtr, "/**\n\t"
    		"* Program durduruldugu zaman cagrilir. Program calısma surecini\n\t"
    		"* doldurdugunda veya arayuzden(GUI) stop butonuna basildigi zaman\n\t"
    		"* cagrilir.\n\t*\n\t" 
    		"* @return Başarılı olursa 0, olmazsa sıfır olmayan değer getirir.\n\t*/\n\t");
    		fprintf( cppFPtr, "virtual int stop();\n\n\t" );
    
    		fprintf( cppFPtr, "/**\n\t"
    		"* Program bittiği zaman cagrilir. Arayuzde(GUI) yeni dosya yuklendigi\n\t"
    		"* veya arayuz kapatildigi zaman cagrilir.\n\t*\n\t" 
   		"* @return Başarılı olursa 0, olmazsa sıfır olmayan değer getirir.\n\t*/\n\t");
    		fprintf( cppFPtr, "virtual int terminate();\n\n" );
    
    		fprintf( cppFPtr, "private:\n\n\t//your private member here\n\n};\n\n#endif\n\n" );
	
		// constructor
		fprintf( cppFPtr, "//====================================================="
		"=========================\n" );
		fprintf( cppFPtr, "// %s::%s\n", className, className );
		fprintf( cppFPtr, "//====================================================="
		"=========================\n" );
		fprintf( cppFPtr, "%s::%s( int argc, char* argv[] ) : ControlBase( argc,"
		" argv ){\n\n\t//your code here\n\n}\n\n", className, className );
	
		// destructor
		fprintf( cppFPtr, "//====================================================="
		"=========================\n" );
		fprintf( cppFPtr, "// %s::~%s\n", className, className );
		fprintf( cppFPtr, "//====================================================="
		"=========================\n" );
		fprintf( cppFPtr, "%s::~%s(){\n\n\t"
		"//your code here\n\n}\n\n", className, className );
	
		// initialize fonksiyonu
		fprintf( cppFPtr, "//====================================================="
		"=========================\n" );
		fprintf( cppFPtr, "// %s::initialize\n", className);
		fprintf( cppFPtr, "//====================================================="
		"=========================\n" );
		fprintf( cppFPtr, "int %s::initialize(){\n\n\t"
		"//your code here\n\n\treturn 0;\n\n}\n\n", className );
	
		// start fonksiyonu
		fprintf( cppFPtr, "//====================================================="
		"=========================\n" );
		fprintf( cppFPtr, "// %s::start\n", className);
		fprintf( cppFPtr, "//====================================================="
		"=========================\n" );
		fprintf( cppFPtr, "int %s::start(){\n\n\t"
		"//your code here\n\n\treturn 0;\n\n}\n\n", className );
		
		// doloop fonksiyonu
		fprintf( cppFPtr, "//====================================================="
		"=========================\n" );
		fprintf( cppFPtr, "// %s::doloop\n", className);
		fprintf( cppFPtr, "//====================================================="
		"=========================\n" );
		fprintf( cppFPtr, "int %s::doloop(){\n\n\t"
		"//your code here\n\n\treturn 0;\n\n}\n\n", className );
		
		// stop fonksiyonu
		fprintf( cppFPtr, "//====================================================="
		"=========================\n" );
		fprintf( cppFPtr, "// %s::stop\n", className);
		fprintf( cppFPtr, "//====================================================="
		"=========================\n" );
		fprintf( cppFPtr, "int %s::stop(){\n\n\t"
		"//your code here\n\n\treturn 0;\n\n}\n\n", className );
		
		// terminate fonksiyonu
		fprintf( cppFPtr, "//====================================================="
		"=========================\n" );
		fprintf( cppFPtr, "// %s::terminate\n", className);
		fprintf( cppFPtr, "//====================================================="
		"=========================\n" );
		fprintf( cppFPtr, "int %s::terminate(){\n\n\t"
		"//your code here\n\n\treturn 0;\n\n}\n\n", className );
		
	}
		
	// main fonksiyonu
	fprintf( cppFPtr, "// ============================================================================\n"
	                  "//  Main\n"
	                  "// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	fprintf( cppFPtr, "int main( int argc, char *argv[] )\n"
                          "{\n\n" );
	fprintf( cppFPtr, "    %s %s( argc, argv );\n",className, objectName);
	fprintf( cppFPtr, "    %s.run();\n\n", objectName);
	fprintf( cppFPtr, "    return 0;\n"
                          "}");
	fclose( cppFPtr );

	return 0;

}

int CreateZnm::createMakefile(){
	
	int len = strlen(folderPath) + 10;

	char *makePath = new char[len];
	
	if( makePath == NULL ){
	
		cout << "Error: " << strerror(12) << endl;
		return 1;
		
	}
	
	snprintf(makePath, len, "%s/Makefile", folderPath );
	
	FILE *makeFPtr;
	
	makeFPtr = fopen( makePath, "w" );
	
	if( makeFPtr == NULL ){
	
		cout << "Makefile can not be created" << endl;
		return 1;
			
	}
	
	fprintf(makeFPtr, "#Warning: this file should must be run %c sudo make %c\n\n", tirnak, tirnak );
	
	ifstream makeMdfFPtr;
	
	makeMdfFPtr.open( makeMdfFile, ios::in );
	
	char textLine[lineLength];
	
	if( ! makeMdfFPtr.is_open()  ){
	
		fprintf( makeFPtr, "XENO_DESTDIR:=\nXENO_CONFIG:=/usr/xenomai/bin/xeno-config\n\n" );
		fprintf( makeFPtr, "#--- POSIX ---\nXENO_POSIX_CFLAGS:=$(shell "
		"DESTDIR=$(XENO_DESTDIR) $(XENO_CONFIG) --posix-cflags)\n");
		fprintf( makeFPtr, "XENO_POSIX_LIBS:=$(shell DESTDIR="
		"$(XENO_DESTDIR) $(XENO_CONFIG) --posix-ldflags)\n\n");
		fprintf( makeFPtr, "#--- NATIVE ---\nXENO_NATIVE_CFLAGS:=$(shell "
		"DESTDIR=$(XENO_DESTDIR) $(XENO_CONFIG) --xeno-cflags)\n");
		fprintf( makeFPtr, "XENO_NATIVE_LIBS:= -lnative $(shell "
		"DESTDIR=$(XENO_DESTDIR) $(XENO_CONFIG) --xeno-ldflags)\n\n");
		fprintf( makeFPtr, "CC= g++\nLD= g++\nCFLAGS = $(XENO_NATIVE_CFLAGS) "
		"$(FLTK_CFLAGS) $(XENO_POSIX_CFLAGS) -W -Wall -fexceptions "
		"-fno-builtin -O2 -fpic -D_REENTRANT -c -g\n");
		fprintf( makeFPtr, "LDFLAGS = -fexceptions -O2 -lrtdk -lrtdm\n");
		fprintf( makeFPtr, "INCLUDEHEADERS = -I /usr/local/Zenom/include/"
		" -I /usr/local/Zenom/include/Common -I /usr/local/Zenom/include/Zenom"
		" -I /usr/local/Zenom/include/ZenomGUI"
		" -I /usr/local/include/QMath/ -I /usr/local/rtnet/include"
		" -I /usr/local/Zenom/include/XenoTools/native -I /usr/local/Zenom/include/XenoTools/posix"
		"\n");
		fprintf( makeFPtr, "INCLUDELIBS = -L $(XENO_POSIX_LIBS) $(XENO_NATIVE_LIBS)"
		" -lX11 -lGL -lGLU -L /usr/local/Zenom/lib/ -L /usr/xenomai/lib"
		" -lZenom -lZenomGUI -lXenoTools\nOBJS= \n\n");
		
	}
	else{
	
		while( ! makeMdfFPtr.eof() ){
		
			makeMdfFPtr.getline( textLine, lineLength );
			
			fprintf( makeFPtr, "%s\n", textLine );

		}
		
		makeMdfFPtr.close();
	
	}
	
	fprintf( makeFPtr, "TARGET= %s\n", oFile );
	
	fprintf(makeFPtr, "RUN= run\nLINK= link\n\n");
	
	fprintf( makeFPtr, "CLEAN= rm -rf $(TARGET) %s\n\n", makeFile);
	
	fprintf( makeFPtr, "# ========== Targets ==========\n" );
	
	fprintf( makeFPtr, "targets: $(TARGET) $(LINK) $(RUN)\n\n" );
	
	fprintf( makeFPtr, "# ----- %s -----\n", eventName );
	
	fprintf( makeFPtr, "%s: %s\n\t", oFile, cppFile );
	
	fprintf( makeFPtr, "$(CC) $(CFLAGS) %s $(INCLUDEHEADERS)\n\n", cppFile );
	
	fprintf( makeFPtr, "link:\n\t$(LD) -o %s $(TARGET) $(OBJ) $(INCLUDELIBS) $(LDFLAGS)\n\n", makeFile );

	fprintf( makeFPtr, "run:\n\t./%s --cfg %s.cfg\n\n", makeFile, eventName );
	
	fprintf( makeFPtr, "clean:\n\t$(CLEAN) ");
	
	fclose( makeFPtr );

	return 0;

}

int CreateZnm::checkTypo( int argc, char *argv[] ){

	if( argc != 2 ){
	
		cout << "Usage: " << argv[0] << " projeName" << endl;
		return 1;
		
	}

	return 0;

}
