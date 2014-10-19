

#include "RTMessage.h"


//==============================================================================
// Message::Message
//==============================================================================
RTMessage::RTMessage()
{
    ipAddress = NULL;
    mMessageSize = 0;
}

//==============================================================================
// Message::~Message
//==============================================================================
RTMessage::~RTMessage()
{
    if(ipAddress)
        delete[] ipAddress;
        
    for (int i = 0 ; i < variableArray.getNumElements() ; ++i )
        delete variableArray.getElement(i);

    udp.close();
}

//==============================================================================
// Message::initialize
//==============================================================================
int RTMessage::initialize(int port, char* ip)
{
    if(ipAddress)
    {
        delete[] ipAddress;    
    }
    
    int length = strlen(ip);
    ipAddress = new char[length];
    strcpy(ipAddress, ip);
    
    udp.bind(port);
    inet_aton(ip, &ipAddr);

    // Mesajin gidecegi adres ayarlanir.
    memset(&sockAddr, 0, sizeof(struct sockaddr_in));
    sockAddr.sin_family = AF_INET;
    sockAddr.sin_port = htons(port);
    sockAddr.sin_addr = ipAddr;

    udp.setTimeout(1000000000);
    udp.extendPool(2048);

    return udp.getErrnoError();
}


//==============================================================================
// Message::add
//==============================================================================
bool RTMessage::add(double *variable, int row,int col)
{
    if ( (mMessageSize + row*col) >= MESSAGESIZE )
        return false;

    Variable *ptr = new Variable( variable, "" , "", row, col );
    variableArray.appendElement(ptr);
    mMessageSize += row*col;

    return true;
}

//==============================================================================
// Message::add
//==============================================================================
bool RTMessage::add(int *variable,int row,int col)
{
     if ( (mMessageSize + row*col) >= MESSAGESIZE )
        return false;
    Variable *ptr = new Variable( variable, "" ,"" , row ,col );
    variableArray.appendElement(ptr);
    mMessageSize += row*col;

    return true;
}


//==============================================================================
// Message::add
//==============================================================================
bool RTMessage::add(double **variable,int row,int col)
{
     if ( (mMessageSize + row*col) >= MESSAGESIZE )
        return false;
    Variable *ptr = new Variable( &(variable[0][0]), "" ,"" , row ,col );
    variableArray.appendElement(ptr);
    mMessageSize += row*col;

    return true;
}


//==============================================================================
// Message::add
//==============================================================================
bool RTMessage::add(int **variable, int row,int col)
{
    if ( (mMessageSize + row*col) >= MESSAGESIZE )
        return false;
    Variable *ptr = new Variable( &(variable[0][0]), "" ,"" , row ,col );
    variableArray.appendElement(ptr);
    mMessageSize += row*col;

    return true;
}


//==============================================================================
// Message::add
//==============================================================================
bool RTMessage::add(int &variable, int row,int col)
{
     if ( (mMessageSize + row*col) >= MESSAGESIZE )
        return false;

    Variable *ptr = new Variable(&variable, "", "", row, col);
    variableArray.appendElement(ptr);
    mMessageSize += row*col;

    return true;
}

//==============================================================================
// Message::add
//==============================================================================
bool RTMessage::add(double &variable)
{
    return  add( &variable,1,1);
}


//==============================================================================
// Message::add
//==============================================================================
bool RTMessage::add(MatrixBase<double>& varMatrix)
{
     if ( (mMessageSize + varMatrix.getNumRows()*varMatrix.getNumColumns()) >= MESSAGESIZE )
        return false;

    Variable *ptr = new Variable( varMatrix.getElementsPointer() , "" ,"" , varMatrix.getNumRows() , varMatrix.getNumColumns() );
    variableArray.appendElement(ptr);
    mMessageSize += varMatrix.getNumRows()*varMatrix.getNumColumns();

    return true;
}

//==============================================================================
// RTMessage::add
//==============================================================================
bool RTMessage::add(MatrixBase<int>& varMatrix)
{
    if ( (mMessageSize + varMatrix.getNumRows()*varMatrix.getNumColumns()) >= MESSAGESIZE )
        return false;
    
    Variable *ptr = new Variable( varMatrix.getElementsPointer() , "", "" , varMatrix.getNumRows() , varMatrix.getNumColumns() );
    variableArray.appendElement(ptr);
    mMessageSize += varMatrix.getNumRows()*varMatrix.getNumColumns();

    return true;
}

//==============================================================================
// RTMessage::setTimeout
//==============================================================================
void RTMessage::setTimeout( RTIME timeout )
{
    udp.setTimeout(timeout);
}
