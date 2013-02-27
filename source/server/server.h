#ifndef SERVER_H
#define SERVER_H

#include "debug.h"
#include "types_zcache.h"
#include "connection.h"

namespace zero_cache
{

class Server : protected Debug
{
public:
    Server(const char* log_file, Connection connection, const SocketType type = kDealer);
    virtual ~Server() {};

    /* FIXME: Remove the timeout parameter */
    void Start(const long timeout = -1);

private:
    /* FIXME: Remove the timeout parameter */
    bool ProcessMessage(const long timeout);
};

}

#endif
