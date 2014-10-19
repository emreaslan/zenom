//==============================================================================
// MutexXn.hpp - Mutual Exclusion object
//             - Condition Variable object
//
// Author        : 
// Version       : 2.0.01 (Temmuz 2009)
// Compatibility : POSIX, GCC
//==============================================================================

#include "MutexXn.hpp"

//==============================================================================
// MutexXn::MutexXn
//==============================================================================
MutexXn::MutexXn()
{
 isOwner = false;
 isCond = false;
 d_errno = 0;
 mutexName = NULL;
}

//==============================================================================
// MutexXn::~MutexXn
//==============================================================================
MutexXn::~MutexXn()
{
 if( isOwner )
  deleteMutex();
 else
  unbind();
 
 if(mutexName)
  delete [] mutexName;

 if(condName)
  delete [] condName;

}

//==============================================================================
// MutexXn::create
//==============================================================================
int MutexXn::create(const char * mName, const char * cName )
{
 int nlen;
 int err;	//Hata denetim
 
 // Isim kopyalanir.
 nlen = strlen(mName);
 if(mutexName)
  delete [] mutexName;
 mutexName = new char [nlen+1];
 strncpy(mutexName, mName, nlen);
 mutexName[nlen] = '\0';

 isOwner = true;

 // Mutex yaratilir
 if( (err = rt_mutex_create( &mutex, mutexName )) )
 {
  d_errno = -err;
  return -1;
 }

 // Condition Variable ismi set edilmis ise condition variable
 // objesi yaratilir.
 if( cName )
 {
  nlen = strlen(cName);
  delete [] condName;
  condName = new char [nlen+1];
  strncpy(condName, cName, nlen);
  condName[nlen] = '\0';
  // Condition Variable yaratilir
  if( (err = rt_cond_create( &cond, condName )) )
  {
   d_errno = -err;
   return -1;
  }
  isCond = true;
 }

 return 0;
}

//==============================================================================
// MutexXn::bind
//==============================================================================
int MutexXn::bind(const char *mName, RTIME timeout, const char * cName)
{
 int nlen;
 int err;	//Hata denetim
 
 // Isim kopyalanir.
 nlen = strlen(mName);
 if(mutexName)
  delete [] mutexName;
 mutexName = new char [nlen+1];
 strncpy(mutexName, mName, nlen);
 mutexName[nlen] = '\0';

 isOwner = false;

 // Mutexe baglanilir
 if( (err = rt_mutex_bind( &mutex, mutexName, timeout )) )
 {
  d_errno = -err;
  return -1;
 }

  // Condition Variable ismi set edilmis ise condition variable
 // objesine baglanilir.
 if( cName )
 {
  nlen = strlen(cName);
  delete [] condName;
  condName = new char [nlen+1];
  strncpy(condName, cName, nlen);
  condName[nlen] = '\0';
  // Condition Variable'a baglanilir.
  if( (err = rt_cond_bind( &cond, condName, timeout )) )
  {
   d_errno = -err;
   return -1;
  }
  isCond = true;
 }

 return 0;
}

//==============================================================================
// MutexXn::acquire
//==============================================================================
int MutexXn::acquire(RTIME timeout)
{
 int err;	//Hata denetim

 if( (err = rt_mutex_acquire(&mutex, timeout)) )
 {
  d_errno = -err;
  return -1;
 }
 return 0;
}

//==============================================================================
// MutexXn::release
//==============================================================================
int MutexXn::release()
{
 int err;	//Hata denetim

 if( (err = rt_mutex_release(&mutex)) )
 {
  d_errno = -err;
  return -1;
 }
 return 0;
}

//==============================================================================
// MutexXn::condSignal
//==============================================================================
int MutexXn::condSignal()
{
 int err;	//Hata denetim

 if( (err = rt_cond_signal(&cond)) )
 {
  d_errno = -err;
  return -1;
 }
 return 0;
}

//==============================================================================
// MutexXn::condBroadcast
//==============================================================================
int MutexXn::condBroadcast()
{
 int err;	//Hata denetim

 if( (err = rt_cond_broadcast(&cond)) )
 {
  d_errno = -err;
  return -1;
 }
 return 0;
}

//==============================================================================
// MutexXn::condWait
//==============================================================================
int MutexXn::condWait(RTIME timeout)
{
 int err;	//Hata denetim

 if( (err = rt_cond_wait(&cond,&mutex,timeout)) )
 {
  d_errno = -err;
  return -1;
 }
 return 0;
}

//==============================================================================
// MutexXn::deleteMutex
//==============================================================================
int MutexXn::deleteMutex()
{
 int err;	//Hata denetim

 // Mutex yaratan nesne degil ise semaphore'u silemez
 if(!isOwner)
 {
  d_errno = EACCES;
  return -1;
 }

 // Mutex silinir.
 if( (err = rt_mutex_delete(&mutex)) )
 {
  d_errno = -err;
  return -1;
 }

 // Condition Variable yaratilmis ise silinir.
 if(isCond)
 {
  // Condition Variable silinir.
  if( (err = rt_cond_delete(&cond)) )
  {
   d_errno = -err;
   return -1;
  }
 }

 isOwner = false;
 d_errno = 0;
 return 0;
}

//==============================================================================
// MutexXn::unbind
//==============================================================================
int MutexXn::unbind( )
{
 int err;	//Hata denetim

 // Mutex'e baglanan nesne degil ise Mutex'i serbest birakamaz.
 if(isOwner)
 {
  d_errno = EACCES;
  return -1;
 }

 // Mutex serbest birakilir.
 if( (err = rt_mutex_unbind(&mutex)) )
 {
  d_errno = -err;
  return -1;
 }

 // Condition Variable yaratilmis ise serbest birakilir.
 if(isCond)
 {
  if( (err = rt_cond_unbind(&cond)) )
  {
   d_errno = -err;
   return -1;
  }
 }

 d_errno = 0;
 return 0;
}

//==============================================================================
// MutexXn::inquire
//==============================================================================
int MutexXn::inquire( RT_MUTEX_INFO * info )
{
 int err;	//Hata denetim

 if( (err = rt_mutex_inquire(&mutex, info)) )
 {
  d_errno = -err;
  return -1;
 }
 return 0;
}

//==============================================================================
// MutexXn::condInquire
//==============================================================================
int MutexXn::condInquire( RT_COND_INFO * info )
{
 int err;	//Hata denetim

 if( (err = rt_cond_inquire(&cond, info)) )
 {
  d_errno = -err;
  return -1;
 }
 return 0;
}


