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
    static SocketList* Instance(const SocketType type = kDealer);

    ~SocketList();

    void CreateSocket(const Connection& connection, const port_t port);
    Socket* GetSocket(const port_t port) const;

private:
    static SocketList* instance_;

    SocketType type_;
    mutable PortSocket sockets_;

    SocketList(const SocketType type = kDealer) : type_(type) {};
};

}

#endif
