//==============================================================================
// AlarmXn.hpp - Alarm services
//
// Author        : 
// Version       : 2.0.01 (Temmuz 2009)
// Compatibility : POSIX, GCC
//==============================================================================

#ifndef _ALARMXN_HPP_INCLUDED
#define _ALARMXN_HPP_INCLUDED

#include <native/alarm.h>


//==============================================================================
// class Alarm
//------------------------------------------------------------------------------
// \brief
// NATIVE Alarm 
// Alarm sınıfı, xenomai tasklarının belirlenen bir gecikme süresi geçikten 
// sonra çalışmasını sağlar. Alarm tek vuruş veya periyodik vuruşlar olabilir.
// <b>Ornek Program:</b>
//
// \include AlarmXn.t.cpp
//==============================================================================

class AlarmXn
{
 public:

  // Alarm Constructor
  // Degisken atamalari yapilir.
  AlarmXn();

  // Alarm Destructor
  ~AlarmXn();
  
   // Alarm yaratilir
   //  name      Alarm ismi
   int create(const char * name);

   // Alarm kurulur.
   //  value    Alarm suresi
   //  interval Alarm vurulduktan sonra, kurulacak sure. TM_INFINITE girilirse,
   //           alarm suresi dolduktan sonra bir daha vurus yapmaz.
   //  return 	Basarili olursa 0 , Hata meydana gelirse -1 getirir, 
   //           hata degerine getErrnoError() fonksiyonu ile ulasılabilir.
   int start( RTIME value, RTIME interval);	 

   // Alarm'i durdurur.
   //  return 	Basarili olursa 0 , Hata meydana gelirse -1 getirir, 
   //           hata degerine getErrnoError() fonksiyonu ile ulasılabilir.
   int stop();

   // Alarm vurulana kadar bekler.
   //  return 	Basarili olursa 0 , Hata meydana gelirse -1 getirir, 
   //           hata degerine getErrnoError() fonksiyonu ile ulasılabilir.
   int wait();

   // Alarm siler. 
   //  return 	Basarili olursa 0 , Hata meydana gelirse -1 getirir, 
   //           hata degerine getErrnoError() fonksiyonu ile ulasılabilir.
   int deleteAlarm();

   // Alarm bilgilerini info struct icine yazar.
   //  info	Alarm bilgilerinin yazilacagi struct pointeri  
   //  return 	Basarili olursa 0 , Hata meydana gelirse -1 getirir, 
   //           hata degerine getErrnoError() fonksiyonu ile ulasılabilir.
  int inquire( RT_ALARM_INFO * info );

   //  return  En son meydana gelen hatayi getirir.
  int getErrnoError() const;

 private:

   // Alarm degiskeni
   RT_ALARM alarm;

   // Alarm ismi
   char * alarmName;

   // Hatalar saklanir   
   int d_errno;
 
};


//==============================================================================
// AlarmXn::getErrnoError
//==============================================================================
int AlarmXn::getErrnoError() const
{
 return d_errno;
}

#endif // _ALARMXN_HPP_INCLUDED
