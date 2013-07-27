#ifndef INCLUDED_ARRAY_H
#define INCLUDED_ARRAY_H

///=============================================================================
/// file   : Array.h
///-----------------------------------------------------------------------------
/// This file implements the template class Array. This class is used to
/// manage arrays of pointers to classes. The classes must provide < and > 
/// operators (for sorting) as well as << operator for printing. The array
/// will grow to accomodate new elements, but it won't shrink. Only the
/// array's destructor will invoke the elements' destructors, removing
/// elements from the array will not invoke their destructors.
///=============================================================================


#include <iostream>
using namespace std;

template<class T>
class Array 
{
	protected:
		int d_maxNumElements; // Maximum # of elements can hold without expanding
		int	d_numElements;    // Number of elements currently in list
		int d_growIncrement;  // Whenever the array is grown, it is grown by this
		                      // many entries.

		T *d_array;          // Array of variables

	protected:
		// These methods are used internally by this class, the user doesn't call
		// them.
		
		void grow (
			int newMaxNumElements // new maximum # of elements in the list
		); 
			// Increase the maximum size of the list by this many elements. 

		void quickSort (
			int left,   // Left index of the partition
			int right   // Right index of the partition
		);

	public:

		// ----- CREATORS

		Array (int initialArraySize = 100);
			// Create a blank list


                // Copy Constructor
                Array (const Array<T> &);

                // = operator
                Array<T>& operator=(const Array<T> &);

			
		~Array ();
			// Deletes all of the elements as well as the array. The elements' 
			// destructors are NOT called. Either delete them manually or
			// call deleteAllElements();

		// ----- OPERATORS

		// ----- MANIPULATORS

		void appendElement (
			T newElement // Pointer to be added to the array
		);
			// Add this element to the end of the array

		void insertElement (
			T newElement, // Pointer to object to be added
			int index     // Index into the list where it will be inserted
		);
			// New element will be inserted into the list at the given index. 
			// All elements with that index and greater will be shifted down
			// by one (their indices will increase by one).
			// If you insert past either end of the array, the insertion will
			// occur at the end (element 0 or element d_numElements)

		void removeElement (int index);
			// Remove the pointer at this index. Compact the array. The element's
			// destructor is NOT called.
		
		void sortAscending ();
			// Sort the array in ascending order. Elements must overload the
			// < and > operators for this to work.
			
		void removeAllElements ();
			// Remove all of the elements of the array. Does NOT call the elements'
			// destructors.

		void deleteAllElements ();
			// Removes all of the elements from the array and deletes them (calls
			// their destructors.
			
		// ----- ACCESSORS
			
		inline int getNumElements() const;
			// Return # of elements in list
			
		T getElement (int index) const;
			// Returns the element at the given index

                T& getElementRef (int index) const;
			// Returns the element at the given index

		void setGrowIncrement (int growIncrement);
			// Sets by how many elements the list will grow when it needs to grow.
};



// ----- CREATORS

///=============================================================================
/// name   : Array 
///-----------------------------------------------------------------------------
/// input  : initialArraySize - What size is the array initially
/// Creates an empty array that can hold the given # of elements. 
///=============================================================================

template <class T>
Array<T>::Array (int initialArraySize) 
{
  d_maxNumElements = initialArraySize;
  d_array = new T [d_maxNumElements];
  d_numElements = 0;
	setGrowIncrement (20); // When the array grows, grow it by this many elements
}

template <class T>
Array<T>::Array (const Array<T> &source)
{
    d_maxNumElements = source.d_maxNumElements;
    d_numElements = source.d_numElements;
    d_growIncrement = source.d_growIncrement;
    d_array = new T [d_maxNumElements];
    setGrowIncrement (d_growIncrement); // When the array grows, grow it by this many elements

    for(int i = 0; i < d_numElements; ++i)
        d_array[i] = source.d_array[i];
}

template <class T>
Array<T>& Array<T>::operator =(const Array<T> &source)
{
    delete [] d_array;

    d_maxNumElements = source.d_maxNumElements;
    d_numElements = source.d_numElements;
    d_growIncrement = source.d_growIncrement;
    d_array = new T [d_maxNumElements];
    setGrowIncrement (d_growIncrement); // When the array grows, grow it by this many elements

    for(int i = 0; i < d_numElements; ++i)
        d_array[i] = source.d_array[i];

    return *this;
}



///=============================================================================
/// name   : ~Array 
///-----------------------------------------------------------------------------
/// Destructor. Invokes the destructor of each element, then deletes the array.
///=============================================================================

template <class T>
Array<T>::~Array () 
{
	delete [] d_array;
}

// ----- OPERATORS


// ----- MANIPULATORS

///=============================================================================
/// name   : grow  
///-----------------------------------------------------------------------------
/// input  : newMaxNumElements - Grow the array so it can hold this many
///          elements.
/// Allocates a new array that can hold this many elements, copies the
/// elements from the old array, then deletes the old array.
///=============================================================================

template <class T>
void Array<T>::grow (int newMaxNumElements) 
{
	T *newList;

	if (newMaxNumElements <= d_maxNumElements)
		return;

	d_maxNumElements = newMaxNumElements;

	newList = new T [d_maxNumElements];

	int i;
	
	for (i = 0; i < d_numElements; i++)
		newList[i]=d_array[i];

	//for (; i < d_maxNumElements; i++)
	//	newList[i]=0;

  delete[] d_array;

  d_array=newList;
}

