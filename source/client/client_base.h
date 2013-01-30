#ifndef CLIENT_BASE_H
#define CLIENT_BASE_H

#include <string>
#include <zmq.h>

#include "debug.h"
#include "types_zcache.h"
#include "socket.h"

namespace zero_cache
{

class Connection;
class Request;

class ClientBase : protected Debug
{
public:
    ClientBase(const char* log_file, Connection connection, SocketType type);
    virtual ~ClientBase();

    virtual void SetQueueSize(int size) = 0;

    virtual void SetHost(std::string host);

protected:
    Socket socket_;
    Request* request_;
    port_t* id_;

private:
    DISALLOW_COPY_AND_ASSIGN(ClientBase);
};

}

#endif
