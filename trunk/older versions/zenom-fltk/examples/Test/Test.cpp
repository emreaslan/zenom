// =================================================================================
                                    //  Zenom - Gercek zamanli Hardware-In-the-Loop Simulasyon
                                    //  (c) 2000 QRTS
                                    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                                    //  Control Program : Test.cpp.cpp
                                    //  Description     : 
                                    //  Author          : 
                                    //  Start Date      : 
                                    // =================================================================================
                                    

#ifndef _TEST_H
#define _TEST_H

#include "ControlBase.h" 

class Test : public ControlBase {

private:
	double Time;
        double counter;


public:
    // Constructor
    // Ozel durumlar haric bu fonksiyonu doldurmaya gerek yoktur.
    Test( int argc = 0, char*argv[] = 0 );

	/** Destructor
	* Obje yok eden fonksiyon
	*
	**/
	~Test();

	/**
	* Program yuklendigi zaman cagrilir. Arayuz(GUI) kullaniyorken, kullanici
	* programa dosyayi yukledigi zaman cagrilir.
	*
	* @return Başarılı olursa 0, olmazsa sıfır olmayan değer getirir.
	*/
	virtual int initialize();

	/**
	* Program calistigi zaman cagrilir. Arayuz(GUI) kullanilmadiysa initialize
	* fonksiyonunda hemen sonra calisir. Eger arayuz kullanildi ise, 
	* kullanicinin start butonuna basması beklenir.
	*
	* @return Başarılı olursa 0, olmazsa sıfır olmayan değer getirir.
	*/
	virtual int start();

	/**
	* Tanimlanan frekans araliginda cagrilacak olan fonksiyondur.
	*
	* @return Başarılı olursa 0, olmazsa sıfır olmayan değer getirir.
	*/
	virtual int doloop();

	/**
	* Program durduruldugu zaman cagrilir. Program calısma surecini
	* doldurdugunda veya arayuzden(GUI) stop butonuna basildigi zaman
	* cagrilir.
	*
	* @return Başarılı olursa 0, olmazsa sıfır olmayan değer getirir.
	*/
	virtual int stop();

	/**
	* Program bittiği zaman cagrilir. Arayuzde(GUI) yeni dosya yuklendigi
	* veya arayuz kapatildigi zaman cagrilir.
	*
	* @return Başarılı olursa 0, olmazsa sıfır olmayan değer getirir.
	*/
	virtual int terminate();

private:

	//your private member here

};

#endif

//==============================================================================
// Test::Test
//==============================================================================
Test::Test( int argc, char* argv[] ) : ControlBase( argc, argv ){

	//your code here

}

//==============================================================================
// Test::~Test
//==============================================================================
Test::~Test(){

	//your code here

}

//==============================================================================
// Test::initialize
//==============================================================================
int Test::initialize(){

	registerLogVariable(Time, "Time", "Time");
        registerLogVariable(counter, "counter", "counter");
        

	//your code here

	return 0;

}

//==============================================================================
// Test::start
//==============================================================================
int Test::start(){

	Time = 0;
        counter = 0;

	//your code here

	return 0;

}

//==============================================================================
// Test::doloop
//==============================================================================
int Test::doloop(){

	//your code here

	Time = elapsedTimeSecond;
        counter++;

	return 0;

}

//==============================================================================
// Test::stop
//==============================================================================
int Test::stop(){

	//your code here

	return 0;

}

//==============================================================================
// Test::terminate
//==============================================================================
int Test::terminate(){

	//your code here

	return 0;

}

// ============================================================================
//  Main
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
int main( int argc, char *argv[] )
{

    Test test( argc, argv );
    test.run();

    return 0;
}
