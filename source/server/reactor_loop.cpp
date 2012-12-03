#include "reactor_loop.h"

#include "reactor.h"

using namespace zero_cache;

void* zero_cache::ReactorLoop(void* args)
{
    Reactor* reactor = static_cast<Reactor*>(args);

    while (true)
        reactor->ProcessMessage();
}
