// ============================================================================
//  Zenom - Gercek zamanli Hardware-In-the-Loop Simulasyon
//  
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  Control Program : <%=file_name%>.cpp
//  Description     : 
//  Author          :
//  
//  Start Date      : 
// ============================================================================

#ifndef _TEST_H
#define _TEST_H

#include "ControlBase.h" 

class test : public ControlBase 
{
public:

    // Constructor
    test( int argc = 0, char*argv[] = 0 ) : ControlBase(argc, argv){}

    // Destructor
    ~test() {}

    // Program bla bla
    virtual int initialize();
    virtual int start();
    virtual int doloop();
    virtual int stop();
    virtual int terminate();

private:
    // ----- Log Variables -----


    // ----- Control Variables -----

};

#endif

// ============================================================================
//  test::initialize
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//    Bu fonksiyon kullanici arayuz kullanimda iken control programi yuklendigi 
//  zaman cagrilir. Kullanici arayuz kullanilmiyorsa hemen cagrilir.
//    Log ve Control degiskenlerinin  kayit etme  islemlerinin burada yapilmasi 
//  zorunludur. Log degiskenleri  registerLogVariable  fonksiyonu ile;  Control 
//  degiskenleri ise registerControlVariable fonksiyonu ile kayit edilir.
//  
//  UYARI! = Log ve Control degiskeni register  fonksiyonu ile kayit  edilirken 
//  string olarak verilen isim ( 2. parametre) degisken ismi kesinlikle birebir 
//  ayni olmalidir.
//  UYARI! = new, malloc gibi dinamik hafiza alinarak  olusturulan iki Boyutlu 
//  diziler kesinlikle Log degiskeni olarak kayit edilmemelidir. 
//   
// ============================================================================
int test::initialize()
{
    
    return 0;
}

// ============================================================================
//  test::start
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//    Control  programi  calismaya baslamadan  once cagrilir. Kullanici  arayuz 
//  kullanimdayken START butona basildigi an cagrilir; arayuz kullanilmiyorken
//  initialize fonksiyonundan hemen sonra cagrilir.
//    Log degiskenlerine ilk deger atanmasi burada yapilir. 
//  
// ============================================================================
int test::start()
{
    
    return 0;
}

// ============================================================================
//  test::doloop
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//    Her bir control dongusunde cagrilir.Control hesaplamalari burada yapilir.
//  Hesaplamalarinizda;
//   frequency              program calisma frekansi
//   period                 program calisma periyodu (1/frequency)
//   elapsedTimeSecond      Saniye cinsinden gecen simulasyon suresi
//   elapsedTimeMiliSecond  Mili-saniye cinsinden gecen simulasyon suresi   
//   elapsedTimeNano        Nano-saniye cinsinden gecen simulasyon suresi 
//  degiskenlerini kullanabilirsiniz.        
//  
// ============================================================================
int test::doloop()
{

    return 0;
}

// ============================================================================
//  test::stop
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//    Control  program bittigi zaman cagrilir. Kullanici arayuz kullanimda iken 
//  simulasyon  suresi  bittikten hemen  sonra veya STOP  butonuna basildiginda 
//  cagrilir; arayuz kullanilmiyorken  simulasyon suresi  bittikten hemen sonra 
//  cagrilir.
//  
// ============================================================================
int test::stop()
{

    return 0;
}

// ============================================================================
//  test::terminate
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//   Bu fonksiyon kullanici arayuz kullanimdayken control programi kaldirildigi 
//  ve ya yeni bir control program yuklendigi zaman cagrilir. Kullanici  arayuz 
//  kullanilmiyorsa stop fonksiyonundan hemen cagrilir.
//    Bu fonksiyon dinamik  olarak alinan hafizalari  sisteme geri vermek  icin
//  kullanilir.
//  
// ============================================================================
int test::terminate()
{

    return 0;
}

// ============================================================================
//  Main
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
int main( int argc, char *argv[] )
{
    test c( argc, argv );
    c.run();

    return 0;
}

