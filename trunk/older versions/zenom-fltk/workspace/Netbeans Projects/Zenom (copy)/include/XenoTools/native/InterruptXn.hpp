//==============================================================================
// InterruptXn.hpp - Interrupt Management services
//
// Author        : 
// Version       : 2.0.01 (Temmuz 2009)
// Compatibility : POSIX, GCC
//==============================================================================

#ifndef _INTERRUPTXN_HPP_INCLUDED
#define _INTERRUPTXN_HPP_INCLUDED

#include <native/intr.h>



//==============================================================================
// class Interrupt
//------------------------------------------------------------------------------
// \brief
// NATIVE Interrupt 
// InterruptXn sınıfı, interrupt yönetim sistemi servisleri için arayüzdür.
// Interruptların devre dışı bırakılmasını veya interrupt beklenmesine olanak 
// sağlar.
//==============================================================================

#define INTR_TIMEOUT 10000000000LL  // Varsayilan zaman asimi olarak 10sn

class InterruptXn
{
 public:

  // Interrupt Constructor
  // Degisken atamalari yapilir.
  InterruptXn();

  // Interrupt Destructor
  ~InterruptXn();
  
   // Interrupt yaratilir
   //  name      Interrupt ismi
   //  irq       Donanim interrupt kanali
   //  mode      Interrupt yaratilma modu
   int create(const char * name, unsigned irq, int mode);

   // Var olan Interrupt'a baglanir. 
   //  name     Baglanilacak Interrupt ismi
   //  INTR_TIMEOUT  Baglanmak icin beklenecek zaman
   //  return 	Basarili olursa 0 , Hata meydana gelirse -1 getirir, hata degerine
   //          	getErrnoError() fonksiyonu ile ulasılabilir.
   int bind(const char *name, RTIME timeout = INTR_TIMEOUT);

   // Interrupt gelene kadar bekler
   //  INTR_TIMEOUT  Beklenecek zaman
   //  return 	Basarili olursa interruptın processe pend sayisi, hata meydana
   //           gelirse -1 getirir, hata degerine getErrnoError() fonksiyonu
   //           ile ulasılabilir.
   int wait( RTIME timeout = INTR_TIMEOUT);	 

   // Interrupt'i devreye sokar.
   //  return 	Basarili olursa 0 , Hata meydana gelirse -1 getirir, hata degerini  
   //          	getErrnoError() fonksiyonu ile ulasılabilir.
   int enable();

   // Interrupt'i devre disi birakir.
   //  return 	Basarili olursa 0 , Hata meydana gelirse -1 getirir, hata degerine
   //          	getErrnoError() fonksiyonu ile ulasılabilir.
   int disable();

   // Interrupt siler. Ancak Interrupt yaratan (create) eden obje silebilir. 
   // Aksi takdirde -1 getirir ve EACCES hatasi d_errno degiskenine atanir. 
   //  return 	Basarili olursa 0 , Hata meydana gelirse -1 getirir, hata degerine
   //          	getErrnoError() fonksiyonu ile ulasılabilir.
   int deleteIntr();

   // Interrupt'i serbest birakir. Ancak Interrupt'a baglanan (bind) obje serbest
   // birakabilir. Aksi takdirde -1 getirir ve EACCES hatasi d_errno degiskenine
   // atanir. 
   //  return 	Basarili olursa 0 , Hata meydana gelirse -1 getirir, hata degerine
   //          	getErrnoError() fonksiyonu ile ulasılabilir.
   int unbind();

   // Interrupt bilgilerini info struct icine yazar.
   //  info	Interrupt bilgilerinin yazilacagi struct pointeri  
   //  return 	Basarili olursa 0 , Hata meydana gelirse -1 getirir, hata degerini  
   //          	getErrnoError() fonksiyonu ile ulasılabilir.
  int inquire( RT_INTR_INFO * info );

   //  return  En son meydana gelen hatayi getirir.
  int getErrnoError() const;

 private:

   // Interrupt degiskeni
   RT_INTR intr;

   // Interrupt ismi
   char * intrName;

   // Interrupt'da yalnızca create eden delete yapabilir
   // Bu bilgiyi belirten flag, create eden ise true degilse false
   bool isOwner;

   // Hatalar saklanir   
   int d_errno;
 
};


//==============================================================================
// InterruptXn::getErrnoError
//==============================================================================
int InterruptXn::getErrnoError() const
{
 return d_errno;
}

#endif // _INTERRUPTXN_HPP_INCLUDED
