/* 
 * File:   MessageRecv.h
 * Author: root
 *
 * Created on September 10, 2009, 1:55 PM
 */

#ifndef _RTMESSAGERECV_H
#define	_RTMESSAGERECV_H

#include "RTMessage.h"

class RTMessageRecv : public RTMessage
{

public:
    
    RTMessageRecv();

    ~RTMessageRecv() {}

    virtual void communicate();

private:

};

#endif	/* _MESSAGERECV_H */

