//==============================================================================
// Semaphore.hpp - POSIX shared memory wrapper class.
//
// Author        : 
// Version       : 2.0.01 (Temmuz 2009)
// Compatibility : POSIX, GCC
//==============================================================================

#ifndef _SEMAPHOREXP_HPP_INCLUDED
#define _SEMAPHOREXP_HPP_INCLUDED

#include <sys/mman.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <stdlib.h>
#include <semaphore.h>


//==============================================================================
// class Semaphore
//------------------------------------------------------------------------------
// \brief
// Shared memory objects.
// Semaphore, threadlerin ortak kullandığı kaynaklar için sayaçtır. Semaphore
// için maksimum değer SEM_VALUE_MAX olarak tanımlanmıştır.
// 
// <b>Ornek Program:</b>
//
// \include Semaphore.t.cpp
//==============================================================================

class SemaphoreXp
{
 public:

  // SemaphoreXp constructor
  SemaphoreXp();

  // SemaphoreXp destructor
  ~SemaphoreXp();

   // Isimsiz Semaphore olusturulur.
   //  pshared  Sıfır ise aynı processten yaratılan threadler kullanabilir, 
   //           değilse herhangi bir thread kullanılabilir. 
   //  value    Semaphore sayac degeri
   //  return 	Basarili olursa 0 , Hata meydana gelirse -1 getirir, 'errno' degerini  
   //          	getErrnoError() fonksiyonu ile ulasılabilir.
  int init( int pshared, unsigned value );
		
   // Isimli Semaphore olusturulur.
   //  nm       Semaphore ismi
   //  oflags   Yaratılma bayrakları
   //  return 	Basarili olursa 0 , Hata meydana gelirse -1 getirir, 'errno' degerini  
   //          	getErrnoError() fonksiyonu ile ulasılabilir.
  int create( const char *name, int oflags );

   // Isimli Semaphore olusturulur.
   //  nm       Semaphore ismi
   //  oflags   Yaratılma bayrakları
   //  return 	Basarili olursa 0 , Hata meydana gelirse -1 getirir, 'errno' degerini  
   //          	getErrnoError() fonksiyonu ile ulasılabilir.
  int open( const char *name, int oflags );

   // Isimli Semaphoreu kapatır.
   //  return 	Basarili olursa 0 , Hata meydana gelirse -1 getirir, 'errno' degerini  
   //          	getErrnoError() fonksiyonu ile ulasılabilir.
  int close();

   // Isimsiz Semaphoreu yok eder.
   //  return 	Basarili olursa 0 , Hata meydana gelirse -1 getirir, 'errno' degerini  
   //          	getErrnoError() fonksiyonu ile ulasılabilir.
  int destroy();

   // Isimli Semaphoreu kapatır.
   //  return 	Basarili olursa 0 , Hata meydana gelirse -1 getirir, 'errno' degerini  
   //          	getErrnoError() fonksiyonu ile ulasılabilir.
  int unlink();

   // Semaphore kitlenir.
   //  return 	Basarili olursa 0 , Hata meydana gelirse -1 getirir, 'errno' degerini  
   //          	getErrnoError() fonksiyonu ile ulasılabilir.
  int wait();

   // Semaphore kitleme girisiminde bulunur.
   // wait fonksiyonundan farkli olarak, semaphore kilitli ise, beklemeden geriye -1
   // dondurur ve errno degeri EAGAIN olur.
   //  return 	Basarili olursa 0 , Hata meydana gelirse -1 getirir, 'errno' degerini  
   //          	getErrnoError() fonksiyonu ile ulasılabilir.
  int tryWait();

   // Semaphore kitleme girisiminde bulunur.
   // wait fonksiyonundan farkli olarak, semaphore kilitli ise, parametre 
   // olarak verilen abs_timeout degeri kadar bekler, eger basarili olamazsa -1
   // dondurur ve errno degeri ETIMEDOUT olur.
   //  abs_timeout  Semaphorea girişi için beklenecek zaman
   //  return 	Basarili olursa 0 , Hata meydana gelirse -1 getirir, 'errno' degerini
   //           getErrnoError() fonksiyonu ile ulasılabilir.
  int timedWait(const struct timespec * abs_timeout);

   // Semaphore kilidi acilir.
   //  return 	Basarili olursa 0 , Hata meydana gelirse -1 getirir, 'errno' degerini  
   //          	getErrnoError() fonksiyonu ile ulasılabilir.
  int post();

   // Semaphore degerini getirir.
   //  value    Semaphore degerinin saklanacagi degisken.
   //  return 	Basarili olursa 0 , Hata meydana gelirse -1 getirir, 'errno' degerini  
   //          	getErrnoError() fonksiyonu ile ulasılabilir.
  int getValue( int *value );

   //  return  En son meydana gelen hatayi getirir.
  int getErrnoError() const;

 private:

   // Semaphore degiskeni
  sem_t * sem;

   // Semaphore ismi
  char * semName;

   // Hatalar saklanir   
  int d_errno;

  bool isOwner;
 
};


//==============================================================================
// SemaphoreXp::getErrnoError
//==============================================================================
int SemaphoreXp::getErrnoError() const
{
 return d_errno;
}

#endif // _SEMAPHOREXP_HPP_INCLUDED
