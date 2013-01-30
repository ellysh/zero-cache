#include "request.h"

#include "socket.h"
#include "functions.h"

using namespace std;
using namespace zero_cache;

Request::Request(port_t id, string& host)
{
    zmq_msg_init(&command_msg_);
    zmq_msg_init(&id_msg_);
    zmq_msg_init(&host_msg_);
    zmq_msg_init(&key_msg_);
    zmq_msg_init(&data_msg_);

    zmq_msg_init_data(&id_msg_, &id, sizeof(id), MsgDataFree, NULL);
    MsgInitString(host_msg_, host);
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

void Request::Send(Socket& socket)
{
    /* FIXME: Change messages sending order here */

    socket.SendMsgClear(command_msg_, ZMQ_SNDMORE);

    if ( zmq_msg_size(&key_msg_) != 0 )
        socket.SendMsgClear(key_msg_, ZMQ_SNDMORE);

    socket.SendMsg(id_msg_, ZMQ_SNDMORE);

    if ( zmq_msg_size(&data_msg_) != 0 )
    {
        socket.SendMsg(host_msg_, ZMQ_SNDMORE);
        socket.SendMsgClear(data_msg_, 0);
    }
    else
        socket.SendMsg(host_msg_, 0);
}

void Request::Receive(Socket& socket)
{
    /* FIXME: Implement this method */
}
