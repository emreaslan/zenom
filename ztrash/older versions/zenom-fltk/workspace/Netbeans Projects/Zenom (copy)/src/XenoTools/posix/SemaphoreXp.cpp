//==============================================================================
// Semaphore.hpp - POSIX shared memory wrapper class.
//
// Author        : 
// Version       : 2.0.01 (Temmuz 2009)
// Compatibility : POSIX, GCC
//==============================================================================

#include "SemaphoreXp.hpp"

//==============================================================================
// SemaphoreXp::SemaphoreXp
//==============================================================================
SemaphoreXp::SemaphoreXp()
{
 d_errno = 0;
 semName = NULL;
}

//==============================================================================
// SemaphoreXp::~SemaphoreXp
//==============================================================================
SemaphoreXp::~SemaphoreXp()
{
 // isimli semaphore
 if(semName)
 {
  close();
  if(isOwner)
   unlink();  
 }
 else
 {
  destroy();
  delete sem;
 }
 delete semName;
}

//==============================================================================
// SemaphoreXp::init
//==============================================================================
int SemaphoreXp::init( int pshared, unsigned value )
{
 if(semName)
  delete semName;
 if(sem)
  delete sem;
 sem = new sem_t;
 if(sem_init ( sem, pshared, value) == -1)
 {
  d_errno = errno;
  return -1;
 }
 return 0;
}

//==============================================================================
// SemaphoreXp::create
//==============================================================================
int SemaphoreXp::create( const char *name, int oflags )
{
 int nlen;
 d_errno = 0;
 
 // Semaphore ismi class degiskenine kopyalanir
 nlen = strlen(name);
 if(semName)
  delete semName;
 semName = new char [nlen+1];
 strncpy(semName, name, nlen);
 semName[nlen] = '\0';
 
 isOwner = true;
 sem = sem_open(semName, oflags); 	
 if( sem == SEM_FAILED )
 {
  d_errno = errno;
  return -1;
 }
 return 0;
}

//==============================================================================
// SemaphoreXp::open
//==============================================================================
int SemaphoreXp::open( const char *name, int oflags )
{
 int nlen;
 d_errno = 0;
 oflags = oflags;
 
 // Semaphore ismi class degiskenine kopyalanir
 nlen = strlen(name);
 if(semName)
  delete semName;
 semName = new char [nlen+1];
 strncpy(semName, name, nlen);
 semName[nlen] = '\0';
 
 isOwner = false;
 sem = sem_open(semName, O_CREAT,NULL,1); 	
 if( sem == SEM_FAILED )
 {
  d_errno = errno;
  return -1;
 }
 return 0;
}

//==============================================================================
// SemaphoreXp::wait
//==============================================================================
int SemaphoreXp::wait()
{
 if( sem_wait(sem) == -1 )
 {
  d_errno = errno;
  return -1;
 }
 return 0;
}

//==============================================================================
// SemaphoreXp::trywait
//==============================================================================
int SemaphoreXp::tryWait()
{
 if( sem_trywait(sem) == -1 )
 {
  d_errno = errno;
  return -1;
 }
 return 0;
}

//==============================================================================
// SemaphoreXp::timedWait
//==============================================================================
int SemaphoreXp::timedWait(const struct timespec * abs_timeout)
{
 if( sem_timedwait(sem, abs_timeout) == -1 )
 {
  d_errno = errno;
  return -1;
 }
 return 0;
}

//==============================================================================
// SemaphoreXp::post
//==============================================================================
int SemaphoreXp::post()
{
 if( sem_wait(sem) == -1 )
 {
  d_errno = errno;
  return -1;
 }
 return 0;
}

//==============================================================================
// SemaphoreXp::getValue
//==============================================================================
int SemaphoreXp::getValue( int *value )
{
 if( sem_getvalue(sem,	value) == -1 )
 {
  d_errno = errno;
  return -1;
 }
 return 0;
}

//==============================================================================
// SemaphoreXp::close
//==============================================================================
int SemaphoreXp::close()
{
 // isimli semaphore kapatabilir.
 if( !semName )
 {
  d_errno = EPERM;
  return -1;
 }
 if( sem_close(sem)  )
 {
  d_errno = errno;
  return -1;
 }
 return 0;
}

//==============================================================================
// SemaphoreXp::destroy
//==============================================================================
int SemaphoreXp::destroy()
{
 // isimsiz semaphore kapatabilir.
 if( semName )
 {
  d_errno = EPERM;
  return -1;
 }
 if( sem_destroy(sem) )
 {
  d_errno = errno;
  return -1;
 }
 return 0;
}

//==============================================================================
// SemaphoreXp::unlink
//==============================================================================
int SemaphoreXp::unlink()
{
 // isimli semaphore ve yaratan baglantiyi koparabilir.
 if( !semName || !isOwner )
 {
  d_errno = EPERM;
  return -1;
 }

 // semophore serbest birakilmadan once kapatilir.
 if( close() )
 {
  d_errno = errno;
  return -1;
 }

 if( sem_unlink(semName) )
 {
  d_errno = errno;
  return -1;
 }
 return 0;
}



















