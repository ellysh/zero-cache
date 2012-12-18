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
    typedef std::map<std::string, int> KeyPort;
    typedef std::map<int, Client*> PortClient;

public:
    ClientList(Connection& connection, SocketType type);
    ~ClientList();

    Client* GetClient(std::string& key);

    void AddKey(std::string& key, int port);
    void CreateClient(int port);

    bool IsKeyExist(std::string& key);

    void SetQueueSize(int size);

private:
    Connection connection_;
    SocketType type_;
    int queue_size_;
    KeyPort ports_;
    PortClient clients_;

    bool IsPortExist(int port);
};

}

#endif
