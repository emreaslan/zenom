//======================================================================== 
// Package		: The Math Library - Ex
// Authors		: Vilas Kumar Chitrakaran
// Start Date		: Sun Oct 2 11:08:28 GMT 2005
// Compiler		: GNU C++ 2.95.3 and above
// ----------------------------------------------------------------------  
// File: GSLCompat.hpp
// Conversion between QMath types and GSL types
//========================================================================  

#ifndef INCLUDED_GSLCompat_hpp
#define INCLUDED_GSLCompat_hpp 

#include "Vector.hpp"
#include "gsl/gsl_matrix.h"
#include "gsl/gsl_vector.h"

/*! Prototypes for typecasting to GSL data types. Note that the
    functions do not copy data between objects. Hence, changes made to 
    contents of one type will reflect in the contents of the converted
    type. Supported data types:
    char, unsigned char, short, unsigned short, int, unsigned int, long,  
    unsigned long, float, double, long double.
*/

void GSLCompat_matrix(MatrixBase<double> *q, gsl_matrix *gsl);
 /*!< Obtain a gsl_matrix pointer from a Matrix pointer for
      data type double. Subsequent modification of one object
      will be reflected in the other.
      \param q    A pointer to QMath object
      \param gsl  A pointer to GSL object
 */
 
void GSLCompat_matrix(MatrixBase<char> *q, gsl_matrix_char *gsl);
void GSLCompat_matrix(MatrixBase<unsigned char> *q, gsl_matrix_uchar *gsl);
void GSLCompat_matrix(MatrixBase<short> *q, gsl_matrix_short *gsl);
void GSLCompat_matrix(MatrixBase<unsigned short> *q, gsl_matrix_ushort *gsl);
void GSLCompat_matrix(MatrixBase<int> *q, gsl_matrix_int *gsl);
void GSLCompat_matrix(MatrixBase<unsigned int> *q, gsl_matrix_uint *gsl);
void GSLCompat_matrix(MatrixBase<long> *q, gsl_matrix_long *gsl);
void GSLCompat_matrix(MatrixBase<unsigned long> *q, gsl_matrix_ulong *gsl);
void GSLCompat_matrix(MatrixBase<float> *q, gsl_matrix_float *gsl);
void GSLCompat_matrix(MatrixBase<long double> *q, gsl_matrix_long_double *gsl);
 
void GSLCompat_vector(VectorBase<double> *q, gsl_vector *gsl);
 /*!< Obtain an gsl_vector pointer from a Vector pointer for
      data type double. Subsequent modification of one object
      will be reflected in the other.
      \param q    A pointer to QMath object
      \param gsl  A pointer to GSL object
 */
 
void GSLCompat_vector(VectorBase<char> *q, gsl_vector_char *gsl);
void GSLCompat_vector(VectorBase<unsigned char> *q, gsl_vector_uchar *gsl);
void GSLCompat_vector(VectorBase<short> *q, gsl_vector_short *gsl);
void GSLCompat_vector(VectorBase<unsigned short> *q, gsl_vector_ushort *gsl);
void GSLCompat_vector(VectorBase<int> *q, gsl_vector_int *gsl);
void GSLCompat_vector(VectorBase<unsigned int> *q, gsl_vector_uint *gsl);
void GSLCompat_vector(VectorBase<long> *q, gsl_vector_long *gsl);
void GSLCompat_vector(VectorBase<unsigned long> *q, gsl_vector_ulong *gsl);
void GSLCompat_vector(VectorBase<float> *q, gsl_vector_float *gsl);
void GSLCompat_vector(VectorBase<long double> *q, gsl_vector_long_double *gsl);

#endif // INCLUDED_GSLCompat_hpp 
