#include "request.h"

#include <algorithm>
#include <assert.h>

#include "socket.h"
#include "functions.h"

using namespace std;
using namespace zero_cache;

Request::Request()
{
    Constructor();
}

Request::Request(const port_t id, const string& host)
{
    Constructor();

    MsgInitData(id_msg_, &id, sizeof(id));
    MsgInitString(host_msg_, host);
}

void Request::Constructor()
{
    zmq_msg_init(&command_msg_);
    zmq_msg_init(&id_msg_);
    zmq_msg_init(&host_msg_);
    zmq_msg_init(&key_msg_);
    zmq_msg_init(&data_msg_);
}

Request::~Request()
{
    zmq_msg_close(&data_msg_);
    zmq_msg_close(&key_msg_);
    zmq_msg_close(&host_msg_);
    zmq_msg_close(&id_msg_);
    zmq_msg_close(&command_msg_);
}

void Request::SetCommand(Command command)
{
    MsgInitData(command_msg_, &command, sizeof(command));
}

void Request::SetKey(const string& key)
{
    MsgInitString(key_msg_, key);
}

void Request::SetData(const void* data, const size_t size)
{
    MsgInitData(data_msg_, data, size);
}

port_t Request::GetId() const
{
    return MsgToPort(id_msg_);
}

string Request::GetHost() const
{
    return MsgToString(host_msg_);
}

Command& Request::GetCommand() const
{
    Command* command = static_cast<Command*>(ZmqMsgData(command_msg_));

    return *command;
}

string Request::GetKey() const
{
    assert( ZmqMsgSize(key_msg_) != 0 );
    return MsgToString(key_msg_);
}

zmq_msg_t& Request::GetData() const
{
    assert( ZmqMsgSize(data_msg_) != 0 );
    return data_msg_;
}

typedef pair<const zmq_msg_t*, int> Message;

BINARY_FUNCTOR(SendMsg, Message, msg, Socket&, socket)
    socket.SendMsg(*msg.first, msg.second);
END_BINARY_FUNCTOR

void Request::Send(const Socket& socket) const
{
    typedef list<Message> MsgQueue;
    MsgQueue queue;
    queue.push_back(MsgQueue::value_type(&command_msg_, ZMQ_SNDMORE));
    queue.push_back(MsgQueue::value_type(&id_msg_, ZMQ_SNDMORE));
    queue.push_back(MsgQueue::value_type(&host_msg_, ZMQ_SNDMORE));

    if ( ZmqMsgSize(key_msg_) != 0 )
        queue.push_back(MsgQueue::value_type(&key_msg_, ZMQ_SNDMORE));

    if ( ZmqMsgSize(data_msg_) != 0 )
        queue.push_back(MsgQueue::value_type(&data_msg_, ZMQ_SNDMORE));

    queue.back().second = 0;

    for_each(queue.begin(), queue.end(),
             bind2nd(SendMsg(), socket));
}

void Request::Receive(Socket& socket)
{
    socket.ReceiveMsg();

    bool is_msg_more = true;

    socket.PopMsg(command_msg_);
    socket.PopMsg(id_msg_);
    is_msg_more = socket.PopMsg(host_msg_);

    if ( is_msg_more )
         is_msg_more = socket.PopMsg(key_msg_);

    if ( is_msg_more )
        socket.PopMsg(data_msg_);
}
