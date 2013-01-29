#include "key_list.h"

#include <algorithm>

#include <stdlib.h>
#include <stdio.h>

#include "connection.h"

using namespace std;
using namespace zero_cache;

static void RemovePort(KeyList::KeyPort::value_type& port_pair)
{
    delete port_pair.second;
}

KeyList::~KeyList()
{
    for_each(ports_.begin(), ports_.end(),
             RemovePort);

    ports_.clear();
}

void KeyList::AddKey(string& key)
{
    if ( ports_.count(key) != 0 )
        return;

    if ( current_counter_ == NULL )
        current_counter_ = new PortCounter(connection_.GetPort(), key_limit_);
    else
    {
        if ( current_counter_->IsLimit() )
            current_counter_ = new PortCounter(current_counter_->GetPort(), key_limit_);
    }

    current_counter_->Increment();
    ports_.insert(KeyPort::value_type(key, current_counter_));
}

port_t KeyList::GetPort(string& key)
{
    if ( ports_.count(key) != 0 )
        return ports_[key]->GetPort();
    else
        return kErrorPort;
}

struct AddKeyArray : public binary_function<KeyList::KeyPort::value_type, KeyArray&, void>
{
    void operator()(KeyList::KeyPort::value_type port_pair, KeyArray& keys) const
    {
        copy(port_pair.first.begin(), port_pair.first.end(),
             back_inserter(keys));

        keys.push_back('\0');
    }
};

KeyArray KeyList::GetKeys()
{
    KeyArray keys;

    for_each(ports_.begin(), ports_.end(),
             bind2nd(AddKeyArray(), keys));

    return keys;
}

void KeyList::SetKeyLimit(int key_limit)
{
    key_limit_ = key_limit;
}
