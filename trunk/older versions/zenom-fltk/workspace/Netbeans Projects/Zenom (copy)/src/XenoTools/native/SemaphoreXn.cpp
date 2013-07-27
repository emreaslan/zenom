//==============================================================================
// SemaphoreXn.hpp - Native Semaphores services
//
// Author        : 
// Version       : 2.0.01 (Temmuz 2009)
// Compatibility : POSIX, GCC
//==============================================================================

#include "SemaphoreXn.hpp"

//==============================================================================
// SemaphoreXn::SemaphoreXn
//==============================================================================
SemaphoreXn::SemaphoreXn()
{
 isOwner = false;
 d_errno = 0;
 semName = NULL;
}

//==============================================================================
// SemaphoreXn::~SemaphoreXn
//==============================================================================
SemaphoreXn::~SemaphoreXn()
{
 if( isOwner )
  deleteSem();
 else
  unbind();
 
 if(semName)
  delete [] semName;

}

//==============================================================================
// SemaphoreXp::create
//==============================================================================
int SemaphoreXn::create( const char * name, unsigned long icount, int mode)
{
 int nlen;
 int err;	//Hata denetim
 
 // Isim kopyalanir.
 nlen = strlen(name);
 if(semName)
  delete [] semName;
 semName = new char [nlen+1];
 strncpy(semName, name, nlen);
 semName[nlen] = '\0';

 isOwner = true;

 // Semaphore yaratilir
 if( (err = rt_sem_create( &sem, semName, icount, mode )) )
 {
  d_errno = -err;
  return -1;
 }

 return 0;
}

//==============================================================================
// SemaphoreXn::bind
//==============================================================================
int SemaphoreXn::bind(const char *name, RTIME timeout)
{
 int nlen;
 int err;	//Hata denetim
 
 // Isim kopyalanir.
 nlen = strlen(name);
 if(semName)
  delete [] semName;
 semName = new char [nlen+1];
 strncpy(semName, name, nlen);
 semName[nlen] = '\0';

 isOwner = false;

 // Semaphore yaratilir
 if( (err = rt_sem_bind( &sem, semName, timeout )) )
 {
  d_errno = -err;
  return -1;
 }

 return 0;
}

//==============================================================================
// SemaphoreXn::p
//==============================================================================
int SemaphoreXn::p( RTIME timeout )
{
 int err;	//Hata denetim

 if( (err = rt_sem_p(&sem, timeout)) )
 {
  d_errno = -err;
  return -1;
 }
 return 0;
}

//==============================================================================
// SemaphoreXn::v
//==============================================================================
int SemaphoreXn::v()
{
 int err;	//Hata denetim

 if( (err = rt_sem_v(&sem)) )
 {
  d_errno = -err;
  return -1;
 }
 return 0;
}

//==============================================================================
// SemaphoreXn::broadcast
//==============================================================================
int SemaphoreXn::broadcast()
{
 int err;	//Hata denetim

 if( (err = rt_sem_broadcast(&sem)) )
 {
  d_errno = -err;
  return -1;
 }
 return 0;
}

//==============================================================================
// SemaphoreXn::deleteSem
//==============================================================================
int SemaphoreXn::deleteSem( )
{
 int err;	//Hata denetim

 // Semaphore yaratan nesne degil ise semaphore'u silemez
 if(!isOwner)
 {
  d_errno = EACCES;
  return -1;
 }

 // Semaphore silinir.
 if( (err = rt_sem_delete(&sem)) )
 {
  d_errno = -err;
  return -1;
 }

 isOwner = false;
 d_errno = 0;
 return 0;
}

//==============================================================================
// SemaphoreXp::unbind
//==============================================================================
int SemaphoreXn::unbind( )
{
 int err;	//Hata denetim

 // Semaphore'a baglanan nesne degil ise semaphore'u serbest birakamaz.
 if(isOwner)
 {
  d_errno = EACCES;
  return -1;
 }

 // Semaphore silinir.
 if( (err = rt_sem_unbind(&sem)) )
 {
  d_errno = -err;
  return -1;
 }

 d_errno = 0;
 return 0;
}

//==============================================================================
// SemaphoreXp::inquire
//==============================================================================
int SemaphoreXn::inquire( RT_SEM_INFO * info )
{
 int err;	//Hata denetim

 if( (err = rt_sem_inquire(&sem, info)) )
 {
  d_errno = -err;
  return -1;
 }
 return 0;
}


