#include "socket.h"

#include <algorithm>

#include "zsignal.h"
#include "functions.h"
#include "connection.h"

using namespace std;
using namespace zero_cache;

Socket::Socket(SocketType type)
{
    context_ = zctx_new();

    if ( type == kDealer )
    {
        in_socket_ = zsocket_new(context_, ZMQ_DEALER);
        out_socket_ = zsocket_new(context_, ZMQ_DEALER);
    }
    else if (type == kPubSub)
    {
        in_socket_ = zsocket_new(context_, ZMQ_SUB);
        zmq_setsockopt(in_socket_, ZMQ_SUBSCRIBE, "", 0);
        out_socket_ = zsocket_new(context_, ZMQ_PUB);
    }

    zmq_pollitem_t items[1] = { { in_socket_, 0, ZMQ_POLLIN, 0 } };
    memcpy(&items_, &items, sizeof(items));
}

Socket::~Socket()
{
    ClearMessages();

    zsocket_destroy(context_, out_socket_);
    zsocket_destroy(context_, in_socket_);
    zctx_destroy(&context_);
}

static void CloseMessage(zmq_msg_t& msg)
{
    zmq_msg_close(&msg);
}

void Socket::ClearMessages()
{
    for_each(messages_.begin(), messages_.end(),
             CloseMessage);

    messages_.clear();
}

static Connection IncrementPort(Connection& connection)
{
    Connection result(connection);
    int port = connection.GetPort() + 1;
    result.SetPort(port);

    return result;
}

void Socket::ConnectOut(Connection& connection)
{
    zsocket_connect(out_socket_, connection.GetString().c_str());
}

void Socket::BindIn(Connection& connection)
{
    zsocket_bind(in_socket_, connection.GetString().c_str());
    SetPermission(connection.GetString().c_str());
}

bool Socket::ReceiveMsg(long timeout)
{
    ClearMessages();

    zmq_msg_t msg;
    zmq_msg_init(&msg);

    int result;

    do
    {
        result = zmq_poll(items_, 1, timeout);

        if ( result == 0 )
            return false;

        if (result == -1)
        {
            if ( zmq_errno() == ERR_INTERRUPT )
                exit(0);
        }

        if ( ! (items_[0].revents & ZMQ_POLLIN) )
            return false;

        zmq_msg_recv(&msg, in_socket_, 0);
        messages_.push_back(msg);
    }
    while ( zmq_msg_more(&msg) );

    return true;
}

bool Socket::PopMsg(zmq_msg_t& msg)
{
    if ( messages_.empty() )
        return false;

    zmq_msg_init(&msg);

    zmq_msg_copy(&msg, &messages_.front());

    messages_.pop_front();

    return true;
}

void Socket::SendMsg(zmq_msg_t& msg, int flags)
{
    size_t size = zmq_msg_size(&msg);

    zmq_msg_t send;
    zmq_msg_init_size(&send, size);

    memcpy(zmq_msg_data(&send), zmq_msg_data(&msg), size);

    zmq_msg_send(&send, out_socket_, flags);
}

void Socket::SetQueueSize(int size)
{
    zsocket_set_hwm(in_socket_, size);
    zsocket_set_hwm(out_socket_, size);
}
