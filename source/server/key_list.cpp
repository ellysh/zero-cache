#include "key_list.h"

#include <stdlib.h>
#include <stdio.h>

using namespace std;
using namespace zero_cache;

KeyList::KeyList(string start_port)
{
    current_port_ = atoi(start_port.c_str());
    current_port_++;
}

void KeyList::AddKey(string key)
{
    char port[10];
    sprintf(port, "%d", current_port_);

    ports_.insert(KeyPort::value_type(key, port));

    /* FIXME: Increment current port on key count limit */
}

string KeyList::GetConnection(string key)
{
    if ( ports_.count(key) != 0 )
        return ports_[key];
    else
        return "";
}
