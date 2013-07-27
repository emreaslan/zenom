/* 
 * File:   ZParameter.h
 * Author: root
 *
 * Created on May 9, 2010, 7:23 AM
 */

#ifndef _ZPARAMETER_H
#define	_ZPARAMETER_H

enum ZParameterType
{
    Z_DOUBLE,
    Z_INTEGER,
    Z_BOOLEAN
};

struct ZParameter
{
    ZParameter()
    {}

    ZParameter(ZParameterType pType, void* pVariable)
    : type(pType), variable(pVariable)
    {}

    ZParameterType type;
    void* variable;
};

#endif	/* _ZPARAMETER_H */

