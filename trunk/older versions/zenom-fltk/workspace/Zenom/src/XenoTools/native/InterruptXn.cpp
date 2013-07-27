//==============================================================================
// InterruptXn.hpp - Interrupt Management services
//
// Author        : 
// Version       : 2.0.01 (Temmuz 2009)
// Compatibility : POSIX, GCC
//==============================================================================

#include "InterruptXn.hpp"

//==============================================================================
// InterruptXn::InterruptXn
//==============================================================================
InterruptXn::InterruptXn()
{
 isOwner = false;
 d_errno = 0;
 intrName = NULL;
}

//==============================================================================
// InterruptXn::~InterruptXn
//==============================================================================
InterruptXn::~InterruptXn()
{
 if( isOwner )
  deleteIntr();
 else
  unbind();
 
 if(intrName)
  delete [] intrName;

}

//==============================================================================
// InterruptXn::create
//==============================================================================
int InterruptXn::create( const char * name, unsigned irq, int mode)
{
 int nlen;
 int err;	//Hata denetim
 
 // Isim kopyalanir.
 nlen = strlen(name);
 if(intrName)
  delete [] intrName;
 intrName = new char [nlen+1];
 strncpy(intrName, name, nlen);
 intrName[nlen] = '\0';

 isOwner = true;

 // intr yaratilir
 if( (err = rt_intr_create( &intr, intrName, irq, mode )) )
 {
  d_errno = -err;
  return -1;
 }

 return 0;
}

//==============================================================================
// InterruptXn::bind
//==============================================================================
int InterruptXn::bind(const char *name, RTIME timeout)
{
 int nlen;
 int err;	//Hata denetim
 
 // Isim kopyalanir.
 nlen = strlen(name);
 if(intrName)
  delete [] intrName;
 intrName = new char [nlen+1];
 strncpy(intrName, name, nlen);
 intrName[nlen] = '\0';

 isOwner = false;

 // intra baglanilir
 if( (err = rt_intr_bind( &intr, intrName, timeout )) )
 {
  d_errno = -err;
  return -1;
 }

 return 0;
}

//==============================================================================
// InterruptXn::wait
//==============================================================================
int InterruptXn::wait( RTIME timeout)
{
 int err;	//Hata denetim

 if( (err = rt_intr_wait(&intr, timeout)) )
 {
  d_errno = -err;
  return -1;
 }
 return 0;
}

//==============================================================================
// InterruptXn::enable
//==============================================================================
int InterruptXn::enable()
{
 int err;	//Hata denetim

 if( (err = rt_intr_enable(&intr)) )
 {
  d_errno = -err;
  return -1;
 }
 return 0;
}

//==============================================================================
// InterruptXn::disable
//==============================================================================
int InterruptXn::disable()
{
 int err;	//Hata denetim

 if( (err = rt_intr_disable(&intr)) )
 {
  d_errno = -err;
  return -1;
 }
 return 0;
}

//==============================================================================
// InterruptXn::deleteintr
//==============================================================================
int InterruptXn::deleteIntr( )
{
 int err;	//Hata denetim

 // intr yaratan nesne degil ise intr'i silemez
 if(!isOwner)
 {
  d_errno = EACCES;
  return -1;
 }

 // intr silinir.
 if( (err = rt_intr_delete(&intr)) )
 {
  d_errno = -err;
  return -1;
 }

 isOwner = false;
 d_errno = 0;
 return 0;
}

//==============================================================================
// InterruptXn::unbind
//==============================================================================
int InterruptXn::unbind( )
{
 int err;	//Hata denetim

 // intr'a baglanan nesne degil ise intr'i serbest birakamaz.
 if(isOwner)
 {
  d_errno = EACCES;
  return -1;
 }

 // intr silinir.
 if( (err = rt_intr_unbind(&intr)) )
 {
  d_errno = -err;
  return -1;
 }

 d_errno = 0;
 return 0;
}

//==============================================================================
// InterruptXn::inquire
//==============================================================================
int InterruptXn::inquire( RT_INTR_INFO * info )
{
 int err;	//Hata denetim

 if( (err = rt_intr_inquire(&intr, info)) )
 {
  d_errno = -err;
  return -1;
 }
 return 0;
}


