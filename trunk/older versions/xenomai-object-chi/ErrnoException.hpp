//==============================================================================
// ErrnoException.hpp - Generic Exception handling.
//
// Author        : Vilas Kumar Chitrakaran
// Version       : 2.0.01 (Temmuz 2009)
// Compatibility : POSIX, GCC
//==============================================================================

#ifndef _ERRNOEXCEPTION_HPP_INCLUDED
#define _ERRNOEXCEPTION_HPP_INCLUDED

#include "/usr/xenomai/include/posix/errno.h"
#include "/usr/xenomai/include/posix/unistd.h"
#include <string.h>

//==============================================================================
// class ErrnoExceptionXp
//------------------------------------------------------------------------------
// \brief
// A mechanism for basic run-time exception handling.
//
// <b>Example Program:</b>
// \include ErrnoException.t.cpp
//==============================================================================

class ErrnoExceptionXp
{
 public:
  inline ErrnoExceptionXp();
   // Standard constructor sets error to 0 (no error)
  
  inline ErrnoExceptionXp(int error, const char *desc=NULL);
   // This constructor allows initialization
   //  error  set integer error code. (0 reserved for no error)
   //  desc   set a short description [less than
   //         40 chars], possibly just the object that
   //         set the error.
   
  inline ErrnoExceptionXp(const ErrnoExceptionXp &e);
   // Copy constructor
   
  inline ErrnoExceptionXp &operator=(const ErrnoExceptionXp &e);
   // Assignment operation 
  
  ~ErrnoExceptionXp(){};
   // Destructor does nothing
   
  inline void setError(int error, const char *desc=NULL);
   // Set an error
   //  error  set integer error code. (0 reserved for no error)
   //  desc   set a short description [less than
   //         40 chars], possibly just the object that
   //         set the error.
   
  inline int getErrorCode() const;
   //  return  latest error code. (0 means no error).
   
  inline const char *getErrorDesc() const;
   //  return  any descriptive message that was set with the 
   //          error.  

  //======== END OF INTERFACE ========

 private:
  int d_errno;     // error number
  char d_desc[40]; // description
};


//==============================================================================
// ErrnoExceptionXp::ErrnoExceptionXp
//==============================================================================
ErrnoExceptionXp::ErrnoExceptionXp()
{
 d_errno = 0;
 d_desc[0]='\0';
}


ErrnoExceptionXp::ErrnoExceptionXp(int error, const char *desc)
{
 setError(error, desc);
}


ErrnoExceptionXp::ErrnoExceptionXp(const ErrnoExceptionXp &e)
{
 setError(e.getErrorCode(), e.getErrorDesc());
}


//==============================================================================
// ErrnoExceptionXp::operator=
//==============================================================================
ErrnoExceptionXp &ErrnoExceptionXp::operator=(const ErrnoExceptionXp &e) 
{
 setError(e.getErrorCode(), e.getErrorDesc());
 return *this;
}


//==============================================================================
// ErrnoExceptionXp::setError
//==============================================================================
void ErrnoExceptionXp::setError(int error, const char *desc)
{
 d_errno = error;
 if(desc)
  strncpy(d_desc, desc, 39);
 d_desc[39] = '\0';
}


//==============================================================================
// ErrnoExceptionXp::getErrorCode
//==============================================================================
int ErrnoExceptionXp::getErrorCode() const
{
 return d_errno;
}


//==============================================================================
// ErrnoExceptionXp::getErrorDesc
//==============================================================================
const char *ErrnoExceptionXp::getErrorDesc() const
{
 return d_desc;
}

#endif //_ErrnoExceptionXp_HPP_INCLUDED
