#include "socket.h"

#include "zsignal.h"

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

void Socket::Connect(string connection)
{
    zsocket_connect(socket_, connection.c_str());
}

void Socket::Bind(string connection)
{
    zsocket_bind(socket_, connection.c_str());
}

bool Socket::ReceiveMsg(long timeout)
{
    if ( msg_ != NULL )
        zmsg_destroy(&msg_);

    int result = zmq_poll(items_, 1, timeout);

    if ( result == 0 )
        return false;

    if (result == -1)
    {
        if ( zmq_errno() == ERR_INTERRUPT )
            exit(0);
    }

    if ( ! (items_[0].revents & ZMQ_POLLIN) )
        return false;

    msg_ = zmsg_recv(socket_);
    assert( msg_ != NULL );
    return true;
}

zframe_t* Socket::PopFrame()
{
    return zmsg_pop(msg_);
}

void Socket::SendFrame(zframe_t* frame, int flags)
{
    zframe_send(&frame, socket_, flags);
}

void Socket::SendString(string data)
{
    zstr_sendf(socket_, data.c_str());
}

void Socket::SetQueueSize(int size)
{
    zsocket_set_hwm(socket_, size);
}
