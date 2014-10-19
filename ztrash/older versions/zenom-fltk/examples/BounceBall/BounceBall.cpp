// ============================================================================
//  Zenom - Gercek zamanli Hardware-In-the-Loop Simulasyon
//  
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  Control Program : BounceBall.cpp
//  Description     : 
//  Author          :
//  
//  Start Date      : 
// ============================================================================


#ifndef _BOUNCEBALL_H
#define _BOUNCEBALL_H

#include "ControlBase.h" 
#include "Integrator.hpp"

class BounceBall : public ControlBase {

public:

    // Constructor
    // Ozel durumlar haric bu fonksiyonu doldurmaya gerek yoktur.
    BounceBall( int argc = 0, char*argv[] = 0 ) : ControlBase(argc, argv){}

    // Destructor
    // Ozel durumlar haric bu fonksiyonu doldurmaya gerek yoktur.
    ~BounceBall() {}

    // Program bla bla
    virtual int initialize();
    virtual int start();
    virtual int doloop();
    virtual int stop();
    virtual int terminate();

private:

    Integrator<double> integratorAcc;
    Integrator<double> integratorVelocity;
    int totalBounceCount;
    int currentBounceCount;
    double ballPos[3];
    double ballScale[3];
    double gravity;
    double ballRadius;
    double velocity;
    double hitAcc;
    double hitAcc2;
    double acc;
    double radius;
    double xyTest[2];

    // ----- Log Variables -----


    // ----- Control Variables -----


};

#endif

// ============================================================================
//  BounceBall::initialize
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
int BounceBall::initialize()
{
    registerLogVariable(ballPos , "ballPos", "Topun Konumu",1,3);
    registerLogVariable(ballScale , "ballScale", "Topun Boyutu",1,3);
    registerLogVariable(xyTest , "xyTest", "xyTest Degiskeni",1,2);

    registerLogVariable(totalBounceCount , "totalBounceCount", "Topun benzetim boyunca toplam  sekme sayisi");
    registerLogVariable(currentBounceCount , "currentBounceCount", "Topun bir kosum boyunca sekme sayisi");
    
    registerLogVariable(velocity , "velocity", "Hiz");
    registerLogVariable(acc , "acc", "Ivme");
    registerLogVariable(hitAcc , "hitAcc", "Carpma Ivmesi");
    registerLogVariable(radius , "radius", "Top Yaricapi");

    registerControlVariable(hitAcc2, "hitAcc2" ,"carpma etkisi");
    registerControlVariable(gravity, "gravity" ,"Yercekimi");
    registerControlVariable(ballRadius, "ballRadius" ,"Top Yaricapi");

    totalBounceCount = 0;
    
    return 0;
}

// ============================================================================
//  BounceBall::start
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//    Control  programi  calismaya baslamadan  once cagrilir. Kullanici  arayuz 
//  kullanimdayken START butona basildigi an cagrilir; arayuz kullanilmiyorken
//  initialize fonksiyonundan hemen sonra cagrilir.
//    Log degiskenlerine ilk deger atanmasi burada yapilir. 
//  
// ============================================================================
int BounceBall::start()
{
    currentBounceCount = 0;
    integratorAcc = Integrator<double>(1/frequency, 0);
    //integratorAcc.reset(-1);
    
    integratorVelocity = Integrator<double>(1/frequency, 20.0);
    //integratorVelocity.reset(-1);
    
    ballPos[0] = 0; ballPos[1] = 20; ballPos[2] = 0;
    ballScale[0] = 1; ballScale[1] = 1; ballScale[2] = 1;
  
    hitAcc = 0;
    
    return 0;
}

// ============================================================================
//  BounceBall::doloop
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
int BounceBall::doloop()
{
    radius = ballRadius;
    if( ( ballPos[1] >= 0 && ballPos[1] <= ballRadius*2))
    {
        ballScale[1] = fabs(ballRadius / ballPos[1]);
        hitAcc = hitAcc2;
    }
    else
    {
        ballScale[1] = 1;
        hitAcc = 0;
    }
    double oldVelocity = velocity;

    acc = hitAcc - gravity;
    velocity = integratorAcc.integrate(acc);
    ballPos[1] = integratorVelocity.integrate(velocity);
    xyTest[0] = acc;
    xyTest[1] = velocity;

    if ( oldVelocity < 0 && velocity > 0 )
    {
        ++totalBounceCount;
        ++currentBounceCount;
    }

    return 0;
}

// ============================================================================
//  BounceBall::stop
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//    Control  program bittigi zaman cagrilir. Kullanici arayuz kullanimda iken 
//  simulasyon  suresi  bittikten hemen  sonra veya STOP  butonuna basildiginda 
//  cagrilir; arayuz kullanilmiyorken  simulasyon suresi  bittikten hemen sonra 
//  cagrilir.
//  
// ============================================================================
int BounceBall::stop()
{

    return 0;
}

// ============================================================================
//  BounceBall::terminate
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//   Bu fonksiyon kullanici arayuz kullanimdayken control programi kaldirildigi 
//  ve ya yeni bir control program yuklendigi zaman cagrilir. Kullanici  arayuz 
//  kullanilmiyorsa stop fonksiyonundan hemen cagrilir.
//    Bu fonksiyon dinamik  olarak alinan hafizalari  sisteme geri vermek  icin
//  kullanilir.
//  
// ============================================================================
int BounceBall::terminate()
{

    return 0;
}

// ============================================================================
//  Main
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
int main( int argc, char *argv[] )
{

    BounceBall bounceBall( argc, argv );
    bounceBall.run();

    return 0;
}
