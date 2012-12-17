#include "key_list.h"

#include <algorithm>

#include <stdlib.h>
#include <stdio.h>

using namespace std;
using namespace zero_cache;

static void RemovePort(KeyList::KeyPort::value_type port_pair)
{
    delete port_pair.second;
}

KeyList::~KeyList()
{
    for_each(ports_.begin(), ports_.end(),
             RemovePort);

    ports_.clear();
}

void KeyList::AddKey(string key)
{
    if ( ports_.count(key) != 0 )
        return;

    if ( current_counter_ == NULL )
        current_counter_ = new PortCounter(connection_str_, key_limit_);
    else
    {
        if ( current_counter_->IsLimit() )
            current_counter_ = new PortCounter(current_counter_->GetString(), key_limit_);
    }

    current_counter_->Increment();
    ports_.insert(KeyPort::value_type(key, current_counter_));
}

string KeyList::GetConnection(string key)
{
    if ( ports_.count(key) != 0 )
        return ports_[key]->GetString();
    else
        return "";
}

void KeyList::SetKeyLimit(int key_limit)
{
    key_limit_ = key_limit;
}
