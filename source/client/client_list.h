#ifndef CLIENT_LIST_H
#define CLIENT_LIST_H

#include <string>
#include <map>

#include "connection.h"
#include "types_zcache.h"

namespace zero_cache
{

class Client;

class ClientList
{
public:
    typedef std::map<std::string, port_t> KeyPort;
    typedef std::map<port_t, Client*> PortClient;

public:
    ClientList(Connection& connection, SocketType type);
    ~ClientList();

    Client* GetClient(const std::string& key) const;

    void AddKey(const std::string& key, const port_t port);
    void CreateClient(const port_t port);

    bool IsKeyExist(const std::string& key) const;

    void SetHost(const std::string host);
    void SetQueueSize(const int size);

private:
    Connection connection_;
    SocketType type_;
    int queue_size_;
    std::string host_;
    mutable KeyPort ports_;
    mutable PortClient clients_;

    bool IsPortExist(const port_t port) const;

    DISALLOW_COPY_AND_ASSIGN(ClientList);
};

}

#endif
