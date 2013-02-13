#include "key_list.h"

#include <algorithm>

#include <stdlib.h>
#include <stdio.h>

#include "connection.h"

using namespace std;
using namespace zero_cache;

KeyList::KeyList(const Connection& connection) : key_counter_(0)
{
    current_port_ = connection.GetPort() + 1;
}

KeyList::~KeyList()
{
    ports_.clear();
}

void KeyList::AddKey(const string& key)
{
    if ( ports_.count(key) != 0 )
        return;

    if ( key_counter_ < key_limit_ )
        key_counter_++;
    else
    {
        current_port_++;
        key_counter_ = 1;
    }

    ports_.insert(KeyPort::value_type(key, current_port_));
}

port_t KeyList::GetPort(const string& key) const
{
    if ( ports_.count(key) != 0 )
        return ports_[key];
    else
        return kErrorPort;
}

BINARY_FUNCTOR(AddKeyArray, KeyList::KeyPort::value_type, port_pair, string&, keys)
    keys += port_pair.first;
    keys += ';';
END_BINARY_FUNCTOR

string KeyList::GetKeys() const
{
    string keys;

    for_each(ports_.begin(), ports_.end(),
             bind2nd(AddKeyArray(), keys));

    return keys;
}

void KeyList::SetKeyLimit(const int key_limit)
{
    key_limit_ = key_limit;
}
