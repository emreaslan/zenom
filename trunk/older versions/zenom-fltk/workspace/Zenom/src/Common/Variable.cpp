//==============================================================================
// Variable.cpp - Variable implementasyonu
//
// Author        : 
// Version       : 
// Compatibility : GCC
//==============================================================================

#include "Variable.h"

//==============================================================================
// Variable::Variable
//==============================================================================
Variable::Variable(double* addr,const char* nm, const char* desc , int nRow , int nCol)
{
    address = addr;
    isInt =false;

    name = new char[ strlen( nm ) + 1 ];
    strcpy( name, nm );

    rows = nRow;
    cols = nCol;
    size = rows * cols ;

    setDescription( desc );
}


//==============================================================================
// Variable::Variable
//==============================================================================
Variable::Variable(int* addr,const char* nm, const char* desc , int nRow , int nCol)
{
    intAddress = addr;
    isInt = true;

    name = new char[ strlen( nm ) + 1 ];
    strcpy( name, nm );

    rows = nRow ;
    cols = nCol ;
    size = cols * rows ;

    setDescription( desc );
}

//==============================================================================
// Variable::~Variable
//==============================================================================
Variable::~Variable()
{
    delete[] name;
    delete[] description;
}

//==============================================================================
// Variable::setDescription
//==============================================================================
void Variable::setDescription (const char *desc)
{
    if( desc != NULL )
    {
        description = new char[ strlen( desc ) + 1 ];
        strcpy( description, desc );
    }
}

//==============================================================================
// Variable::setElement
//==============================================================================
void Variable::setElement(int index, double value)
{
    if(isInt)
        intAddress[index] = (int)value;
    else
        address[index] = value;
}

//==============================================================================
// Variable::setElement
//==============================================================================
void Variable::setElement(int row, int col, double value)
{
    setElement(row * cols + col, value);
}
