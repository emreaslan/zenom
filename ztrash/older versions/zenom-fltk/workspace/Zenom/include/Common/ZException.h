/*
 * ZException.h
 *
 *  Created on: Dec 22, 2010
 *      Author: root
 */

#ifndef ZEXCEPTION_H_
#define ZEXCEPTION_H_

#include <iostream>
#include <signal.h>
#include "ZString.h"

class ZException:public std::exception
{
public:
	ZException(ZString def) : info(def)
	{

	}
	virtual ~ZException() throw()
	{
	}
	virtual const char* what() const throw()
	{
		return info.c_str();
	}
private:
	ZString info;
};

#define DEFINE_ZEXCEPTION(_EXNAME,_DEFINITION) class _EXNAME: public ZException \
{ \
public: \
	_EXNAME(ZString def=#_DEFINITION): ZException(def){}\
	~_EXNAME()throw () {} \
};

DEFINE_ZEXCEPTION(ZTestException, This is a test exception)
DEFINE_ZEXCEPTION(ZInvalidMemory, Invalid memory segment access)
DEFINE_ZEXCEPTION(ZFloatingPointException, Erroneous arithmetic operation)
DEFINE_ZEXCEPTION(ZTerminalStopSignal, Terminal stop signal)
DEFINE_ZEXCEPTION(ZOutOfRange, Array length is out of range)

#endif /* ZEXCEPTION_H_ */
