//==============================================================================
// TaskXn.hpp - Native Task
//
// Author        : 
// Version       : 2.0.01 (Temmuz 2009)
// Compatibility : POSIX, GCC
//==============================================================================

#include "TaskXn.hpp"

#include <iostream>
using namespace std;
//==============================================================================
// TaskXn::TaskXn
//==============================================================================
TaskXn::TaskXn()
{
 isOwner = false;
 d_errno = 0;
 taskName = NULL;
 isSpawn = false;
}

//==============================================================================
// TaskXn::~TaskXn
//==============================================================================
TaskXn::~TaskXn()
{
 if( isOwner )
  deleteTask();
 else
  unbind();
 
 if(taskName)
  delete [] taskName;
}

//==============================================================================
// TaskXn::create
//==============================================================================
int TaskXn::create(const char *name, int stksize, int prio , int mode)
{
 int nlen;
 int err;	//Hata denetim
 
 // Isim kopyalanir.
 nlen = strlen(name);
 if(taskName)
  delete [] taskName;
 taskName = new char [nlen+1];
 strncpy(taskName, name, nlen);
 taskName[nlen] = '\0';

 isOwner = true;

 // Task yaratilir
 if( (err = rt_task_create( &task, taskName, stksize, prio, mode )) )
 {
  d_errno = -err;
  return -1;
 }
 return 0;
}

//==============================================================================
// TaskXn::bind
//==============================================================================
int TaskXn::bind(const char *name, RTIME timeout)
{
 int nlen;
 int err;	//Hata denetim
 
 // Isim kopyalanir.
 nlen = strlen(name);
 if(taskName)
  delete [] taskName;
 taskName = new char [nlen+1];
 strncpy(taskName, name, nlen);
 taskName[nlen] = '\0';

 isOwner = false;

 // Task'a baglanilir
 if( (err = rt_task_bind( &task, taskName, timeout )) )
 {
  d_errno = -err;
  return -1;
 }

 return 0;
}

//==============================================================================
// TaskXn::start
//==============================================================================
int TaskXn::start(void(*entry)(void *cookie), void *cookie)
{

 // Obje Spawn bir task olusturmusta start fonksiyonu calismaz
 if(!isSpawn)
 {
  int err;	//Hata denetim

  err = rt_task_start(&task, entry, cookie);
  d_errno = -err;
  if( err )
   return -1;  
  return 0;
  }
  
  return -1;
}


//==============================================================================
// TaskXn::start
// Parametresiz overload versiyonu
//==============================================================================
int TaskXn::start()
{
 // Obje Spawn bir task olusturmusta start fonksiyonu calismaz
 if(!isSpawn)
 {
  int err;	//Hata denetim

  err = rt_task_start(&task, TaskXn::taskRun, (void *) this );
  d_errno = -err;
  if( err )
   return -1;  
  return 0;
  }
  
  return -1;
}


//==============================================================================
// TaskXn::suspend
//==============================================================================
int TaskXn::suspend()
{
 int err;	//Hata denetim

 // Task askiya alinir.
 if( (err = rt_task_suspend( &task )) )
 {
  d_errno = -err;
  return -1;
 }

 return 0;
}

//==============================================================================
// TaskXn::resume
//==============================================================================
int TaskXn::resume()
{
 int err;	//Hata denetim

 // Task'a kaldigi yerden devam eder.
 if( (err = rt_task_resume( &task )) )
 {
  d_errno = -err;
  return -1;
 }

 return 0;
}

//==============================================================================
// TaskXn::yield
//==============================================================================
int TaskXn::yield()
{
 int err;	//Hata denetim

 // Manual round-robin.
 if( (err = rt_task_yield()) )
 {
  d_errno = -err;
  return -1;
 }

 return 0;
}

//==============================================================================
// TaskXn::setPeriodic
//==============================================================================
int TaskXn::setPeriodic(RTIME idate, RTIME period)
{
 int err;	//Hata denetim

 if( (err = rt_task_set_periodic( &task,idate, period )) )
 {
  d_errno = -err;
  return -1;
 }

 return 0;
}

//==============================================================================
// TaskXn::waitPeriod
//==============================================================================
int TaskXn::waitPeriod(unsigned long* overruns_r)
{
 int err;	//Hata denetim

 if( (err = rt_task_wait_period( overruns_r )) )
 {
  d_errno = -err;
  return -1;
 }

 return 0;
}

