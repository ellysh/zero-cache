#ifndef REACTOR_LOOP_H
#define REACTOR_LOOP_H

#include <czmq.h>

namespace zero_cache
{

class Debug;
class Container;

struct ReactorArgs
{
    Debug* debug;
    Container* container;
    void* socket;
    zmq_pollitem_t items[1];
    zctx_t* context;
};

void* ReactorLoop(void* reactor_args);

}

#endif
