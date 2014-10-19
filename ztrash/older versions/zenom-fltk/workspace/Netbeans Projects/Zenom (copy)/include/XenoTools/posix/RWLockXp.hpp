//==============================================================================
// RWLock.hpp - Reader/Writer lock wrapper class.
//
// Author        : Vilas Kumar Chitrakaran
// Version       : 2.0.01 (Temmuz 2009)
// Compatibility : POSIX, GCC
//==============================================================================

#ifndef _RWLOCKXP_HPP_INCLUDED
#define _RWLOCKXP_HPP_INCLUDED

#include <pthread.h>
#include "ErrnoExceptionXp.hpp"

//==============================================================================
// class RWLockXp
//------------------------------------------------------------------------------
// \brief
//
// RWLock sınıfı, birden fazla threadin paylaştığı bir hafıza alanını, 
// senkronize bir şekilde kullanmalarını sağlar. Okuma ve yazma işlemleri için
// kullanılan kilitleme fonksiyonları ile hafızanın aynı anda sadece bir thread
// tarafından değiştirilmesini sağlar. Bu sayede veri güvenliği de korunur. 
// 
// <b>Ornek Program:</b>
// \include RWLockXp.t.cpp
//==============================================================================

class RWLockXp
{
 public:
  inline RWLockXp();
   // Constructor initializes the lock.
   
  inline ~RWLockXp();
   // Destroys the lock.
   
  inline void readLock();
   // Acquire the shared lock for read access. 
   // If the lock is not available, block until it is.
   
  inline int tryReadLock();
   // Try to acquire the shared lock for read access. 
   // If the lock is not available, return immediately.
   //  return  0 on successful acquisition of lock, else -1

  inline void writeLock();
   // Acquire the shared lock for exclusive write access. 
   // If the lock is not available, block until it is.

  inline int tryWriteLock();
   // Try to acquire the shared lock for exclusive write access. 
   // If the lock is not available, return immediately.
   //  return  0 on successful acquisition of lock, else -1

  inline void unlock();
   // Unlock the shared lock. If the calling thread doesn't own
   // the lock, the behavior of this function is undefined.
   
  //======== END OF INTERFACE ========
 private:
  inline void errorCheck(int code);
   // This will throw an exception on any error.

  pthread_rwlock_t d_rwl;
   // The pthread lock
  
};


//==============================================================================
// RWLockXp::RWLockXp
//==============================================================================
RWLockXp::RWLockXp()
{
 pthread_rwlockattr_t attr;
 errorCheck( pthread_rwlockattr_init(&attr) );
 errorCheck( pthread_rwlockattr_setpshared(&attr, PTHREAD_PROCESS_PRIVATE) );
 errorCheck( pthread_rwlock_init(&d_rwl, &attr) );
 pthread_rwlockattr_destroy(&attr);
}


//==============================================================================
// RWLockXp::~RWLockXp
//==============================================================================
RWLockXp::~RWLockXp()
{
 pthread_rwlock_destroy(&d_rwl);
}


//==============================================================================
// RWLockXp::readLock
//==============================================================================
void RWLockXp::readLock()
{
 errorCheck( pthread_rwlock_rdlock(&d_rwl) );
}


//==============================================================================
// RWLockXp::tryReadLock
//==============================================================================
int RWLockXp::tryReadLock()
{
 int retVal;

 retVal = pthread_rwlock_tryrdlock(&d_rwl);

 if( retVal == 0 )
  return 0;
  
 if( retVal == EAGAIN || retVal == EBUSY ) 
  return -1;
 
 errorCheck(retVal);
 return -1;
}


//==============================================================================
// RWLockXp::writeLock
//==============================================================================
void RWLockXp::writeLock()
{
 errorCheck( pthread_rwlock_wrlock(&d_rwl) );
}


//==============================================================================
// RWLockXp::tryWriteLock
//==============================================================================
int RWLockXp::tryWriteLock()
{
 int retVal;
 retVal = pthread_rwlock_trywrlock(&d_rwl);
 
 if( retVal == 0 )
  return 0;
 
 if( retVal == EAGAIN || retVal == EBUSY ) 
  return -1;
 
 errorCheck(retVal);
 return -1;
}


//==============================================================================
// RWLockXp::unlock
//==============================================================================
void RWLockXp::unlock()
{
 errorCheck( pthread_rwlock_unlock(&d_rwl) );
}


//==============================================================================
// RWLockXp::errorCheck
//==============================================================================
void RWLockXp::errorCheck(int code)
{
 if(code == 0) return;
 throw(ErrnoExceptionXp(code), "[RWLockXp]");
}

#endif // _RWLOCKXP_HPP_INCLUDED
