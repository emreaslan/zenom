//==============================================================================
// MessageQueueXn.hpp - Native MessageQueue services
//
// Author        : 
// Version       : 2.0.01 (Temmuz 2009)
// Compatibility : POSIX, GCC
//==============================================================================


#include "MessageQueueXn.hpp"

//==============================================================================
// MessageQueueXn::MessageQueueXn
//==============================================================================
MessageQueueXn::MessageQueueXn() 
{
 isOwner = false;
 d_errno = 0;
 queueName = NULL;
}

//==============================================================================
// MessageQueueXn::~MessageQueueXn
//==============================================================================
MessageQueueXn::~MessageQueueXn()
{

 if( isOwner )
  deleteQueue();
 else
  unbind();
 
 if(queueName)
  delete [] queueName;

}

//==============================================================================
// MessageQueueXn::create
//==============================================================================
int MessageQueueXn::create( const char * name, size_t poolsize, size_t qlimit, int mode )
{
 int nlen;
 int err;	//Hata denetim
 
 // Isim kopyalanir.
 nlen = strlen(name);
 if(queueName)
  delete [] queueName;
 queueName = new char [nlen+1];
 strncpy(queueName, name, nlen);
 queueName[nlen] = '\0';

 isOwner = true;

 // MessageQueue yaratilir
 if( (err = rt_queue_create( &queue, queueName, poolsize,qlimit, mode )) )
 {
  d_errno = -err;
  return -1;
 }

 return 0;
}

//==============================================================================
// MessageQueueXn::bind
//==============================================================================
int MessageQueueXn::bind(const char *name, RTIME timeout)
{
 int nlen;
 int err;	//Hata denetim
 
 // Isim kopyalanir.
 nlen = strlen(name);
 if(queueName)
  delete [] queueName;
 queueName = new char [nlen+1];
 strncpy(queueName, name, nlen);
 queueName[nlen] = '\0';

 isOwner = false;

 // MessageQueue yaratilir
 if( (err = rt_queue_bind( &queue, queueName, timeout )) )
 {
  d_errno = -err;
  return -1;
 }

 return 0;
}

//==============================================================================
// MessageQueueXn::alloc
//==============================================================================
void* MessageQueueXn::alloc( size_t size)
{
 void *ptr;	
 if( !(ptr = rt_queue_alloc(&queue,size )) )
 {
  return NULL;
 }
 return ptr;
}

//==============================================================================
// MessageQueueXn::free
//==============================================================================
int MessageQueueXn::free( void *buf)
{
 int err;	//Hata denetim

 if( (err = rt_queue_free(&queue,buf)) )
 {
  d_errno = -err;
  return -1;
 }
 return 0;
}

//==============================================================================
// MessageQueueXn::deleteQueue
//==============================================================================
int MessageQueueXn::deleteQueue( )
{
 int err;	//Hata denetim

 // MessageQueue yaratan nesne degil ise MessageQueue'u silemez
 if(!isOwner)
 {
  d_errno = EACCES;
  return -1;
 }

 // Queue silinir.
 if( (err = rt_queue_delete(&queue)) )
 {
  d_errno = -err;
  return -1;
 }

 isOwner = false;
 d_errno = 0;
 return 0;
}

//==============================================================================
// MessageQueueXp::unbind
//==============================================================================
int MessageQueueXn::unbind( )
{
 int err;	//Hata denetim

 // MessageQueue'a baglanan nesne degil ise MessageQueue'u serbest birakamaz.
 if(isOwner)
 {
  d_errno = EACCES;
  return -1;
 }

 // MessageQueue silinir.
 if( (err = rt_queue_unbind(&queue)) )
 {
  d_errno = -err;
  return -1;
 }

 d_errno = 0;
 return 0;
}

//==============================================================================
// MessageQueueXp::inquire
//==============================================================================
int MessageQueueXn::inquire( RT_QUEUE_INFO * info )
{
 int err;	//Hata denetim

 if( (err = rt_queue_inquire(&queue, info)) )
 {
  d_errno = -err;
  return -1;
 }
 return 0;
}


//==============================================================================
// MessageQueueXp::send
//==============================================================================
int MessageQueueXn::send( void *mbuf,size_t size, int mode )
{
 int err;	//Hata denetim

 if( (err = rt_queue_send(&queue,mbuf,size,mode )) )
 {
  d_errno = -err;
  return -1;
 }
 return 0;
}


//==============================================================================
// MessageQueueXp::write
//==============================================================================
int MessageQueueXn::write( const void *buf,size_t size, int mode )
{
 int err;	//Hata denetim

 if( (err = rt_queue_write(&queue,buf,size,mode )) )
 {
  d_errno = -err;
  return -1;
 }
 return 0;
}


//==============================================================================
// MessageQueueXp::receive
//==============================================================================
size_t MessageQueueXn::receive( void **bufp,RTIME timeout )
{
 size_t readByte;

 if( (readByte = rt_queue_receive(&queue,bufp,timeout )) < 1 )
 {
  d_errno = -readByte;
  return NULL;
 }
 return readByte;
}


//==============================================================================
// MessageQueueXp::read
//==============================================================================
size_t MessageQueueXn::read( void *buf,size_t size,RTIME timeout )
{
 size_t readByte;

 if(  (readByte = rt_queue_read(&queue,buf,size,timeout )) < 1 )
 {
  d_errno = -readByte;
  return NULL;
 }
 return readByte;
}
