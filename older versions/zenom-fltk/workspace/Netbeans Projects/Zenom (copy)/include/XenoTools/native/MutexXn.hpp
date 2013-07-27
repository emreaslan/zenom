//==============================================================================
// MutexXn.hpp - Mutual Exclusion object
//             - Condition Variable object
//
// Author        : 
// Version       : 2.0.01 (Temmuz 2009)
// Compatibility : POSIX, GCC
//==============================================================================

#ifndef _MUTEXXN_HPP_INCLUDED
#define _MUTEXXN_HPP_INCLUDED

#include <native/mutex.h>
#include <native/cond.h>


//==============================================================================
// class Mutex
//------------------------------------------------------------------------------
// \brief
// NATIVE Mutex 
// Mutex eş zamanlı değişen ortak verileri korumak için elverişlidir. Mutex 
// alanına tasklardan yalnızca bir tanesi girebilir. Diğer tasklar mutex alanına
// girmek için bekler. Tasklar mutex alanına task öncelik sırasına göre girer.

// Condition variable,  ortak veri yapısı değişene kadar, taskın uyutulmasına 
// olanak verir. Condition variable her zaman mutex ile ilişkili olduğu için 
// MutexXn sınıfı condition variable'ı barındırır.
//
// <b>Ornek Program:</b>
//
// \include MutexXn.t.cpp
//==============================================================================

#define MUTEX_TIMEOUT 10000000000LL  // Varsayilan zaman asimi olarak 10sn

class MutexXn
{
 public:

  // Mutex Constructor
  // Degisken atamalari yapilir.
  MutexXn();

  // Mutex Destructor
  ~MutexXn();
  
   // Mutex yaratilir
   //  mName    Mutex ismi
   //  cName    Condition Variable ismi
   //  return   Başarılı olursa 0 , hata meydana gelirse -1 getirir, hata 
   //           değerine getErrnoError() fonksiyonu ile ulaşılabilir.
   int create(const char * mName, const char * cName = NULL);

   // Var olan Mutex'e baglanir. 
   //  mName    Baglanilacak Mutex ismi
   //  MUTEX_TIMEOUT  Baglanmak icin beklenecek zaman
   //  cName    Baglanilacak Condition Variable ismi
   //  return 	Basarili olursa 0 , Hata meydana gelirse -1 getirir, 'errno' degerini
   //          	getErrnoError() fonksiyonu ile ulasılabilir
   int bind(const char *mName, RTIME timeout = MUTEX_TIMEOUT, const char * cName = NULL);

   // Mutex'e girmek icin bekler.
   //  MUTEX_TIMEOUT  Mutex alanina girmek icin beklenecek zaman
   //  return 	Basarili olursa 0 , Hata meydana gelirse -1 getirir, 'errno' degerini
   //          	getErrnoError() fonksiyonu ile ulasılabilir.
   int acquire(RTIME timeout = MUTEX_TIMEOUT);

   // Mutex'ten cikilir. 
   //  return 	Basarili olursa 0 , Hata meydana gelirse -1 getirir, hata degerini
   //          	getErrnoError() fonksiyonu ile ulasılabilir.
   int release();

   // Condition Variable'a sinyal verilir. Oncelik sırasına göre bekleyen 
   // ilk taskı bırakır
   //  return 	Basarili olursa 0 , Hata meydana gelirse -1 getirir, hata degerini
   //          	getErrnoError() fonksiyonu ile ulasılabilir.
   int condSignal();

   // Condition Variable'lara sinyal verilir. Bekleyen butun taskları bırakır.
   //  return 	Basarili olursa 0 , Hata meydana gelirse -1 getirir, hata degerini
   //          	getErrnoError() fonksiyonu ile ulasılabilir.
   int condBroadcast();

   // Condition Variable'da bekler.
   //  MUTEX_TIMEOUT  Condştşon variable icin beklenecek zaman
   //  return 	Basarili olursa 0 , Hata meydana gelirse -1 getirir, hata degerini
   //          	getErrnoError() fonksiyonu ile ulasılabilir.
   int condWait(RTIME timeout = MUTEX_TIMEOUT);

   // Mutex ve varsa Condition Variable'i siler. Ancak mutex yaratan (create) eden
   // obje silebilir. Aksi takdirde -1 getirir ve EACCES hatasi d_errno degiskenine
   // atanir.
   //  return 	Basarili olursa 0 , Hata meydana gelirse -1 getirir, hata degerini
   //          	getErrnoError() fonksiyonu ile ulasılabilir.
   int deleteMutex();

   // Mutex'i ve varsa Condition Variable'i serbest birakir. Ancak mutex'e baglanan
   // (bind) obje serbest birakabilir. Aksi takdirde -1 getirir ve EACCES hatasi 
   // d_errno degiskenine atanir.
   //  return 	Basarili olursa 0 , Hata meydana gelirse -1 getirir, hata degerini 
   //          	getErrnoError() fonksiyonu ile ulasılabilir.
   int unbind();

   // Mutex bilgilerini info struct icine yazar.
   //  info	Mutex bilgilerinin yazilacagi struct pointeri  
   //  return 	Basarili olursa 0 , Hata meydana gelirse -1 getirir, hata degerini  
   //          	getErrnoError() fonksiyonu ile ulasılabilir.
  int inquire( RT_MUTEX_INFO * info );

   // Condition Variable bilgilerini info struct icine yazar.
   //  info	Condition Variable bilgilerinin yazilacagi struct pointeri  
   //  return 	Basarili olursa 0 , Hata meydana gelirse -1 getirir, hata degerini  
   //          	getErrnoError() fonksiyonu ile ulasılabilir.
  int condInquire( RT_COND_INFO * info );

   //  return  En son meydana gelen hatayi getirir.
  int getErrnoError() const;

 private:

   // Mutex degiskeni
   RT_MUTEX mutex;

   // Condition Variable degiskeni
   RT_COND cond;

   // Mutex ismi
   char * mutexName;

   // Condition Variable ismi
   char * condName;

   // Mutex yaratan( create ) eden obje ise true, 
   // Mutexe baglanan obje ise false;
   bool isOwner;

   // Condition Variable iceren mutex ise true
   bool isCond;

   // Hatalar saklanir   
   int d_errno;
 
};


//==============================================================================
// MutexXn::getErrnoError
//==============================================================================
int MutexXn::getErrnoError() const
{
 return d_errno;
}

#endif // _MUTEXXN_HPP_INCLUDED
