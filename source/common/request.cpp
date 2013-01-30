#include "request.h"

#include "socket.h"
#include "functions.h"

using namespace std;
using namespace zero_cache;

Request::Request()
{
    Constructor();
}

Request::Request(port_t id, string& host)
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

void Request::SetKey(string& key)
{
    MsgInitString(key_msg_, key);
}

void Request::SetData(void* data, size_t size)
{
    MsgInitData(data_msg_, data, size);
}

Command& Request::GetCommand()
{
    Command* command = (Command*)zmq_msg_data(&command_msg_);

    return *command;
}

string Request::GetKey()
{
    return MsgToString(key_msg_);
}

zmq_msg_t& Request::GetData()
{
    return data_msg_;
}

void Request::Send(Socket& socket)
{
    /* FIXME: Refactoring this method */

    socket.SendMsg(command_msg_, ZMQ_SNDMORE);
    socket.SendMsg(id_msg_, ZMQ_SNDMORE);

    size_t key_size = zmq_msg_size(&key_msg_);

    if ( key_size != 0 )
        socket.SendMsg(host_msg_, ZMQ_SNDMORE);
    else
        socket.SendMsg(host_msg_, 0);

    size_t data_size = zmq_msg_size(&data_msg_);

    if ( (key_size != 0) && (data_size != 0) )
    {
        socket.SendMsg(key_msg_, ZMQ_SNDMORE);
        socket.SendMsg(data_msg_, 0);
    }
    else if ( key_size != 0 )
        socket.SendMsg(key_msg_, 0);
}

void Request::Receive(Socket& socket)
{
    /* FIXME: Add timeout for this receiving if this is needed */
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
