//==============================================================================
// HeapXn.hpp - Native Heap class.
//
// Author        : 
// Version       : 2.0.01 (Temmuz 2009)
// Compatibility : POSIX, GCC
//==============================================================================

#ifndef _HEAPXN_HPP_INCLUDED
#define _HEAPXN_HPP_INCLUDED

#include <native/heap.h>


//==============================================================================
// class HeapXn
//------------------------------------------------------------------------------
// \brief
// Heap objects.
// HeapXn sınıfı, tasklar için ortak kullanılabilen hafıza alanı oluşturur. 
// Dinamik afıza tahsisi için uygundur. 
// 
// <b>Example Program:</b>
//
// \include HeapXn.t.cpp
//==============================================================================

#define HEAP_TIMEOUT 10000000000LL // Varsayilan zaman asimi olarak 10sn
#define HEAP_MODE_C    H_SHARED     //Heap yaratilma modu

class HeapXn
{
 public:

   // Sadece objenin degiskenlerine atamalar yapilir.
  HeapXn();
   
   // Heap yaratan ise delete, heape baglanan ise unbind edilir.
  ~HeapXn();
  
   // Heap yaratir
   // yapilirsa, o semaphore'a baglanir.
   //  name      Yaratilacak Heap ismi
   //  heapsize  Heap boyutu
   //  HEAP_MODE_C      Heap yaratilma modu
   //  return 	 Basarili olursa null olmayan bir deger, hata meydana gelirse 
   //            NULL getirir, hata degerine getErrnoError() fonksiyonu ile
   //            ulasılabilir.
  void *create(const char *name, int heapsize, int mode = HEAP_MODE_C); 

   // Heap'e baglanir
   // yapilirsa, o semaphore'a baglanir.
   //  name      Yaratilacak Heap ismi
   //  HEAP_TIMEOUT   Beklenecek zaman
   //            Varsayilan olarak TM_INFINITE (sonsuza kadar bekler)
   //  return 	 Basarili olursa null olmayan bir deger, hata meydana gelirse 
   //            NULL getirir, hata degerine getErrnoError() fonksiyonu ile
   //            ulasılabilir.
  void *bind(const char *name, RTIME timeout = HEAP_TIMEOUT);
   
   // Heap'i serbest birakir. Ancak heap'e baglanan (bind) obje serbest birakabilir.
   // Aksi takdirde -1 getirir ve EACCES hatasi d_errno degiskenine atanir. 
   //  return 	Basarili olursa 0 , Hata meydana gelirse -1 getirir, 
   //           hata degerine getErrnoError() fonksiyonu ile ulasılabilir.
  int unbind();
      
   // Heap'i siler. Ancak heap yaratan (create) eden obje silebilir. Aksi takdirde
   // -1 getirir ve EACCES hatasi d_errno degiskenine atanir. 
   //  return 	Basarili olursa 0 , Hata meydana gelirse -1 getirir, 
   //           hata degerine getErrnoError() fonksiyonu ile ulasılabilir.
  int deleteHeap();

   // Heap bilgilerini info struct icine yazar.
   //  info	Heap bilgilerinin yazilacagi struct pointeri  
   //  return 	Basarili olursa 0 , Hata meydana gelirse -1 getirir, 
   //           hata degerine getErrnoError() fonksiyonu ile ulasılabilir.
  int inquire( RT_HEAP_INFO * info );

   //  return  En son meydana gelen hatayi getirir.
  inline int getErrnoError() const;
   
 private:

   // Heap 
  RT_HEAP heap;

   // Heap ismi
  char *heapName;

   // Heap ile elde edilen adres
  void *heapMem;
   
   // Heap yaratan( create ) eden obje ise true, 
   // Heape baglanan obje ise false;
  bool isOwner;
  
   // Hatalarin saklandigi degisken
  int d_errno;
};


//==============================================================================
// HeapXn::getErrnoError
//==============================================================================
int HeapXn::getErrnoError() const
{
 return d_errno;
}

#endif // _HEAPXN_HPP_INCLUDED
