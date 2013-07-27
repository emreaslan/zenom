//==============================================================================
// PipeXn.hpp - Native Messagepipe services
//
// Author        : 
// Version       : 2.0.01 (Temmuz 2009)
// Compatibility : POSIX, GCC
//==============================================================================


#include "PipeXn.hpp"

//==============================================================================
// PipeXn::PipeXn
//==============================================================================
PipeXn::PipeXn() 
{
 d_errno = 0;
 pipeName = NULL;
}

//==============================================================================
// PipeXn::~PipeXn
//==============================================================================
PipeXn::~PipeXn()
{
 
 deletePipe();
 
 if(pipeName)
  delete [] pipeName;

}

//==============================================================================
// PipeXn::create
//==============================================================================
int PipeXn::create( const char * name, int minor ,size_t poolsize )
{
 int nlen;
 int err;	//Hata denetim
 
 // Isim kopyalanir.
 nlen = strlen(name);
 if(pipeName)
  delete [] pipeName;
 pipeName = new char [nlen+1];
 strncpy(pipeName, name, nlen);
 pipeName[nlen] = '\0';

 // Messagepipe yaratilir
 if( (err = rt_pipe_create( &pipe, pipeName, minor, poolsize )) )
 {
  d_errno = err;
  return -1;
 }

 return 0;
}


//==============================================================================
// PipeXn::deletepipe
//==============================================================================
int PipeXn::deletePipe( )
{
 int err;	//Hata denetim

 // pipe silinir.
 if( (err = rt_pipe_delete(&pipe)) )
 {
  d_errno = -err;
  return -1;
 }

 d_errno = 0;
 return 0;
}




//==============================================================================
// PipeXn::write
//==============================================================================
ssize_t PipeXn::write( const void *buf,size_t size, int mode )
{
 int err;	//Hata denetim

 if( (err = rt_pipe_write(&pipe,buf,size,mode ))  < 1 )
 {
  d_errno = err;
  return NULL;
 }
 return err;
}




//==============================================================================
// PipeXn::read
//==============================================================================
ssize_t PipeXn::read( void *buf,size_t size,RTIME timeout )
{
 size_t readByte;

 if( (readByte = rt_pipe_read(&pipe,buf,size,timeout ))  < 1)
 {
  d_errno = -readByte;
  return NULL;
 }
 return readByte;
}


//==============================================================================
// PipeXn::stream
//==============================================================================
ssize_t PipeXn::stream( void *buf,size_t size )
{
int err;	//Hata denetim

 if( (err = rt_pipe_stream(&pipe,buf,size )) < 1 )
 {
  d_errno = -err;
  return NULL;
 }
 return err;
}

