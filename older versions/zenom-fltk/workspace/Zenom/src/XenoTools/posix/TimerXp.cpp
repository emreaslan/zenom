//==============================================================================
// Timer.cpp - Timer servisleri
//
// Author        : 
// Version       : 2.0.01 (Temmuz 2009)
// Compatibility : POSIX, GCC
//==============================================================================

#include "TimerXp.hpp"
#include <iostream>
using namespace std;

//==============================================================================
// TimerXp::TimerXp
//==============================================================================
TimerXp::TimerXp()
{
 d_errno = 0;
}


//==============================================================================
// TimerXp::~TimerXp
//==============================================================================
TimerXp::~TimerXp()
{
 if( timer_delete(timerId) )
 {
  d_errno = errno;
 }
}

//==============================================================================
// TimerXp::create
//==============================================================================
int TimerXp::create(clockid_t clockId, struct sigevent *evp)
{

 if(timer_create( clockId, evp, &timerId ) == -1 )
 {
  d_errno = errno;
  return -1;
 } 	
 
 return 0;
}

//==============================================================================
// TimerXp::timerGetOverrun
//==============================================================================
int TimerXp::timerGetOverrun()
{
 int overrun;
 overrun = timer_getoverrun(timerId); 
 if( overrun == -1)
 {
  d_errno = errno;
  return -1;
 }

 return overrun; 
}

//==============================================================================
// TimerXp::timerGetTime
//==============================================================================
int TimerXp::timerGetTime(struct itimerspec* value)
{
 if( timer_gettime(timerId,value) == -1 )
 {
  d_errno = errno;
  return -1;
 }
 return 0;
}

//==============================================================================
// TimerXp::timerSetTime
//==============================================================================
int TimerXp::timerSetTime( int flags, const struct itimerspec *__restrict__ value, struct itimerspec *__restrict__  ovalue )
{
 if( timer_settime( timerId, flags, value, ovalue ) == -1 )
 {
  d_errno = errno;
  return -1;
 } 
 return 0;
}

//==============================================================================
// TimerXp::clockGetRes
//==============================================================================
int TimerXp::clockGetRes( clockid_t clockId, struct timespec* res )
{
 if( clock_getres(clockId,res) == -1 )
 {
  d_errno = errno;
  return -1;
 }
 return 0;
}

//==============================================================================
// TimerXp::clockGetTime
//==============================================================================
int TimerXp::clockGetTime( clockid_t clockId, struct timespec* tp )
{
 if( clock_gettime(clockId,tp) == -1 )
 {
  d_errno = errno;
  return -1;
 }
 return 0;
}



