//==============================================================================
// Interrupt.hpp - POSIX shared memory wrapper class.
//
// Author        : 
// Version       : 2.0.01 (Temmuz 2009)
// Compatibility : POSIX, GCC
//==============================================================================

#include "InterruptXp.hpp"


InterruptXp::InterruptXp()
{
}

InterruptXp::~InterruptXp()
{
}

//==============================================================================
// InterruptXp::attach
//==============================================================================
int InterruptXp::attach(unsigned irq,int mode )
{
 if( pthread_intr_attach_np( &inter , irq , mode ) == -1 )
 {
   d_errno = errno ;
   return -1;
  }

 return 0;
 
}

//==============================================================================
// InterruptXp::detach
//==============================================================================
int InterruptXp::detach()
{
 if(  pthread_intr_detach_np(inter) == -1 )
 {
  d_errno = errno;
  return -1;
 }
 
 return 0;
}

//==============================================================================
// InterruptXp::wait
//==============================================================================
int InterruptXp::wait(const struct timespec * timeout )
{
 if( pthread_intr_wait_np( inter , timeout ) == -1 )
 {
  d_errno = errno;
  return -1;
 }
 
 return 0;
}

//==============================================================================
// InterruptXp::control
//==============================================================================
int InterruptXp::control(int channel )
{
 if( pthread_intr_control_np( inter , channel ) == -1 )
 {
  d_errno = errno;
  return -1;
 }
 
 return 0;
}