///=============================================================================
/// name   : appendElement
///-----------------------------------------------------------------------------
/// input  : newElement - Pointer to the new element to be added.
/// Adds the new element as the last entry in the array. The array is grown if
/// necessary.
///=============================================================================

template <class T>
void Array<T>::appendElement (T newElement) 
{
  if (d_numElements >= d_maxNumElements)
    grow (d_maxNumElements + d_growIncrement);

  d_array[d_numElements]=newElement;
  d_numElements++;
}

///=============================================================================
/// name   : insertElement
///-----------------------------------------------------------------------------
/// input  : newElement - Pointer to the new element to be added.
///         index - Position in the array where this element will be inserted.
/// Adds the new element at the given position in the array. The other
/// elements are moved to make room for the new element. The array is grown if
/// necessary.
///=============================================================================

template <class T>
void Array<T>::insertElement (T newElement, int index) 
{
	int i;

  if (d_numElements >= d_maxNumElements)
    grow (d_maxNumElements + d_growIncrement);

	for (i = d_numElements; i > index; i--)
		d_array[i] = d_array[i-1];

	d_array[i] = newElement;

	d_numElements++;
}

///=============================================================================
/// name   : removeElement
///-----------------------------------------------------------------------------
/// input  : index - Index in the array of the element to be removed.
/// Removes the given element from the array. The array is then compacted.
/// Does NOT call the element's destructor.
///=============================================================================

template <class T>
void Array<T>::removeElement (int index) 
{
	int i;
	for (i = index + 1; i < d_numElements; i++)
		d_array[i-1] = d_array[i];

	d_numElements--;
}

///=============================================================================
/// name   : sortAscending
///-----------------------------------------------------------------------------
/// Sorts the array in ascending order, using the elements' < and > operators
/// for comparisons. This function just sets up the recursive quicksort.
///=============================================================================

template <class T>
void Array<T>::sortAscending () 
{
	quickSort (0, d_numElements - 1);
}

///=============================================================================
/// name   : quickSort
///-----------------------------------------------------------------------------
/// input  : left - Index of the left boundary of the partition
///         right - Index of the right boundary of the partition
/// Recursive implementation of quicksort. The elements must provide < and >
/// operators.
///=============================================================================

template <class T>
void Array<T>::quickSort (int left, int right)
{
	int i;
	int j;
	T pivot;
	T temp;

	i = left;
	j = right;

	// Just partition the array about this central pivot. Not optimal but works.
	pivot = d_array[(left + right) / 2];
	
	do
	{
		while (d_array[i]->compare(pivot) < 0 && i < right)
			i++;
		while (pivot->compare(d_array[j]) < 0 && j > left)
			j--;

		if (i <= j)
		{
			temp = d_array[i];
			d_array[i] = d_array[j];
			d_array[j] = temp;
			i++;
			j--;
		}
	} 
	while (i <= j);

	if (left < j)
		quickSort (left, j);

	if (i < right)
		quickSort (i, right);
}


///=============================================================================
/// name   : removeAllElements
/// Remove all of the elements from the array. Does NOT call destructores.
///=============================================================================

template <class T>
void Array<T>::removeAllElements () 
{
	int i;

	// Could remove this for loop to optimize
	//for (i = 0; i < d_numElements; i++)
	//	d_array[i]=0;

	d_numElements = 0;
}

///=============================================================================
/// name   : deleteAllElements
/// Deletes all of the elements of the array (calls their DESTRUCTORS).
///=============================================================================

template <class T>
void Array<T>::deleteAllElements () 
{
	int i;

	// Could remove this for loop to optimize
	for (i = 0; i < d_numElements; i++)
	{
		delete d_array[i];
		d_array[i]=0;
	}
	d_numElements = 0;

}

// ----- ACCESSORS

///=============================================================================
/// name   : getNumElements
///-----------------------------------------------------------------------------
/// return : # of elements in the list.
///=============================================================================

template <class T>
inline int Array<T>::getNumElements() const
{
	return (d_numElements);
}


///=============================================================================
/// name   : getElement
///-----------------------------------------------------------------------------
/// input  : index - Index of the element to be returned.
/// return : The element of the array at the given index.
///=============================================================================

template <class T>
inline T Array<T>::getElement (int index) const
{
	return (d_array[index]);
}

///=============================================================================
/// name   : getElementRef
///-----------------------------------------------------------------------------
/// input  : index - Index of the element to be returned.
/// return : The element of the array at the given index.
///=============================================================================

template <class T>
inline T& Array<T>::getElementRef (int index) const
{
	return (d_array[index]);
}

///=============================================================================
/// name   : setGrowIncrement
///-----------------------------------------------------------------------------
/// input  : growIncrement - # of elements to be added when the array grows.
/// This value is used when the array is grown automatically. This happens
/// when an element is added, and the current # of elements becomes > that the
/// max # of elements.
///=============================================================================

template <class T>
inline void Array<T>::setGrowIncrement (int growIncrement) 
{
	d_growIncrement = growIncrement;
}

#endif
