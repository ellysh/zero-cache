#ifndef SOCKET_H
#define SOCKET_H

#include <string>
#include <list>
#include <czmq.h>

#include "types_zcache.h"

namespace zero_cache
{

class Connection;

class Socket
{
public:
    typedef std::list<zmq_msg_t> MsgList;

public:
    explicit Socket(SocketType type = kDealer);
    virtual ~Socket();

    void ConnectOut(Connection& connection);
    void BindIn(Connection& connection);

    void SendMsg(zmq_msg_t& msg, int flags);

    bool ReceiveMsg(long timeout = -1);
    bool PopMsg(zmq_msg_t& msg);

    void SetQueueSize(int size);

private:
    MsgList messages_;
    zctx_t* context_;
    void* in_socket_;
    void* out_socket_;
    zmq_pollitem_t items_[1];

    void ClearMessages();

    DISALLOW_COPY_AND_ASSIGN(Socket)
};

}

#endif
