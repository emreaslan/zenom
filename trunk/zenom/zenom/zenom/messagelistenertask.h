#ifndef MESSAGELISTENERTASK_H_
#define MESSAGELISTENERTASK_H_

#include <TaskXn.h>
#include "zenom.h"
class Zenom;

class MessageListenerTask: public TaskXn
{
public:
    MessageListenerTask(Zenom* pZenom);

    virtual void run();

private:
    Zenom* mZenom;
};

#endif /* MESSAGELISTENERTASK_H_ */
