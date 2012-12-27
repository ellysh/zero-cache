#include "client_list.h"

#include <algorithm>

#include "client.h"

using namespace std;
using namespace zero_cache;

static const long kInitServerDelay = 1000;

ClientList::ClientList(Connection& connection, SocketType type) : connection_(connection), type_(type), queue_size_(10)
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

Client* ClientList::GetClient(string& key)
{
    if ( ! IsKeyExist(key) )
        return NULL;

    int port = ports_[key];

    if ( ! IsPortExist(port) )
        return NULL;

    return clients_[port];
}

void ClientList::AddKey(string& key, port_t port)
{
    ports_.insert(KeyPort::value_type(key, port));
}

void ClientList::CreateClient(port_t port)
{
    Connection connection(connection_);
    connection.SetPort(port);

    if ( ! IsPortExist(port) )
    {
        Client* client = new Client("", connection, type_);
        client->SetHost(host_);
        client->SetQueueSize(queue_size_);
        clients_.insert(PortClient::value_type(port, client));

        usleep(kInitServerDelay);
    }
}

bool ClientList::IsPortExist(port_t port)
{
    if ( clients_.count(port) != 0 )
        return true;
    else
        return false;
}

bool ClientList::IsKeyExist(string& key)
{
    if ( ports_.count(key) != 0 )
        return true;
    else
        return false;
}

void ClientList::SetHost(string host)
{
    host_ = host;
}

void ClientList::SetQueueSize(int size)
{
    queue_size_ = size;
}
