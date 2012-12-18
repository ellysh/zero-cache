#include "client_list.h"

#include <algorithm>

#include "client.h"

using namespace std;
using namespace zero_cache;

ClientList::ClientList()
{
}

static void RemoveClient(ClientList::PortClient::value_type client_pair)
{
    delete client_pair.second;
}

ClientList::~ClientList()
{
    for_each(clients_.begin(), clients_.end(),
             RemoveClient);

    clients_.clear();
}

Client* ClientList::GetClient(string key)
{
    if ( ! IsKeyExist(key) )
        return NULL;

    int port = ports_[key];

    if ( ! IsPortExist(port) )
        return NULL;

    return clients_[port];
}

void ClientList::AddKey(string key, int port)
{
    ports_.insert(KeyPort::value_type(key, port));
}

void ClientList::AddClient(int port, Client* client)
{
    clients_.insert(PortClient::value_type(port, client));
}

bool ClientList::IsPortExist(int port)
{
    if ( clients_.count(port)  != 0 )
        return true;
    else
        return false;
}

bool ClientList::IsKeyExist(string key)
{
    if ( ports_.count(key) != 0 )
        return true;
    else
        return false;
}
