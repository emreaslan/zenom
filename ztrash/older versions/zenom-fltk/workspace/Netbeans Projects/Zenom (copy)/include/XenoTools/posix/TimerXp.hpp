//==============================================================================
// Timer.hpp - Timer servisleri
//
// Author        : 
// Version       : 2.0.01 (Temmuz 2009)
// Compatibility : POSIX, GCC
//==============================================================================

#ifndef _TIMERXP_HPP_INCLUDED
#define _TIMERXP_HPP_INCLUDED

#include <time.h>
#include <errno.h>


//==============================================================================
// class Timer
//------------------------------------------------------------------------------
// \brief
// Clock ve zamanlama servisleridir. CLOCK_REALTIME ve CLOCK_MONOTONIC olmak
// üzere iki tip clock destekler.  CLOCK_REALTIME, EPOCH'dan beri zaman
// miktarını saklayarak, sistem çekirdek clocku sağlar.  CLOCK_MONOTONIC, mimari 
// bağımlı yüksek çözünürlüklü bir sayaçtır, kısa zaman aralıklarında ölçüm 
// yapmak için uygundur.
// <b>Example Program:</b>
// \include Timer.t.cpp
//==============================================================================

class TimerXp
{
 public:
   // TimerXp constructor
  TimerXp();

   // TimerXp constructor
  ~TimerXp();

   // Timer objesi yaratir.
   //  clockid	Zaman tabani olarak kullanilacak clock; 
   //  evp	Zaman doldugunda yapilacak bildiriler 
   //  return 	Basarili olursa 0 , Hata meydana gelirse -1 getirir, 'errno' degerini  
   //          	getErrnoError() fonksiyonu ile ulasılabilir.
  int create(clockid_t clockId, struct sigevent *evp = NULL );

   //  Overrun sayisini getirir.
   //  return	Overrun sayisini getiririlir, eger deger DELAYTIMER_MAX'i gecerse, 
   //           DELAYTIMER_MAX degeri getirilir. Hata meydana gelirse -1 getirir,
   //           'errno' degerine getErrnoError() fonksiyonu ile ulasılabilir.
  int timerGetOverrun();

   //  Bir Timer baslat veya durdur. 
   //  flags	0 veya TIMER_ABSTIME;
   //  value	Bitis tarihi (member it_value) ve reload degeri (member it_interval)
   //		okunacak struct
   //  ovalue	NULL degilse bir onceki itimerspec struct bilgileri kayit edilir.
   //  return 	Basarili olursa 0 , Hata meydana gelirse -1 getirir, 'errno' degerini  
   //          	getErrnoError() fonksiyonu ile ulasılabilir.
  int timerSetTime( int flags, const struct itimerspec *__restrict__ value, struct itimerspec *__restrict__  ovalue = NULL );


   //  Bitis tarihi (member it_value) ve reload degeri (member it_interval) bulunan 
   //  struct (itimerspec) yapisini getirir. 
   //  value	Bilgilerin kayit edilecegi struct itimerspec.
   //  return 	Basarili olursa 0 , Hata meydana gelirse -1 getirir, 'errno' degerini  
   //          	getErrnoError() fonksiyonu ile ulasılabilir.
  int timerGetTime( struct itimerspec *value);

   //  Belirtilen saatin çözünürlüğünü verir.
   //  clockId	clock degeri (CLOCK_REALTIME veya CLOCK_MONOTONIC)
   //  res   	Cozunurluk degerinin kayit edildigi struct timespec.
   //  return 	Basarili olursa 0 , Hata meydana gelirse -1 getirir, 'errno' degerini  
   //          	getErrnoError() fonksiyonu ile ulasılabilir.
  int clockGetRes( clockid_t clockId, struct timespec*res ); 	

   //  Clock degeri getirir.
   //  clockId	clock degeri (CLOCK_REALTIME veya CLOCK_MONOTONIC)
   //  tp	Clock degerlerinin kayit edildigi struct timespec.
   //  return 	Basarili olursa 0 , Hata meydana gelirse -1 getirir, 'errno' degerini  
   //          	getErrnoError() fonksiyonu ile ulasılabilir.
  int clockGetTime( clockid_t clockId, struct timespec* tp );

   //  return  En son meydana gelen hatayi getirir.
  inline int getErrnoError() const;
   
 private:
   // Timer id
   timer_t timerId;

   // Hatalar saklanir 
   int d_errno; 
};

//==============================================================================
// TimerXp::getErrnoError
//==============================================================================
int TimerXp::getErrnoError() const
{
 return d_errno;
}

#endif // _TIMERXP_HPP_INCLUDED
