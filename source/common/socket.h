#ifndef SOCKET_H
#define SOCKET_H

#include <string>
#include <czmq.h>

#include "types_zcache.h"

namespace zero_cache
{

class Connection;

class Socket
{
public:
    explicit Socket(SocketType type = kDealer);
    virtual ~Socket();

    void Connect(Connection& connection);
    void Bind(Connection& connection);

    void SendFrame(zframe_t* frame, int flags);

    bool ReceiveMsg(long timeout = -1);
    zframe_t* PopFrame();

    void SetQueueSize(int size);

private:
    zmsg_t* msg_;
    zctx_t* context_;
    void* in_socket_;
    void* out_socket_;
    zmq_pollitem_t items_[1];

    DISALLOW_COPY_AND_ASSIGN(Socket)
};

}

#endif