//==============================================================================
// TaskXn::setPriority
//==============================================================================
int TaskXn::setPriority(int prio)
{
 int err;	//Hata denetim

 if( (err = rt_task_set_priority( &task, prio)) )
 {
  d_errno = -err;
  return -1;
 }

 return 0;
}

//==============================================================================
// TaskXn::unblock
//==============================================================================
int TaskXn::unblock()
{
 int err;	//Hata denetim

 if( (err = rt_task_unblock( &task )) )
 {
  d_errno = -err;
  return -1;
 }

 return 0;
}

//==============================================================================
// TaskXn::self
//==============================================================================
RT_TASK* TaskXn::self()
{
 return rt_task_self();
}

//==============================================================================
// TaskXn::slice
//==============================================================================
int TaskXn::slice(RTIME quantum)
{
 int err;	//Hata denetim

 if( (err = rt_task_slice( &task, quantum )) )
 {
  d_errno = -err;
  return -1;
 }

 return 0;
}

//==============================================================================
// TaskXn::send
//==============================================================================
int TaskXn::send(TaskXn receiver, RT_TASK_MCB * mcb_s, RT_TASK_MCB* mcb_r, RTIME timeout)
{
 int err;	//Hata denetim

 if( ( (err = (int)rt_task_send( &(receiver.task), mcb_s, mcb_r, timeout )) ) < 0 )
 {
  d_errno = -err;
  return -1;
 }

 return err;
}

//==============================================================================
// TaskXn::receive
//==============================================================================
int TaskXn::receive(RT_TASK_MCB* mcb_r, RTIME timeout)
{
 if( (flowid = rt_task_receive( mcb_r, timeout )) < 0)
 {
  d_errno = -flowid;
  return -1;
 }

 return 0;
}

//==============================================================================
// TaskXn::reply
//==============================================================================
int TaskXn::reply( RT_TASK_MCB* mcb_s )
{
 int err;

 if( (err = rt_task_reply( flowid, mcb_s )) )
 {
  d_errno = -err;
  return -1;
 }

 return 0;
}


//==============================================================================
// TaskXn::spawn
//==============================================================================
int TaskXn::spawn(const char * name, int stksize, int prio, int mode, void(*entry)(void *cookie), void * cookie )
{
 int nlen;
 int err;	//Hata denetim
 
 // Isim kopyalanir.
 nlen = strlen(name);
 if(taskName)
  delete [] taskName;
 taskName = new char [nlen+1];
 strncpy(taskName, name, nlen);
 taskName[nlen] = '\0';

 isOwner = true;
 isSpawn = true;

 // Task yaratilir
 if( (err = rt_task_spawn( &task, taskName, stksize, prio, mode,entry,cookie)) )
 {
  d_errno = -err;
  return -1;
 }
 return 0;
}


//==============================================================================
// TaskXn::join
//==============================================================================
int TaskXn::join()
{
 int err;	//Hata denetim
 
 // Task'in islemini bitirmesi beklenir
 if( (err = rt_task_join( &task) ) )
 {
  d_errno = -err;
  return -1;
 }
 return 0;

}



//==============================================================================
// TaskXn::deleteTask
//==============================================================================
int TaskXn::deleteTask()
{
 int err;	//Hata denetim

 // Task yaratan nesne degil ise event'i silemez
 if(!isOwner)
 {
  d_errno = EACCES;
  return -1;
 }

 // Event silinir.
 if( (err = rt_task_delete(&task)) )
 {
  d_errno = -err;
  return -1;
 }

 isOwner = false;
 d_errno = 0;
 return 0;

 }
 
 
 
//==============================================================================
// TaskXn::unbind
//==============================================================================
int TaskXn::unbind()
{
 int err;	//Hata denetim

 // Task'a baglanan nesne degil ise Event'i serbest birakamaz.
 if(isOwner)
 {
  d_errno = EACCES;
  return -1;
 }

 // Event silinir.
 if( (err = rt_task_unbind(&task)) )
 {
  d_errno = -err;
  return -1;
 }

 d_errno = 0;
 return 0;
}

//==============================================================================
// TaskXn::inquire
//==============================================================================
int TaskXn::inquire( RT_TASK_INFO * info )
{
 int err;	//Hata denetim

 if( (err = rt_task_inquire(&task, info)) )
 {
  d_errno = -err;
  return -1;
 }
 return 0;
}

