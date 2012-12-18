#ifndef CLIENT_LIST_H
#define CLIENT_LIST_H

#include <string>

namespace zero_cache
{

class Client;

class ClientList
{
public:
    ClientList();

    /* FIXME: Add constructo to remove Client objects pointers */

    Client* GetClient(std::string key);

    void AddKey(std::string key, int port);
    void AddClient(int port, Client* client);

    bool IsPortExist(int port);
    bool IsKeyExist(std::string key);
};

}

#endif
