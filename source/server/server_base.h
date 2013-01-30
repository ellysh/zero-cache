#ifndef SERVER_BASE_H
#define SERVER_BASE_H

#include "debug.h"
#include "socket.h"
#include "types_zcache.h"
#include "request.h"
#include "answer.h"

namespace zero_cache
{

class ServerBase : protected Debug
{
public:
    ServerBase(const char* log_file, Connection connection, SocketType type = kDealer);
    virtual ~ServerBase() {};

    void Start();

    virtual void SetQueueSize(int size) = 0;

protected:
    Socket socket_;
    Request request_;
    Answer answer_;

    virtual void ProcessMessage() = 0;
};

}

#endif
