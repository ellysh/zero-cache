#ifndef CLIENT_LIST_H
#define CLIENT_LIST_H

#include <string>
#include <map>

namespace zero_cache
{

class Client;

class ClientList
{
public:
    typedef std::map<std::string, int> KeyPort;
    typedef std::map<int, Client*> PortClient;

public:
    ClientList();
    ~ClientList();

    Client* GetClient(std::string key);

    void AddKey(std::string key, int port);
    void AddClient(int port, Client* client);

    bool IsPortExist(int port);
    bool IsKeyExist(std::string key);

private:
    KeyPort ports_;
    PortClient clients_;
};

}

#endif
