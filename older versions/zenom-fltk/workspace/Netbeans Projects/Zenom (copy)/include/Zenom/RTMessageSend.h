/* 
 * File:   MessageSend.h
 * Author: Cuneyt AY
 *
 * Created on September 10, 2009, 1:53 PM
 */

#ifndef _RTMESSAGESEND_H
#define	_RTMESSAGESEND_H

#include "RTMessage.h"

class RTMessageSend : public RTMessage
{
public:

    ~RTMessageSend(){} 

    virtual void communicate();
    
private:

};

#endif	/* _MESSAGESEND_H */

