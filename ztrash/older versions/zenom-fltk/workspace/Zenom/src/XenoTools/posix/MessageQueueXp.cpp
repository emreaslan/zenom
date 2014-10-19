//==============================================================================
// MessageQueueXp.cpp - POSIX message queue wrapper class.
//
// Author        : Vilas Kumar Chitrakaran
// Version       : 2.0 (Apr 2005)
// Compatibility : POSIX, GCC
//==============================================================================

#include "MessageQueueXp.hpp"
#include <sys/mman.h>
#include <iostream>

using namespace std;


//==============================================================================
// MessageQueueXp::MessageQueueXp
//==============================================================================
MessageQueueXp::MessageQueueXp()
{
 d_name = NULL;
 d_desc = (mqd_t)-1;
 d_maxNumMsgs = 0;
 d_maxMsgLength = 0;
 isBlocked = false;
 d_errno = 0;
 d_isOwner = false;
 memset(&Attr,0,sizeof(struct mq_attr));
}


//==============================================================================
// MessageQueueXp::~MessageQueueXp
//==============================================================================
MessageQueueXp::~MessageQueueXp()
{
 if( unlink() == -1 )
  close();

 if(d_name)
  delete [] d_name;
}


//==============================================================================
// MessageQueueXp::create
//==============================================================================
int MessageQueueXp::create(const char *name, int maxNumMsgs, int maxMsgLen)
{

 int nlen;
 mode_t mode;
 int oflags;

 // copy the name
 nlen = strlen(name);
 if(d_name)
  delete [] d_name;
 d_name = new char [nlen+1];
 strncpy(d_name, name, nlen);
 d_name[nlen] = '\0';
 
 
 // permissions bits default: nonblocking read/write for anyone
 mode = S_IRWXU | S_IRWXG | S_IRWXO;
 oflags = O_CREAT | O_RDWR | O_NONBLOCK;
 Attr.mq_maxmsg = maxNumMsgs;
 Attr.mq_msgsize = maxMsgLen;
 //mqAttrs.mq_flags = 0; // this is not used by mq_open at all!.

 
 // create queue
 d_desc = mq_open( d_name, oflags, mode, &Attr );

 if(d_desc == (mqd_t)-1)
    return -1; 
 
 d_isOwner = true;
 isBlocked = false;

 return 0;
}


//==============================================================================
// MessageQueueXp::open
//==============================================================================
int MessageQueueXp::open(const char *name)
{
 int nlen;
 //mode_t mode;
 int oflags;
 
 
 // copy the name
 nlen = strlen(name);
 if(d_name)
  delete [] d_name;
 d_name = new char [nlen+1];
 strncpy(d_name, name, nlen);
 d_name[nlen] = '\0';
 
 // permissions bits default: nonblocking read/write for anyone
 //mode = S_IRWXU | S_IRWXG | S_IRWXO; // ** test this. do we need umask(0)? **
 oflags = O_RDWR | O_NONBLOCK;
 

 // open queue
 d_desc = mq_open( d_name, oflags );

 if(d_desc == (mqd_t)-1)
 {
  d_errno = errno;
  return -1;
 }
 d_isOwner = false;


 // Read attributes back and store them
 if(mq_getattr( d_desc, &Attr) == -1)
  cout << "Hata";
// d_maxNumMsgs = mqAttrs.mq_maxmsg;
// d_maxMsgLength = mqAttrs.mq_msgsize;
  (Attr.mq_flags == O_NONBLOCK) ? (isBlocked = false) : (isBlocked = true);

  // cout << strerror(errno ) << endl;

 // cout << mqAttrs.mq_maxmsg <<   "    " << mqAttrs.mq_msgsize << endl;

 return 0;
}


//==============================================================================
// MessageQueueXp::close
//==============================================================================
int MessageQueueXp::close()
{
 if( d_desc == (mqd_t)-1 )
  return 0;
  
 if( mq_close(d_desc) == -1 )
 {
  d_errno = errno;
  return -1;
 }

 d_desc = (mqd_t)-1;
 d_errno = 0;
 
 return 0;
}


//==============================================================================
// MessageQueueXp::unlink
//==============================================================================
int MessageQueueXp::unlink()
{
 if(!d_isOwner)
 {
  d_errno = EACCES;
  return -1;
 }

 if( close() == -1 )
  return -1;
 
 if( mq_unlink(d_name) == -1)
 {
  d_errno = errno;
  return -1;
 }

 d_isOwner = false;
 d_errno = 0;
 
 return 0;
}


//==============================================================================
// MessageQueueXp::trySend
//==============================================================================
int MessageQueueXp::trySend(const char *msgBuffer, int msgSize)
{

 struct sched_param param;
 if( isBlocked == true )
 {
  // get current process priority
  int policy;
  
  if( pthread_getschedparam( pthread_self(), &policy, &param) == -1)
  {
   d_errno = errno;
   return -1;
  }

  
 
  Attr.mq_flags =  O_NONBLOCK ;
  if( mq_setattr(d_desc, &Attr, NULL) == -1)
  {
   d_errno = errno;
   return -1;
  }

   isBlocked = false;
 }
 

  // send message at same priority as process
  if( mq_send( d_desc, msgBuffer, msgSize, param.sched_priority) == -1)
  {
   d_errno = errno;
   return -1;
  }
  

 d_errno = 0;
 return 0;
}


//==============================================================================
// MessageQueueXp::send
//==============================================================================
int MessageQueueXp::send(const char *msgBuffer, int msgSize)
{

 if( isBlocked == false)
 {
  Attr.mq_flags = NULL ;
  if( mq_setattr(d_desc, &Attr, NULL) == -1)
  {
   d_errno = errno;
   return -1;
  }

  isBlocked = true;
 }



 if( mq_send( d_desc, msgBuffer, msgSize, NULL) == -1)
 {
  d_errno = errno;
  return -1;
 }



 return 0;
}


//==============================================================================
// MessageQueueXp::tryReceive
//==============================================================================
int MessageQueueXp::tryReceive(char *msgBuffer, int bufSize)
{

 if(isBlocked == true )
 {
  Attr.mq_flags = O_NONBLOCK;
  if( mq_setattr(d_desc, &Attr, NULL) == -1)
  {
   d_errno = errno;
   return -1;
  }

  isBlocked = false;

 }

 
 // receive message
 int retVal;
 retVal = mq_receive(d_desc, msgBuffer, bufSize, NULL);
 if(retVal == -1)
 {
  d_errno = errno;
  return -1;
 }
 
 d_errno = 0;
 
 return retVal;
}


//==============================================================================
// MessageQueueXp::receive
//==============================================================================
int MessageQueueXp::receive(char *msgBuffer, int bufSize)
{ 

 if( isBlocked == false )
 {
  //unsigned int priority = 0;

  Attr.mq_flags = NULL;
  if( mq_setattr(d_desc, &Attr, NULL) == -1)
  {
   d_errno = errno;
   return -1;
  }

  isBlocked = true;
 }
   

 if( mq_receive( d_desc, msgBuffer, bufSize, NULL ) == -1)
 {
  d_errno = errno;
  return -1;
 }

 return 0;
}


//==============================================================================
// MessageQueueXp::notify
//==============================================================================
int MessageQueueXp::notify(const struct sigevent *notification)
{
 if( mq_notify(d_desc, notification) == -1 )
 {
  d_errno = errno;
  return -1;
 }
 d_errno = 0;
 return 0;
}
