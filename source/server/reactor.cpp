#include "reactor.h"

#include <czmq.h>

#include "reactor_loop.h"

using namespace std;
using namespace zero_cache;

static const int kThreadCreationDelay = 1000 * 1000;

void Reactor::Start()
{
    if ( is_start_ )
        return;

    is_start_ = true;

    ReactorArgs args;
    args.debug = debug_;
    args.container = &container_;

    zthread_new(ReactorLoop, &args);

    usleep(kThreadCreationDelay);
}
