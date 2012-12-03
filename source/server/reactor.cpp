#include "reactor.h"

#include <czmq.h>

#include "reactor_loop.h"

using namespace std;
using namespace zero_cache;

static const int kThreadCreationDelay = 1000 * 1000;

Reactor::Reactor(string log_file) : DebugClient(log_file), is_start_(false)
{
    args_.debug = debug_;
    args_.container = &container_;

    args_.context = zctx_new ();
    args_.socket = zsocket_new(args_.context, ZMQ_DEALER);

    zsocket_bind(args_.socket, "tcp://*:5570");
    zsocket_set_hwm(args_.socket, 1000);

    zmq_pollitem_t items[1] = { { args_.socket, 0, ZMQ_POLLIN, 0 } };
    memcpy(&args_.items, &items, sizeof(items));
}

Reactor::~Reactor()
{
    zsocket_destroy(args_.context, args_.socket);
    zctx_destroy(&args_.context);
}

void Reactor::Start()
{
    if ( is_start_ )
        return;

    is_start_ = true;

    zthread_new(ReactorLoop, &args_);

    usleep(kThreadCreationDelay);
}
