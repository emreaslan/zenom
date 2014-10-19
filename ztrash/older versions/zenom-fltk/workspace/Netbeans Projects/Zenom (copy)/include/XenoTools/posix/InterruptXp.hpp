//==============================================================================
// Semaphore.hpp - POSIX shared memory wrapper class.
//
// Author        : 
// Version       : 2.0.01 (Temmuz 2009)
// Compatibility : POSIX, GCC
//==============================================================================

#ifndef _INTERRUPT_HPP_INCLUDED
#define _INTERRUPT_HPP_INCLUDED

#include <sys/mman.h>
#include <pthread.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <stdlib.h>

//==============================================================================
// class ConditionVariable
//------------------------------------------------------------------------------
// \brief
// Interruptions management object
//
// 
// <b>Ornek Program:</b>
//
// \include Interrupt.t.cpp
//==============================================================================

class InterruptXp
{
 public:

  // InterruptXP constructor
  InterruptXp();


  // InterruptXP destructor
  ~InterruptXp();

   // Interrupt durumda yapilacak islemi set eder .
   // irq       Interrupt kanali
   // isr       Interrupt subrutini
   // iack      Opsiyonel interrupt bilgilendirme rutini, kullanilmiyorsa NULL olmali
   //  return 	Basarili olursa 0 , Hata meydana gelirse -1 getirir, 'errno' degerini  
   //           getErrnoError() fonksiyonu ile ulasılabilir.
   int attach(unsigned irq,int mode);

   // Interrupt objesini yok eder.
   //   return 	Basarili olursa 0 , Hata meydana gelirse -1 getirir, 'errno' degerini  
   //           getErrnoError() fonksiyonu ile ulasılabilir.
   int detach();

   // Bir sonraki interrupt olusunu bekler. 
   // timeout degeri kadar bekler, eger verilen sure icersinde interrupt olursa
   // interrupt numarasini dondurur olamazsa -1 dondurur ve errno degeri ETIMEDOUT olur.
   //  timeout   zaman asimi
   //  return        Basarili olursa interrupt numarasini,Hata meydana gelirse -1 getirir
   //                errno' degerini getErrnoError() fonksiyonu ile ulasılabilir.
   int wait( const struct timespec * timeout );

   // Interrupt kanalini kontrol eder.
   // channel   interrupt kanali
   //  return 	Basarili olursa 0 , Hata meydana gelirse -1 getirir, 'errno' degerini  
   //          getErrnoError() fonksiyonu ile ulasılabilir.
   int control(int channel);


   //  return  En son meydana gelen hatayi getirir.
   int getErrnoError() const;

 private:

    // ConditionVariable degiskeni
  pthread_intr_t inter;

   // Hatalar saklanir   
   int d_errno;
};


//==============================================================================
// ShMem::getErrnoError
//==============================================================================
int InterruptXp::getErrnoError() const
{
 return d_errno;
}

#endif // _SEMAPHORE_HPP_INCLUDED
