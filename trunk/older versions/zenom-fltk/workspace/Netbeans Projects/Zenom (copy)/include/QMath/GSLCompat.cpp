//======================================================================== 
// Package		: The Math Library - Ex
// Authors		: Vilas Kumar Chitrakaran
// Start Date		: Sun Oct 2 11:08:28 GMT 2005
// Compiler		: GNU C++ 2.95.3 and above
// ----------------------------------------------------------------------  
// File: GSLCompat.cpp
// Conversion between QMath types and GSL types
//========================================================================  

#include "GSLCompat.hpp"

//========================================================================  
// to_gsl_matrix
//========================================================================  
void GSLCompat_matrix(MatrixBase<double> *q, gsl_matrix *gsl)
{
 gsl->size1 = q->getNumRows();
 gsl->size2 = q->getNumColumns();
 gsl->tda = gsl->size2;
 gsl->data = q->getElementsPointer();
 gsl->block = NULL;
 gsl->owner = 0;
}

void GSLCompat_matrix(MatrixBase<char> *q, gsl_matrix_char *gsl)
{
 gsl->size1 = q->getNumRows();
 gsl->size2 = q->getNumColumns();
 gsl->tda = gsl->size2;
 gsl->data = q->getElementsPointer();
 gsl->block = NULL;
 gsl->owner = 0;
}


void GSLCompat_matrix(MatrixBase<unsigned char> *q, gsl_matrix_uchar *gsl)
{
 gsl->size1 = q->getNumRows();
 gsl->size2 = q->getNumColumns();
 gsl->tda = gsl->size2;
 gsl->data = q->getElementsPointer();
 gsl->block = NULL;
 gsl->owner = 0;
}

void GSLCompat_matrix(MatrixBase<short> *q, gsl_matrix_short *gsl)
{
 gsl->size1 = q->getNumRows();
 gsl->size2 = q->getNumColumns();
 gsl->tda = gsl->size2;
 gsl->data = q->getElementsPointer();
 gsl->block = NULL;
 gsl->owner = 0;
}

void GSLCompat_matrix(MatrixBase<unsigned short> *q, gsl_matrix_ushort *gsl)
{
 gsl->size1 = q->getNumRows();
 gsl->size2 = q->getNumColumns();
 gsl->tda = gsl->size2;
 gsl->data = q->getElementsPointer();
 gsl->block = NULL;
 gsl->owner = 0;
}

void GSLCompat_matrix(MatrixBase<int> *q, gsl_matrix_int *gsl)
{
 gsl->size1 = q->getNumRows();
 gsl->size2 = q->getNumColumns();
 gsl->tda = gsl->size2;
 gsl->data = q->getElementsPointer();
 gsl->block = NULL;
 gsl->owner = 0;
}

void GSLCompat_matrix(MatrixBase<unsigned int> *q, gsl_matrix_uint *gsl)
{
 gsl->size1 = q->getNumRows();
 gsl->size2 = q->getNumColumns();
 gsl->tda = gsl->size2;
 gsl->data = q->getElementsPointer();
 gsl->block = NULL;
 gsl->owner = 0;
}

void GSLCompat_matrix(MatrixBase<long> *q, gsl_matrix_long *gsl)
{
 gsl->size1 = q->getNumRows();
 gsl->size2 = q->getNumColumns();
 gsl->tda = gsl->size2;
 gsl->data = q->getElementsPointer();
 gsl->block = NULL;
 gsl->owner = 0;
}

void GSLCompat_matrix(MatrixBase<unsigned long> *q, gsl_matrix_ulong *gsl)
{
 gsl->size1 = q->getNumRows();
 gsl->size2 = q->getNumColumns();
 gsl->tda = gsl->size2;
 gsl->data = q->getElementsPointer();
 gsl->block = NULL;
 gsl->owner = 0;
}

void GSLCompat_matrix(MatrixBase<float> *q, gsl_matrix_float *gsl)
{
 gsl->size1 = q->getNumRows();
 gsl->size2 = q->getNumColumns();
 gsl->tda = gsl->size2;
 gsl->data = q->getElementsPointer();
 gsl->block = NULL;
 gsl->owner = 0;
}

void GSLCompat_matrix(MatrixBase<long double> *q, gsl_matrix_long_double *gsl)
{
 gsl->size1 = q->getNumRows();
 gsl->size2 = q->getNumColumns();
 gsl->tda = gsl->size2;
 gsl->data = q->getElementsPointer();
 gsl->block = NULL;
 gsl->owner = 0;
}



//========================================================================  
// to_gsl_vector
//========================================================================  
void GSLCompat_vector(VectorBase<double> *q, gsl_vector *gsl)
{
 gsl->size = q->getNumElements();
 gsl->stride = 1;
 gsl->data = q->getElementsPointer();
 gsl->block = NULL;
 gsl->owner = 0;
}

void GSLCompat_vector(VectorBase<char> *q, gsl_vector_char *gsl)
{
 gsl->size = q->getNumElements();
 gsl->stride = 1;
 gsl->data = q->getElementsPointer();
 gsl->block = NULL;
 gsl->owner = 0;
}

void GSLCompat_vector(VectorBase<unsigned char> *q, gsl_vector_uchar *gsl)

{
 gsl->size = q->getNumElements();
 gsl->stride = 1;
 gsl->data = q->getElementsPointer();
 gsl->block = NULL;
 gsl->owner = 0;
}

void GSLCompat_vector(VectorBase<short> *q, gsl_vector_short *gsl)
{
 gsl->size = q->getNumElements();
 gsl->stride = 1;
 gsl->data = q->getElementsPointer();
 gsl->block = NULL;
 gsl->owner = 0;
}

void GSLCompat_vector(VectorBase<unsigned short> *q, gsl_vector_ushort *gsl)
{
 gsl->size = q->getNumElements();
 gsl->stride = 1;
 gsl->data = q->getElementsPointer();
 gsl->block = NULL;
 gsl->owner = 0;
}

void GSLCompat_vector(VectorBase<int> *q, gsl_vector_int *gsl)
{
 gsl->size = q->getNumElements();
 gsl->stride = 1;
 gsl->data = q->getElementsPointer();
 gsl->block = NULL;
 gsl->owner = 0;
}

void GSLCompat_vector(VectorBase<unsigned int> *q, gsl_vector_uint *gsl)
{
 gsl->size = q->getNumElements();
 gsl->stride = 1;
 gsl->data = q->getElementsPointer();
 gsl->block = NULL;
 gsl->owner = 0;
}

void GSLCompat_vector(VectorBase<long> *q, gsl_vector_long *gsl)
{
 gsl->size = q->getNumElements();
 gsl->stride = 1;
 gsl->data = q->getElementsPointer();
 gsl->block = NULL;
 gsl->owner = 0;
}

void GSLCompat_vector(VectorBase<unsigned long> *q, gsl_vector_ulong *gsl)
{
 gsl->size = q->getNumElements();
 gsl->stride = 1;
 gsl->data = q->getElementsPointer();
 gsl->block = NULL;
 gsl->owner = 0;
}

void GSLCompat_vector(VectorBase<float> *q, gsl_vector_float *gsl)
{
 gsl->size = q->getNumElements();
 gsl->stride = 1;
 gsl->data = q->getElementsPointer();
 gsl->block = NULL;
 gsl->owner = 0;
}

void GSLCompat_vector(VectorBase<long double> *q, gsl_vector_long_double *gsl)
{
 gsl->size = q->getNumElements();
 gsl->stride = 1;
 gsl->data = q->getElementsPointer();
 gsl->block = NULL;
 gsl->owner = 0;
}

