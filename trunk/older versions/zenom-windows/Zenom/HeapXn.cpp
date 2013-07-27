//==============================================================================
// ShMem.cpp - Native shared memory wrapper class.
//
// Author        :
// Version       : 2.0.01 (Temmuz 2009)
// Compatibility : POSIX, GCC
//==============================================================================

#include "HeapXn.h"

//==============================================================================
// HeapXn::HeapXn
//==============================================================================
HeapXn::HeapXn()
{
	mState = HeapXn::NONE;
}

//==============================================================================
// HeapXn::~HeapXn
//==============================================================================
HeapXn::~HeapXn()
{

}

//==============================================================================
// HeapXn::create
//==============================================================================
void HeapXn::create(const std::string& pName, size_t pHeapSize, int pMode)
{
	mHeapName = pName;
	int err;
	/*
	// Create a heap.
	if( (err = rt_heap_create( &heap, pName.c_str(), pHeapSize, pMode )) )
	{
		throw ZException(mHeapName, "rt_heap_create", -err);
	}
	*/
	mState = HeapXn::CREATED;
}

//==============================================================================
// HeapXn::alloc
//==============================================================================
void* HeapXn::alloc(size_t pHeapSize, RTIME pTimeout)
{
	int err;
	void *block;	// Heap address
	/*
	if( (err = rt_heap_alloc( &heap, pHeapSize, pTimeout, &block )) )
	{
		throw ZException(mHeapName, "rt_heap_alloc", -err);
	}
	*/
	block = new size_t[pHeapSize];

	return block;
}

//==============================================================================
// HeapXn::free
//==============================================================================
void HeapXn::free(void* pBlock)
{
	/*
	int err;
	// Free the block.
	if( (err = rt_heap_free(&heap, pBlock)) )
	{
		throw ZException(mHeapName, "rt_heap_free", -err);
	}
	*/
	 //TODO memory leak
}

//==============================================================================
// HeapXn::deleteHeap
//==============================================================================
void HeapXn::deleteHeap()
{
	/*
	int err;
	// Delete a heap.
	if( (err = rt_heap_delete(&heap)) )
	{
		throw ZException(mHeapName, "rt_heap_delete", -err);
	}
	*/
	mState = HeapXn::NONE;
}

//==============================================================================
// HeapXn::bind
//==============================================================================
void HeapXn::bind(const std::string& pName, RTIME pTimeout)
{
	mHeapName = pName;
	int err;
	/*
	// Bind to a mappable heap.
	if( (err = rt_heap_bind( &heap, pName.c_str(), pTimeout )) )
 	{
		throw ZException(pName, "rt_heap_bind", -err);
	}
	*/

	mState = HeapXn::BINDED;
}


//==============================================================================
// HeapXn::unbind
//==============================================================================
void HeapXn::unbind()
{
	int err;
	/*
	// Unbind from a mappable heap.
 	if( (err = rt_heap_unbind(&heap)) )
	{
		throw ZException(mHeapName, "rt_heap_unbind", -err);
	}
	*/
 	mState = HeapXn::NONE;
}

/*
//==============================================================================
// HeapXn::inquire
//==============================================================================
RT_HEAP_INFO HeapXn::inquire()
{
	RT_HEAP_INFO info;
	int err;

	// Inquire about a heap.
	if( (err = rt_heap_inquire(&heap, &info)) )
	{
		throw ZException(mHeapName, "rt_heap_inquire", -err);
	}

	return info;
}
*/
