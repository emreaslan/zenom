//==============================================================================
// ShMem.cpp - Native shared memory wrapper class.
//
// Author        : 
// Version       : 2.0.01 (Temmuz 2009)
// Compatibility : POSIX, GCC
//==============================================================================

#include "HeapXn.hpp"

//==============================================================================
// HeapXn::HeapXn
//==============================================================================
HeapXn::HeapXn()
{
 heapName = NULL;
 heapMem = NULL;
 isOwner = false;
 d_errno = 0;
}


//==============================================================================
// HeapXn::~HeapXn
//==============================================================================
HeapXn::~HeapXn()
{
 if( isOwner )
  deleteHeap();
 else
  unbind();
 
 if(heapName)
  delete [] heapName;
}


//==============================================================================
// HeapXn::create
//==============================================================================
void *HeapXn::create(const char *name, int heapsize, int mode)
{
 int nlen;
 int err;	//Hata denetim
 
 // Isim kopyalanir.
 nlen = strlen(name);
 if(heapName)
  delete [] heapName;
 heapName = new char [nlen+1];
 strncpy(heapName, name, nlen);
 heapName[nlen] = '\0';

 isOwner = true;

 // Heap yaratilir
 if( (err = rt_heap_create( &heap, heapName, heapsize, mode )) )
 {
  d_errno = -err;
  return NULL;
 }

 if( (err = rt_heap_alloc(&heap, heapsize,TM_NONBLOCK , &heapMem)) )
 {
  d_errno = -err;
  return NULL;
 }

 return heapMem;
}


//==============================================================================
// HeapXn::bind
//==============================================================================
void *HeapXn::bind(const char *name, RTIME timeout)
{
 int nlen;
 int err;	//Hata denetim
 
 isOwner = false;

 // Isim kopyalanir.
 nlen = strlen(name);
 if(heapName)
  delete [] heapName;
 heapName = new char [nlen+1];
 strncpy(heapName, name, nlen);
 heapName[nlen] = '\0';
 
 // Heap'e baglanilir.
 if( (err = rt_heap_bind( &heap, heapName, timeout )) )
 {
  d_errno = -err;
  return NULL;
 }

 if( (err = rt_heap_alloc(&heap, 0, TM_NONBLOCK , &heapMem)) )
 {
  d_errno = -err;
  return NULL;
 } 
 return heapMem;
}


//==============================================================================
// HeapXn::unbind
//==============================================================================
int HeapXn::unbind()
{
 int err;	//Hata denetim

 // Heap'e baglanan nesne degil ise heap'i serbest birakamaz.
 if(isOwner)
 {
  d_errno = EACCES;
  return -1;
 }
 // Hafiza geri verilir.
 if( (err = rt_heap_free(&heap, heapMem)) )
 {
  d_errno = -err;
  return -1;
 }

 // Heap serbest birakilir.
 if( (err = rt_heap_unbind(&heap)) )
 {
  d_errno = -err;
  return -1;
 }

 d_errno = 0;
 
 return 0;
}


//==============================================================================
// HeapXn::deleteHeap
//==============================================================================
int HeapXn::deleteHeap()
{
 int err;	//Hata denetim

 // Heap yaratan nesne degil ise heap'i silemez
 if(!isOwner)
 {
  d_errno = EACCES;
  return -1;
 }
 // Hafiza geri verilir.
 if( (err = rt_heap_free(&heap, heapMem)) )
 {
  d_errno = -err;
  return -1;
 }
 // Heap silinir.
 if( (err = rt_heap_delete(&heap)) )
 {
  d_errno = -err;
  return -1;
 }

 isOwner = false;
 d_errno = 0;
 
 return 0;
}

//==============================================================================
// HeapXn::inquire
//==============================================================================
int HeapXn::inquire( RT_HEAP_INFO * info )
{
 int err;	//Hata denetim

 if( (err = rt_heap_inquire(&heap, info)) )
 {
  d_errno = -err;
  return -1;
 } 
 return 0;
}
