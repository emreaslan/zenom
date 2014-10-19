//==============================================================================
// EventXn.hpp - Event services
//
// Author        : 
// Version       : 2.0.01 (Temmuz 2009)
// Compatibility : POSIX, GCC
//==============================================================================

#ifndef _EVENTXN_HPP_INCLUDED
#define _EVENTXN_HPP_INCLUDED

#include <native/event.h>


//==============================================================================
// class Event
//------------------------------------------------------------------------------
// \brief
// NATIVE Event 
// Event sinifi, bayraklar yardimiyla obje senkronizasyonu saglar. Xenomai 
// tasklari ve interruptlar event bayraklari ile baska bir taska sinyal 
// yollayabilir. Taskların event sinyalleri beklemesi conjunctive manner 
// (taskin uyanmasi icin tum event sinyallerinin gerekir) veya disjunctive way 
// (taskın uyanması icin event sinyallerinde bir tanesi yeterlidir) seklinde 
// olabilir.
// <b>Ornek Program:</b>
//
// \include EventXn.t.cpp
//==============================================================================

#define EVENT_TIMEOUT 10000000000LL  // Varsayilan zaman asimi olarak 10sn
#define I_MASK  0x0  // Varsayilan event mask ilk degeri
#define EVENT_MODE_C  EV_PRIO  // Varsayilan event yaratılma modu
#define EVENT_MODE_W  EV_ANY  // Varsayilan event bekleme modu

class EventXn
{
 public:

  // Event Constructor
  // Degisken atamalari yapilir.
  EventXn();

  // Event Destructor
  ~EventXn();
  
   // Event yaratilir
   //  name     Event ismi
   //  ivalue   Event mask'in ilk degeri
   //  mode     Event yaratilma modu
   //  return 	Basarili olursa 0 , Hata meydana gelirse -1 getirir, 
   //           hata degerine getErrnoError() fonksiyonu ile ulasılabilir.
   int create(const char * name, unsigned long ivalue = I_MASK, int mode = EVENT_MODE_C);

   // Var olan Event'a baglanir. 
   //  name     Baglanilacak Event ismi
   //  EVENT_TIMEOUT  Baglanmak icin beklenecek zaman
   //  return 	Basarili olursa 0 , Hata meydana gelirse -1 getirir, 
   //           hata degerine getErrnoError() fonksiyonu ile ulasılabilir.
   int bind(const char *name, RTIME timeout = EVENT_TIMEOUT);

   // Event bitleri uyarilana kadar task askiya alinir.
   //  mask     Beklenecek mask bitleri
   //  mask_r   Okunan mask bitleri  
   //  mode     Askiya alma modu
   //           EV_ANY mask bitlerinden bir tanesi set edilirse, tamamlanir
   //           EV_ALL Beklemenin uyarilmasi icin mask bitlerinin tamami set edilmelidir.
   //  EVENT_TIMEOUT  Beklenecek zaman
   //  return 	Basarili olursa 0 , Hata meydana gelirse -1 getirir, 
   //           hata degerine getErrnoError() fonksiyonu ile ulasılabilir.
   int wait(unsigned long mask, unsigned long *	mask_r, int mode = EVENT_MODE_W, RTIME timeout = EVENT_TIMEOUT);	 

   // Event bitlerini atar.
   //  mask     Atanacak bitler
   //  return 	Basarili olursa 0 , Hata meydana gelirse -1 getirir, 
   //           hata degerine getErrnoError() fonksiyonu ile ulasılabilir.
   int signal(unsigned long mask);

   // Event temizler. 
   //  mask     Temizlenecek mask bitleri
   //  mask_r   Mask bitlerinin temizlenmeden onceki degeri 
   //  return 	Basarili olursa 0 , Hata meydana gelirse -1 getirir, 
   //           hata degerine getErrnoError() fonksiyonu ile ulasılabilir.
   int clear(unsigned long mask, unsigned long *mask_r = NULL);

   // Event siler. Ancak event yaratan (create) eden obje silebilir. Aksi takdirde
   // -1 getirir ve EACCES hatasi d_errno degiskenine atanir. 
   //  return 	Basarili olursa 0 , Hata meydana gelirse -1 getirir, 
   //           hata degerine getErrnoError() fonksiyonu ile ulasılabilir.
   int deleteEvent();

   // Event'i serbest birakir. Ancak event'a baglanan (bind) obje serbest birakabilir.
   // Aksi takdirde -1 getirir ve EACCES hatasi d_errno degiskenine atanir. 
   //  return 	Basarili olursa 0 , Hata meydana gelirse -1 getirir, 
   //           hata degerine getErrnoError() fonksiyonu ile ulasılabilir.
   int unbind();

   // Event bilgilerini info struct icine yazar.
   //  info	Event bilgilerinin yazilacagi struct pointeri  
   //  return 	Basarili olursa 0 , Hata meydana gelirse -1 getirir, 
   //           hata degerine getErrnoError() fonksiyonu ile ulasılabilir.
  int inquire( RT_EVENT_INFO * info );

   //  return  En son meydana gelen hatayi getirir.
  int getErrnoError() const;

 private:

   // Event degiskeni
   RT_EVENT event;

   // Event ismi
   char * eventName;

   // Event'da yalnızca create eden delete yapabilir
   // Bu bilgiyi belirten flag, create eden ise true degilse false
   bool isOwner;

   // Hatalar saklanir   
   int d_errno;
 
};


//==============================================================================
// Event::getErrnoError
//==============================================================================
int EventXn::getErrnoError() const
{
 return d_errno;
}

#endif // _EVENTXN_HPP_INCLUDED
