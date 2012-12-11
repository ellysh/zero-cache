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

void Socket::Bind(string connection)
{
    zsocket_bind(socket_, connection.c_str());

    /* FIXME: Set queue size through separate function */
    zsocket_set_hwm(socket_, 1);
}

void Socket::ReceiveMsg()
{
    if ( msg_ != NULL )
        zmsg_destroy(&msg_);

    if ( zmq_poll(items_, 1, -1) == -1 )
    {
        //Log() << "Registrar::ProcessMessage() - error = " << zmq_strerror(zmq_errno()) << " (" << zmq_errno() << ")" << endl;
        if ( zmq_errno() == ERR_INTERRUPT )
            exit(0);
    }

    if ( ! (items_[0].revents & ZMQ_POLLIN) )
        return;

    msg_ = zmsg_recv(socket_);
    assert( msg_ != NULL );
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
