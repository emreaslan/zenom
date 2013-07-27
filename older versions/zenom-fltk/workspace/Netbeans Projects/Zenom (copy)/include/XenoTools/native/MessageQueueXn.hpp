//==============================================================================
// MessageQueueXn.hpp - Native MessageQueue services
//
// Author        : 
// Version       : 2.0.01 (Temmuz 2009)
// Compatibility : POSIX, GCC
//==============================================================================

#ifndef _MESSAGEQUEUEXN_HPP_INCLUDED
#define _MESSAGEQUEUEXN_HPP_INCLUDED
#include <native/queue.h>


//==============================================================================
// class MessageQueue
//------------------------------------------------------------------------------
// \brief
// MessageQueue services
// MessageQueue sınıfı, processlerin iletisim kurmasını sağlar.Processler 
// MessageQueue kullanarak mesaj gönderip, kuyruktan mesaj alırlar.
// MessageQueue bir process tarafından oluşturulur, diğer processler
// oluşturulan kuyruğa bağlanır. 
// 
// <b>Ornek Program:</b>
//
// \include MessageQueueXn.t.cpp
//==============================================================================

#define MQ_TIMEOUT 10000000000LL  // Varsayilan zaman asimi olarak 10sn

class MessageQueueXn
{
 public:

  // MessageQueue Constructor
  // Degisken atamalari yapilir.
  MessageQueueXn();

  // MessageQueueXn Destructor
  ~MessageQueueXn();
  
   // MessageQueueXn yaratilir
   //  name       MessageQueue ismi
   //  poolsize   MessageQueue icin alinacak alan miktari
   //  qlimit     MessageQueuede ayni anda bulunabilecek maksimum mesaj sayisi
   //  mode       MessageQueue olusturma modu
   //  return 	  Basarili olursa 0 , Hata meydana gelirse -1 getirir, 'errno' 
   //             degerini getErrnoError() fonksiyonu ile ulasılabilir.
   int create( const char * name, size_t poolsize, size_t qlimit, int mode );

   // MessageQueue silinir ve bekleyen butun processler serbest birakilir.
   //   
   //  return 	  Basarili olursa 0 , Hata meydana gelirse -1 getirir, 'errno' 
   //             degerini getErrnoError() fonksiyonu ile ulasılabilir.  
   int deleteQueue();

   // MessageQueue icin hafizadan alan alir.
   //  size       Hafizadan alinacak alan miktari
   //  return 	  Basarili olursa alinan hafizanin pointer degerini,
   //             Hata meydana gelirse NULL getirir
   void* alloc( size_t size );

   // Hafizadan alinan alani geri veren fonksiyon.
   //  buf       geri verilmek istenen hafiza alanini gosteren pointer.
   //  return    Basarili olursa 0 , Hata meydana gelirse -1 getirir, 'errno' 
   //            degerini getErrnoError() fonksiyonu ile ulasılabilir.
   int free ( void *buf );

   // MessageQueue ya mesaj gonderen fonksiyon.
   //  mbuf      Gondericek olan mesaj
   //  size      Mesaj boyutu
   //  mode      Mesaj gonderim modu
   //  return 	 Basarili olursa 0 , Hata meydana gelirse -1 getirir, 'errno'
   //            degerini getErrnoError() fonksiyonu ile ulasılabilir.
   int send( void *mbuf,size_t size , int mode );

   // MessageQueue ya mesaj gonderen fonksiyon.
   //  buf       Gondericek olan mesaj
   //  size      Mesaj boyutu
   //  mode      Mesaj gonderim modu
   //  return 	 Basarili olursa 0 , Hata meydana gelirse -1 getirir, 'errno' 
   //            degerini getErrnoError() fonksiyonu ile ulasılabilir.
   int write( const void *buf,size_t size , int mode );

   // MessageQueue dan mesaj alan fonksiyon.
   //  buf       Alinan mesajin tutulacagi hafiza adresi
   //  MQ_TIMEOUT   Mesaji almak icin beklenilecek maksimum sure
   //  return 	 Basarili olursa 0 , Hata meydana gelirse -1 getirir, 'errno' 
   //            degerini getErrnoError() fonksiyonu ile ulasılabilir.
   size_t receive(void **bufp,RTIME timeout = MQ_TIMEOUT);
  
   // MessageQueue dan mesaj alan fonksiyon.
   //  buf       Alinan mesajin tutulacagi hafiza adresi
   //  size      Alinacak mesajin uzunlugu
   //  MQ_TIMEOUT   Mesaji almak icin beklenilecek maksimum sure
   //  return 	 Okunan byte miktarini dondurur, hata olusursa 0 dondurur
   size_t read (void *buf,size_t size , RTIME timeout = MQ_TIMEOUT);

   // MessageQueue bilgilerini info struct icine yazar.
   //  info	MessageQueue bilgilerinin yazilacagi struct pointeri  
   //  return 	Basarili olursa 0 , Hata meydana gelirse -1 getirir, hata 
   //           degerini getErrnoError() fonksiyonu ile ulasılabilir.
   int inquire( RT_QUEUE_INFO * info );



   // Olusturulmus bir MessageQueue 'ye baglanmaya yarar
   //  name	Baglanilacak MessageQueue'nun ismi
   //  MQ_TIMEOUT  Baglanma icin maksimum bekleme suresi  
   //  return 	Basarili olursa 0 , Hata meydana gelirse -1 getirir, hata 
   //           degerini getErrnoError() fonksiyonu ile ulasılabilir.
   int bind( const char *name , RTIME timeout = MQ_TIMEOUT);


   // Bind ile baglanilan MessageQueue ile baglantiyi keser
   //  return 	Basarili olursa 0 , Hata meydana gelirse -1 getirir, hata 
   //           degerini getErrnoError() fonksiyonu ile ulasılabilir.
   int unbind();

   //  return  En son meydana gelen hatayi getirir.
   inline int getErrnoError() const { return d_errno; }


 private:

   // MessageQueue degiskeni
   RT_QUEUE queue;

   // MessageQueue ismi
   char * queueName;

   // MessageQueue yalnızca create eden tarafindan unlink edilebilir
   // Bu bilgiyi belirten flag, create eden ise true degilse false
   bool isOwner;

   // Hatalar saklanir   
   int d_errno;

};


#endif // _MESSAGEQUEUEXN_HPP_INCLUDED
