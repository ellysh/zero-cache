#include "client_list.h"

using namespace std;
using namespace zero_cache;

ClientList::ClientList()
{
}

Client* ClientList::GetClient(string key)
{
}

void ClientList::AddKey(string key, int port)
{
}

void ClientList::AddClient(int port, Client* client)
{
}

bool ClientList::IsPortExist(int port)
{
    return false;
}

bool ClientList::IsKeyExist(string key)
{
    return false;
}
