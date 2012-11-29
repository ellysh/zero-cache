#include "reactor.h"

#include <czmq.h>

#include "debug.h"

using namespace std;
using namespace zero_cache;

static const int kThreadCreationDelay = 1000 * 1000;

struct ReactorArgs
{
    Debug* debug;
    Container* container;
};

static void* ReactorLoop(void* args)
{
    ReactorArgs* reactor = static_cast<ReactorArgs*>(args);
    Debug* debug = reactor->debug;
    Container* container = reactor->container;

    zctx_t* ctx = zctx_new ();
    void* receiver = zsocket_new (ctx, ZMQ_DEALER);
    zsocket_bind(receiver, "tcp://*:5570");
    zsocket_set_hwm(receiver, 1000);

    zmq_pollitem_t items[] = { { receiver, 0, ZMQ_POLLIN, 0 } };
    while (true)
    {
        zmq_poll(items, 1, -1);
        if ( items[0].revents & ZMQ_POLLIN )
        {
            string data = zstr_recv(receiver);
            debug->Log() << "data = " << data << endl;
        }
    }
    zctx_destroy(&ctx);
}

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
