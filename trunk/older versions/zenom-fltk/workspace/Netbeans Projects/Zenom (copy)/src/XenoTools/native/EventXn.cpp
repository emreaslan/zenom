//==============================================================================
// EventXn.hpp - Native Event services
//
// Author        : 
// Version       : 2.0.01 (Temmuz 2009)
// Compatibility : POSIX, GCC
//==============================================================================

#include "EventXn.hpp"

//==============================================================================
// EventXn::EventXn
//==============================================================================
EventXn::EventXn()
{
 isOwner = false;
 d_errno = 0;
 eventName = NULL;
}

//==============================================================================
// EventXn::~EventXn
//==============================================================================
EventXn::~EventXn()
{
 if( isOwner )
  deleteEvent();
 else
  unbind();
 
 if(eventName)
  delete [] eventName;

}

//==============================================================================
// EventXn::create
//==============================================================================
int EventXn::create( const char * name, unsigned long ivalue, int mode)
{
 int nlen;
 int err;	//Hata denetim
 
 // Isim kopyalanir.
 nlen = strlen(name);
 if(eventName)
  delete [] eventName;
 eventName = new char [nlen+1];
 strncpy(eventName, name, nlen);
 eventName[nlen] = '\0';

 isOwner = true;

 // Event yaratilir
 if( (err = rt_event_create( &event, eventName, ivalue, mode )) )
 {
  d_errno = -err;
  return -1;
 }

 return 0;
}

//==============================================================================
// EventXn::bind
//==============================================================================
int EventXn::bind(const char *name, RTIME timeout)
{
 int nlen;
 int err;	//Hata denetim
 
 // Isim kopyalanir.
 nlen = strlen(name);
 if(eventName)
  delete [] eventName;
 eventName = new char [nlen+1];
 strncpy(eventName, name, nlen);
 eventName[nlen] = '\0';

 isOwner = false;

 // Eventa baglanilir
 if( (err = rt_event_bind( &event, eventName, timeout )) )
 {
  d_errno = -err;
  return -1;
 }

 return 0;
}

//==============================================================================
// EventXn::wait
//==============================================================================
int EventXn::wait(unsigned long mask, unsigned long * mask_r, int mode, RTIME timeout)
{
 int err;	//Hata denetim

 if( (err = rt_event_wait(&event, mask, mask_r, mode, timeout)) )
 {
  d_errno = -err;
  return -1;
 }
 return 0;
}

//==============================================================================
// EventXn::signal
//==============================================================================
int EventXn::signal(unsigned long mask)
{
 int err;	//Hata denetim

 if( (err = rt_event_signal(&event, mask)) )
 {
  d_errno = -err;
  return -1;
 }
 return 0;
}

//==============================================================================
// EventXn::clear
//==============================================================================
int EventXn::clear(unsigned long mask, unsigned long *mask_r)
{
 int err;	//Hata denetim

 if( (err = rt_event_clear(&event, mask, mask_r)) )
 {
  d_errno = -err;
  return -1;
 }
 return 0;
}

//==============================================================================
// EventXn::deleteEvent
//==============================================================================
int EventXn::deleteEvent( )
{
 int err;	//Hata denetim

 // Event yaratan nesne degil ise event'i silemez
 if(!isOwner)
 {
  d_errno = EACCES;
  return -1;
 }

 // Event silinir.
 if( (err = rt_event_delete(&event)) )
 {
  d_errno = -err;
  return -1;
 }

 isOwner = false;
 d_errno = 0;
 return 0;
}

//==============================================================================
// EventXn::unbind
//==============================================================================
int EventXn::unbind( )
{
 int err;	//Hata denetim

 // Event'a baglanan nesne degil ise Event'i serbest birakamaz.
 if(isOwner)
 {
  d_errno = EACCES;
  return -1;
 }

 // Event silinir.
 if( (err = rt_event_unbind(&event)) )
 {
  d_errno = -err;
  return -1;
 }

 d_errno = 0;
 return 0;
}

//==============================================================================
// EventXn::inquire
//==============================================================================
int EventXn::inquire( RT_EVENT_INFO * info )
{
 int err;	//Hata denetim

 if( (err = rt_event_inquire(&event, info)) )
 {
  d_errno = -err;
  return -1;
 }
 return 0;
}


