#include "answer.h"

#include <assert.h>

#include "socket.h"
#include "functions.h"

using namespace std;
using namespace zero_cache;

Answer::Answer()
{
    zmq_msg_init(&msg_);
}

Answer::~Answer()
{
    zmq_msg_close(&msg_);
}

void Answer::SetPort(port_t port)
{
    MsgInitData(msg_, &port, sizeof(port));
}

void Answer::SetKeys(KeyArray& keys)
{
    MsgInitData(msg_, &keys[0], keys.size());
}

void Answer::SetData(zmq_msg_t* data)
{
    zmq_msg_copy(&msg_, data);
}

port_t Answer::GetPort()
{
    return MsgToPort(msg_);
}

KeyArray Answer::GetKeys()
{
    return MsgToKeyArray(msg_);
}

zmq_msg_t& Answer::GetData()
{
    assert( zmq_msg_size(&msg_) != 0 );
    return msg_;
}

void Answer::Send(Socket& socket)
{
    socket.SendMsg(msg_, 0);
}

bool Answer::Receive(Socket& socket, long timeout)
{
    if ( ! socket.ReceiveMsg(timeout) )
        return false;

    socket.PopMsg(msg_);

    return true;
}
