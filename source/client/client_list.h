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

    Client* GetClient(std::string& key);

    void AddKey(std::string& key, port_t port);
    void CreateClient(port_t port);

    bool IsKeyExist(std::string& key);

    void SetHost(std::string host);
    void SetQueueSize(int size);

private:
    Connection connection_;
    SocketType type_;
    int queue_size_;
    std::string host_;
    KeyPort ports_;
    PortClient clients_;

    bool IsPortExist(port_t port);
};

}

#endif
