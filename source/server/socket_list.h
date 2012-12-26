#ifndef SOCKET_LIST_H
#define SOCKET_LIST_H

#include <map>

#include "types_zcache.h"

namespace zero_cache
{

class Socket;

class SocketList
{
private:
    typedef std::map<port_t, Socket*> PortSocket;

public:
    SocketList();
    ~SocketList();

private:
    PortSocket sockets_;
};

}

#endif
