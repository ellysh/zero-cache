#ifndef SERVER_BASE_H
#define SERVER_BASE_H

#include "debug.h"
#include "socket.h"
#include "types_zcache.h"
#include "request.h"
#include "answer.h"
#include "connection.h"

namespace zero_cache
{

class ServerBase : protected Debug
{
public:
    ServerBase(const char* log_file, Connection connection, SocketType type = kDealer);
    virtual ~ServerBase() {};

    virtual void SetQueueSize(int size) = 0;

    void Start();

protected:
    Socket socket_;
    Connection connection_;
    Request request_;
    Answer answer_;

    virtual void PerformCommand() = 0;

    void ProcessMessage();

private:
    DISALLOW_COPY_AND_ASSIGN(ServerBase)
};

}

#endif
