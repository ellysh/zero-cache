#ifndef REACTOR_LOOP_H
#define REACTOR_LOOP_H

namespace zero_cache
{

class Debug;
class Container;

struct ReactorArgs
{
    Debug* debug;
    Container* container;
};

void* ReactorLoop(void* args);

}

#endif
