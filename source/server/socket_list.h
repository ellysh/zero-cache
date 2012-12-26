#ifndef SOCKET_LIST_H
#define SOCKET_LIST_H

#include <map>

#include "types_zcache.h"

namespace zero_cache
{

class Socket;
class Connection;

class SocketList
{
public:
    typedef std::map<port_t, Socket*> PortSocket;

public:
    /* FIXME: Pass socket type to the constructor */
    SocketList() {};
    ~SocketList();

    void CreateSocket(Connection& connection, port_t port);
    Socket& GetSocket(port_t port);

private:
    PortSocket sockets_;
};

}

#endif
