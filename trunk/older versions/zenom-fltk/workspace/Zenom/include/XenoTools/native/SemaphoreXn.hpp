//==============================================================================
// Semaphore.hpp - Native Semaphores services
//
// Author        : 
// Version       : 2.0.01 (Temmuz 2009)
// Compatibility : POSIX, GCC
//==============================================================================

#ifndef _SEMAPHOREXN_HPP_INCLUDED
#define _SEMAPHOREXN_HPP_INCLUDED

#include <native/sem.h>

//==============================================================================
// class Semaphore
//------------------------------------------------------------------------------
// \brief
// POSIX Semaphores services
// Task senkronizasyonu saglanir. 
// Semaphore tasklar arasında senkronizasyon sağlar. Semaphoreda verilen value 
// değeri ile ortak verilere erişebilen task sayısı sınırlanır. Tasklar öncelik
// sırasına veya fifo sırasına göre semaphoreda askıda kalabilir.
// <b>Ornek Program:</b>
//
// \include SemaphoreXn.t.cpp
//==============================================================================

#define SEMAPHORE_TIMEOUT 10000000000LL  // Varsayilan zaman asimi olarak 10sn

class SemaphoreXn
{
 public:

  // Semaphore Constructor
  // Degisken atamalari yapilir.
  SemaphoreXn();

  // Semaphore Destructor
  ~SemaphoreXn();
  
   // Semaphore yaratilir
   //  name     Semaphore ismi
   //  icount   Semaphore'a girecek Task sayisi
   //  mode     Semaphore yaratilma modu
   //           S_FIFO semaphoreda tasklar FIFO sırasına göre askıda kalır.
   //           S_PRIO semaphoreda tasklar priority sırasına göre askıda kalır.
   //           S_PULSE 
   //  return 	Basarili olursa 0 , Hata meydana gelirse -1 getirir, 
   //           hata degerine getErrnoError() fonksiyonu ile ulasılabilir.
   int create( const char * name, unsigned long icount, int mode);

   // Var olan Semaphore'a baglanir. Semaphore yok ise -1 getirir.
   //  name     Baglanilacak Semaphore'un ismi
   //  SEMAPHORE_TIMEOUT  Beklenecek zaman
   //  return 	Basarili olursa 0 , Hata meydana gelirse -1 getirir, 
   //           hata degerine getErrnoError() fonksiyonu ile ulasılabilir.
   int bind(const char *name, RTIME timeout = SEMAPHORE_TIMEOUT);

   // Semaphore kitleme girisiminde bulunur.
   //  SEMAPHORE_TIMEOUT  Beklenecek zaman
   //  return 	Basarili olursa 0 , Hata meydana gelirse -1 getirir, 
   //           hata degerine getErrnoError() fonksiyonu ile ulasılabilir.
   int p( RTIME timeout = SEMAPHORE_TIMEOUT);

   // Semaphore kilidi acilir.
   //  return 	Basarili olursa 0 , Hata meydana gelirse -1 getirir, 
   //           hata degerine getErrnoError() fonksiyonu ile ulasılabilir.
   int v();

   // Semaphore'da bekleyen butun tasklarin kilidi acilir.
   //  return 	Basarili olursa 0 , Hata meydana gelirse -1 getirir, 
   //           hata degerine getErrnoError() fonksiyonu ile ulasılabilir.
   int broadcast();

   // Semaphore'u siler. Ancak heap yaratan (create) eden obje silebilir. Aksi takdirde
   // -1 getirir ve EACCES hatasi d_errno degiskenine atanir. 
   //  return 	Basarili olursa 0 , Hata meydana gelirse -1 getirir, 
   //           hata degerine getErrnoError() fonksiyonu ile ulasılabilir.
   int deleteSem();

   // Semaphore'u serbest birakir. Ancak semaphore'a baglanan (bind) obje serbest birakabilir.
   // Aksi takdirde -1 getirir ve EACCES hatasi d_errno degiskenine atanir. 
   //  return 	Basarili olursa 0 , Hata meydana gelirse -1 getirir, 
   //           hata degerine getErrnoError() fonksiyonu ile ulasılabilir.
   int unbind();

   // Semaphore bilgilerini info struct icine yazar.
   //  info	Heap bilgilerinin yazilacagi struct pointeri  
   //  return 	Basarili olursa 0 , Hata meydana gelirse -1 getirir, 
   //           hata degerine getErrnoError() fonksiyonu ile ulasılabilir.
  int inquire( RT_SEM_INFO * info );

   //  return  En son meydana gelen hatayi getirir.
  int getErrnoError() const;

 private:

   // Semaphore degiskeni
   RT_SEM sem;

   // Semaphore ismi
   char * semName;

   // Isimli Semaphore'da yalnızca create eden unlink yapabilir
   // Bu bilgiyi belirten flag, create eden ise true degilse false
   bool isOwner;

   // Hatalar saklanir   
  int d_errno;
 
};


//==============================================================================
// SemaphoreXn::getErrnoError
//==============================================================================
int SemaphoreXn::getErrnoError() const
{
 return d_errno;
}

#endif // _SEMAPHOREXN_HPP_INCLUDED
