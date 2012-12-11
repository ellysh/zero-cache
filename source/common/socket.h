#ifndef SOCKET_H
#define SOCKET_H

#include <string>
#include <czmq.h>

#include "types_zcache.h"

namespace zero_cache
{

class Socket
{
public:
    Socket();
    virtual ~Socket();

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
    void* socket_;
    zmq_pollitem_t items_[1];

    DISALLOW_COPY_AND_ASSIGN(Socket)
};

}

#endif
