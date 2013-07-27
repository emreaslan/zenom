//==============================================================================
// AlarmXn.hpp - Native Alarm services
//
// Author        : 
// Version       : 2.0.01 (Temmuz 2009)
// Compatibility : POSIX, GCC
//==============================================================================

#include "AlarmXn.hpp"

//==============================================================================
// AlarmXn::AlarmXn
//==============================================================================
AlarmXn::AlarmXn()
{
 d_errno = 0;
 alarmName = NULL;
}

//==============================================================================
// AlarmXn::~AlarmXn
//==============================================================================
AlarmXn::~AlarmXn()
{
 deleteAlarm();

 if(alarmName)
  delete [] alarmName;
}

//==============================================================================
// AlarmXn::create
//==============================================================================
int AlarmXn::create( const char * name )
{
 int nlen;
 int err;	//Hata denetim
 
 // Isim kopyalanir.
 nlen = strlen(name);
 if(alarmName)
 {
  delete [] alarmName;
 }
 alarmName = new char [nlen+1];
 strncpy(alarmName, name, nlen);
 alarmName[nlen] = '\0';

 // Alarm yaratilir
 if( (err = rt_alarm_create(&alarm, alarmName)) )
 {
  d_errno = -err;
  return -1;
 }

 return 0;
}

//==============================================================================
// AlarmXn::start
//==============================================================================
int AlarmXn::start( RTIME value, RTIME interval)
{
 int err;	//Hata denetim

 if( (err = rt_alarm_start(&alarm, value, interval)) )
 {
  d_errno = -err;
  return -1;
 }
 return 0;
}

//==============================================================================
// AlarmXn::stop
//==============================================================================
int AlarmXn::stop()
{
 int err;	//Hata denetim

 if( (err = rt_alarm_stop(&alarm)) )
 {
  d_errno = -err;
  return -1;
 }
 return 0;
}

//==============================================================================
// AlarmXn::wait
//==============================================================================
int AlarmXn::wait()
{
 int err;	//Hata denetim

 if( (err = rt_alarm_wait(&alarm)) )
 {
  d_errno = -err;
  return -1;
 }
 return 0;
}

//==============================================================================
// AlarmXn::deleteAlarm
//==============================================================================
int AlarmXn::deleteAlarm( )
{
 int err;	//Hata denetim

 // Alarm silinir.
 if( (err = rt_alarm_delete(&alarm)) )
 {
  d_errno = -err;
  return -1;
 }

 d_errno = 0;
 return 0;
}

//==============================================================================
// AlarmXn::inquire
//==============================================================================
int AlarmXn::inquire( RT_ALARM_INFO * info )
{
 int err;	//Hata denetim

 if( (err = rt_alarm_inquire(&alarm, info)) )
 {
  d_errno = -err;
  return -1;
 }
 return 0;
}


