#include "reactor.h"

#include <czmq.h>

#include "debug.h"
#include "types.h"

using namespace std;
using namespace zero_cache;

static const int kThreadCreationDelay = 1000 * 1000;

struct ReactorArgs
{
    Debug* debug;
    Container* container;
};

static Command GetCommand(zframe_t* frame)
{
    Command command = kSet;
    zframe_t* set_frame = zframe_new(&command, sizeof(Command));

    if ( zframe_eq(frame, set_frame) )
        return kSet;
    else
        return kGet;
}

static void* ReactorLoop(void* args)
{
    /* FIXME: Split this function to sub-functions */
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
            zmsg_t* msg = zmsg_recv(receiver);
            zframe_t* command = zmsg_pop(msg);
            zframe_t* key = zmsg_pop(msg);
            zframe_t* data = zmsg_pop(msg);

            if ( GetCommand(command) == kSet )
            {
                debug->Log() << "set: key = " << zframe_strdup(key) << " data = " << zframe_strhex(data) << endl;
                container->WriteData(zframe_strdup(key), zframe_dup(data));
            }

            zmsg_destroy(&msg);
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
