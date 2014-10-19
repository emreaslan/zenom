//==============================================================================
// MessageQueueXp.hpp - POSIX message queue wrapper class.
//
// Author        : Vilas Kumar Chitrakaran
// Version       : 2.0 (Apr 2005)
// Compatibility : POSIX, GCC
//==============================================================================

#ifndef _MESSAGEQUEUEXP_HPP_INCLUDED
#define _MESSAGEQUEUEXP_HPP_INCLUDED

#include <mqueue.h>
#include <string.h>
#include <errno.h>


//==============================================================================
// class MessageQueueXp
//------------------------------------------------------------------------------
// \brief
// Processler arasi mesajlasma mekanizmasi.
//
// MessageQueue sınıfı, processlerin iletisim kurmasını sağlar.Processler
// MessageQueue kullanarak mesaj gönderip, kuyruktan mesaj alırlar. MessageQueue
// bir process tarafından oluşturulur, diğer processler oluşturulan kuyruğa bağlanır. 
//
// <b>Ornek Program:</b>
//
// \include MessageQueueXp.t.cpp
//==============================================================================

class MessageQueueXp
{
 public: 
  MessageQueueXp();
   // Default constructor does nothing.
   
  ~MessageQueueXp();
   // Default destructor deletes the message queue if it was created 
   // by the object.
   
  int create(const char *name, int maxNumMsgs, int maxMsgLen = 1024);
   // Creates a message queue object with read/write access. 
   // Note that if a message queue with the same name already exists, this 
   // function will exit with an error (errno set).
   //  name        Name of the message queue. For portability, the name
   //              should begin with a leading "/" and contain no other 
   //              "/" characters.
   //  maxNumMsgs  Number of messages the queue must hold
   //  maxMsgLen   Maximum possible length (bytes) of each message (default 1kB)
   //  return      0 on sucess, -1 on error, 'errno' is set and can be 
   //              retrieved by a call to getErrnoError().

  int open(const char *name);
   // Opens an existing message queue for read/write access. 
   // Note that if the queue does not exist, this function will return with an 
   // error (errno set).
   //  name    Name of the queue to establish connection with.
   //  return  0 on sucess, -1 on error, 'errno' is set and can be 
   //          retrieved by a call to getErrnoError().

  int close();
   // Release access to the message queue. Note that the queue and any
   // messages it may contain are not deleted, and can be opened again.
   //  return  0 on sucess, -1 on error, 'errno' is set and can be 
   //          retrieved by a call to getErrnoError().

  int unlink();
   // If the process calling this function created the message queue, this 
   // function calls close() and marks the message queue for deletion. 
   // Message queues are persistant, i.e., if there are processes that 
   // have the queue open when this function is called then the destruction 
   // of the queue is delayed until all processes have closed their access 
   // to the queue (by calling close()).
   //  return  0 on sucess, -1 on error, 'errno' is set and can be 
   //          retrieved by a call to getErrnoError(). This function
   //          will return -1 if it is called by an object that did not create
   //          the message queue.

  int trySend(const char *msgBuffer, int msgSize);
   // Send a message without blocking.  
   //  msgBuffer  Buffer containing message to be sent.
   //  msgSize    Size of the message.
   //  return     0 on sucess, -1 on error. If the queue is full, 
   //             this function will return -1 with errno set to 
   //             EAGAIN (which can be retrieved by a call to getErrnoError()).

  int send(const char *msgBuffer, int msgSize);
   // Send a message. If the queue is full, this function blocks until
   // the message queue empties and the message can be placed in the queue  
   //  msgBuffer  Buffer containing message to be sent.
   //  msgSize    Size of the message.
   //  return     0 on sucess, -1 on error, 'errno' is set and can be 
   //             retrieved by a call to getErrnoError().

  int tryReceive(char *msgBuffer, int bufSize);
   // Removes a message from the head of the queue. If the queue is empty, 
   // returns immediately without blocking.
   //  msgBuffer  Buffer for received message.
   //  bufSize    Size of the buffer (must be atleast as large as the maximum 
   //             message size for the queue).
   //  return     Number of bytes in the received message, -1 on error. If the 
   //             queue is empty, this function will return -1 with errno set to 
   //             EAGAIN (which can be retrieved by a call to getErrnoError()).

  int receive(char *msgBuffer, int bufSize);
   // Removes a message from the head of the queue. If the queue is empty, 
   // it will block until there is something to read.
   //  msgBuffer  Buffer for received message.
   //  bufSize    Size of the buffer (must be atleast as large as the maximum 
   //             message size for the queue).
   //  return     Number of bytes in the received message, -1 on error. If the 
   //             queue is empty, this function will return -1 with errno set to 
   //             EAGAIN (which can be retrieved by a call to getErrnoError()).

  int notify(const struct sigevent *notification);
   // Notify the calling process asynchronously if a message appeared in the queue. 
   // This is useful if you don't want to keep polling the queue to find whether
   // a new message has arrived, for instance in handling emergency messages.
   // (See pp. 107, Programming for the Real World, POSIX.4 for an example.) 
   //  notification  NULL or a pointer to sigevent structure that describes how 
   //                you want to be notified. 
   //  return        0 on sucess, -1 on error, 'errno' is set and can be 
   //                retrieved by a call to getErrnoError().
   
  inline int getMaxNumMsgs() const;
   //  return  The maximum number of messages the queue can hold.
  
  inline int getMaxMsgLength() const;
   //  return  The maximum possible length (in bytes) for a message in queue.
  
  inline int getErrnoError() const;
   //  return  Error code from the last error that happened before
   //          this function was called, else 0. Error codes are defined
   //          in the standard header errno.h
  
  //======== END OF INTERFACE ========

 private:

  char *d_name;        // Name of the message queue
  mqd_t d_desc;        // Descriptor for the queue
  int d_maxNumMsgs;    // max. number of messages in queue
  int d_maxMsgLength;  // maximum length of a message in the queue
  bool isBlocked;      // true if this end of the queue is configured
                       // to block at receive (if queue) or write (when 
                       // queue is full).
  bool d_isOwner;      // true if this object created the queue, false if 
                       // this object only opened the queue
  int d_errno;         // Latest error message
  
  struct mq_attr Attr;
};



//==============================================================================
// MessageQueueXp::getMaxNumMsgs
//==============================================================================
int MessageQueueXp::getMaxNumMsgs() const
{
 return d_maxNumMsgs;
}


//==============================================================================
// MessageQueueXp::getMaxMsgLength
//==============================================================================
int MessageQueueXp::getMaxMsgLength() const
{
 return d_maxMsgLength;
}


//==============================================================================
// MessageQueueXp::getErrnoError
//==============================================================================
int MessageQueueXp::getErrnoError() const
{
 return d_errno;
}


#endif // _MessageQueueXp_HPP_INCLUDED
