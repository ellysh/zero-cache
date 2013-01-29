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

class ClientBase : protected Debug
{
public:
    ClientBase(const char* log_file, Connection connection, SocketType type);
    virtual ~ClientBase();

    virtual void SetQueueSize(int size) = 0;
    virtual void SetHost(std::string host);

private:
    Socket socket_;
    zmq_msg_t host_msg_;
    zmq_msg_t id_msg_;
    zmq_msg_t command_msg_;
    zmq_msg_t key_msg_;

    DISALLOW_COPY_AND_ASSIGN(ClientBase);
};

}

#endif
