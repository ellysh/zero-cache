#ifndef SOCKET_DOUBLE_H
#define SOCKET_DOUBLE_H

#include <string>
#include <czmq.h>

#include "types_zcache.h"

namespace zero_cache
{

class SocketDouble
{
public:
    SocketDouble();
    virtual ~SocketDouble();

    void Connect(std::string connection);
    void Bind(std::string connection);

    void SendFrame(zframe_t* frame, int flags);
    void SendString(std::string data);

    bool ReceiveMsg(long timeout = -1);
    zframe_t* PopFrame();

    void SetQueueSize(int size);

private:
    zmsg_t* msg_;
    zctx_t* context_;
    void* in_socket_;
    void* out_socket_;
    zmq_pollitem_t items_[1];

    DISALLOW_COPY_AND_ASSIGN(SocketDouble)
};

}

#endif
