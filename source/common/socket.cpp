#include "socket.h"

using namespace std;
using namespace zero_cache;

Socket::Socket() : msg_(NULL)
{
    context_ = zctx_new ();
    socket_ = zsocket_new(context_, ZMQ_DEALER);

    zmq_pollitem_t items[1] = { { socket_, 0, ZMQ_POLLIN, 0 } };
    memcpy(&items_, &items, sizeof(items));
}

Socket::~Socket()
{
    zsocket_destroy(context_, socket_);
    zctx_destroy(&context_);
}
