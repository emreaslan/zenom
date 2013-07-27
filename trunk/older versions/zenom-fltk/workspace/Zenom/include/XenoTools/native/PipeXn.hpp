//==============================================================================
// PipeXn.hpp - Native Pipe services
//
// Author        : 
// Version       : 2.0.01 (Temmuz 2009)
// Compatibility : POSIX, GCC
//==============================================================================

#ifndef _PIPEXN_HPP_INCLUDED
#define _PIPEXN_HPP_INCLUDED
#include <native/pipe.h>


//==============================================================================
// class Pipe
//------------------------------------------------------------------------------
// \brief
// Pipe services
// Message pipe tasklar ve linux processleri arasında dosya I/O işlemleri 
// kullanarak haberleşen iki yönlü iletişim kanalıdır.
// <b>Ornek Program:</b>
//
// \include 
//==============================================================================

#define PIPE_TIMEOUT 10000000000LL  // Varsayilan zaman asimi olarak 10sn

class PipeXn
{
 public:

  // Pipe Constructor
  // Degisken atamalari yapilir.
  PipeXn();

  // PipeXn Destructor
  ~PipeXn();
  
   // PipeXn yaratilir
   //  name       Pipe ismi
   //  minor      Baglanti kurulacak aygit numarası
   //  poolsize   Pipe icin alinacak alan miktari
   //  return 	Basarili olursa 0 , Hata meydana gelirse -1 getirir, 
   //           hata degerine getErrnoError() fonksiyonu ile ulasılabilir.
   int create( const char * name, int minor , size_t poolsize );

   // Pipe silinir ve bekleyen mesajlar silinir.
   //  return 	Basarili olursa 0 , Hata meydana gelirse -1 getirir, 
   //           hata degerine getErrnoError() fonksiyonu ile ulasılabilir.
   int deletePipe();

   
   // Pipe ya mesaj gonderen fonksiyon.
   //  buf       Gondericek olan mesaj
   //  size      Mesaj boyutu
   //  mode      Mesaj gonderim modu
   //  return 	 Gonderilen byte miktarini dondurur, hata olusursa 0 dondurur.
   ssize_t write( const void *buf,size_t size , int mode );

   // Pipe dan mesaj alan fonksiyon.
   //  buf       Alinan mesajin tutulacagi hafiza adresi
   //  size      Alinacak mesajin uzunlugu
   //  PIPE_TIMEOUT   Mesajı almak için beklenilecek clock tick sayısı
   //  return 	 Okunan byte miktarini dondurur, hata olusursa 0 dondurur
   ssize_t read (void *buf,size_t size , RTIME timeout = PIPE_TIMEOUT);

   // Pipe dan bilgi gonderir. Bufferda mesaj icin yeterli yer yoksa mesaji 
   // eksik gonderir
   //  buf       Alinan mesajin tutulacagi hafiza adresi
   //  size      Alinacak mesajin uzunlugu
   //  return 	 Gonderilen byte miktarini dondurur, hata olusursa 0 dondurur.
   ssize_t stream( void *buf, size_t size );

   //  return  En son meydana gelen hatayi getirir.
   int getErrnoError() const;

 private:

   // Pipe degiskeni
   RT_PIPE pipe;

   // Pipe ismi
   char * pipeName;

   // Hatalar saklanir   
   int d_errno;

};


//==============================================================================
// PipeXn::getErrnoError
//==============================================================================
int PipeXn::getErrnoError() const
{
 return d_errno;
}



#endif // _PIPEXN_HPP_INCLUDED
