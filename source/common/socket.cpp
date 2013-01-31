#include "socket.h"

#include <algorithm>
#include <string.h>

#include "interrupt_signal.h"
#include "functions.h"
#include "connection.h"

using namespace std;
using namespace zero_cache;

Socket::Socket(SocketType type)
{
    context_ = zmq_ctx_new();

    if ( type == kDealer )
    {
        in_socket_ = zmq_socket(context_, ZMQ_DEALER);
        out_socket_ = zmq_socket(context_, ZMQ_DEALER);
    }
    else if (type == kPubSub)
    {
        in_socket_ = zmq_socket(context_, ZMQ_SUB);
        zmq_setsockopt(in_socket_, ZMQ_SUBSCRIBE, "", 0);
        out_socket_ = zmq_socket(context_, ZMQ_PUB);
    }

    zmq_pollitem_t items[1] = { { in_socket_, 0, ZMQ_POLLIN, 0 } };
    memcpy(&items_, &items, sizeof(items));
}

Socket::~Socket()
{
    ClearMessages();

    zmq_close(out_socket_);
    zmq_close(in_socket_);
    zmq_ctx_destroy(context_);
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

void Socket::ConnectOut(const Connection& connection)
{
    zmq_connect(out_socket_, connection.GetString().c_str());
}

void Socket::BindIn(const Connection& connection)
{
    zmq_bind(in_socket_, connection.GetString().c_str());
    SetPermission(connection.GetString().c_str());
}

bool Socket::ReceiveMsg(const long timeout)
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

void Socket::SendMsg(const zmq_msg_t& msg, const int flags) const
{
    size_t size = ZmqMsgSize(msg);

    zmq_msg_t send;
    zmq_msg_init_size(&send, size);

    memcpy(zmq_msg_data(&send), ZmqMsgData(msg), size);

    zmq_msg_send(&send, out_socket_, flags);
}

void Socket::SetQueueSize(const int size)
{
    zmq_setsockopt(in_socket_, ZMQ_SNDHWM, &size, sizeof(size));
    zmq_setsockopt(in_socket_, ZMQ_RCVHWM, &size, sizeof(size));

    zmq_setsockopt(out_socket_, ZMQ_SNDHWM, &size, sizeof(size));
    zmq_setsockopt(out_socket_, ZMQ_RCVHWM, &size, sizeof(size));
}
