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
    static SocketList* Instance(SocketType type = kDealer);

    ~SocketList();

    void CreateSocket(Connection& connection, port_t port);
    Socket& GetSocket(port_t port);

private:
    static SocketList* instance_;

    SocketType type_;
    PortSocket sockets_;

    SocketList(SocketType type = kDealer) : type_(type) {};
};

}

#endif
