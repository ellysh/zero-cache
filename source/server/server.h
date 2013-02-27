#ifndef SERVER_H
#define SERVER_H

#include "debug.h"
#include "socket.h"
#include "types_zcache.h"
#include "request.h"
#include "answer.h"
#include "connection.h"

namespace zero_cache
{

class Server : protected Debug
{
public:
    Server(const char* log_file, Connection connection, const SocketType type = kDealer);
    virtual ~Server() {};

    void Start(long timeout = -1);

private:
    bool ProcessMessage(long timeout);
};

}

#endif
