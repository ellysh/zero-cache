#include "key_list.h"

#include <stdlib.h>
#include <stdio.h>

using namespace std;
using namespace zero_cache;

KeyList::KeyList(string connection)
{
    size_t pos = connection.find_last_of('/') + 1;
    string port = connection.substr(pos, connection.size());

    current_port_ = atoi(port.c_str());
    current_port_++;

    host_= connection.substr(0, pos);
}

KeyList::~KeyList()
{
    /* FIXME: Free memory allocated for all Connection structures in
     * connections_ map */
    connections_.clear();
}

void KeyList::AddKey(string key)
{
    if ( connections_.count(key) != 0 )
        return;

    char port[10];
    sprintf(port, "%d", current_port_);

    string connection = host_;
    connection += port;

    connections_.insert(KeyConnection::value_type(key, connection));

    /* FIXME: Increment current port on key count limit */
    current_port_++;
}

string KeyList::GetConnection(string key)
{
    if ( connections_.count(key) != 0 )
        return connections_[key];
    else
        return "";
}

bool KeyList::IsKeyExist(string key)
{
    if ( connections_.count(key) != 0 )
        return true;
    else
        return false;
}
