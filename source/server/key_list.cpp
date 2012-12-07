#include "key_list.h"

#include <stdlib.h>
#include <stdio.h>

using namespace std;
using namespace zero_cache;

static const int kKeyLimit = 10;

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

    if ( current_connection_ == NULL )
        current_connection_ = new Connection(connection_str_, kKeyLimit);
    else
    {
        if ( current_connection_->IsCounterLimit() )
            current_connection_ = new Connection(current_connection_->GetString(), kKeyLimit);
    }

    connections_.insert(KeyConnection::value_type(key, current_connection_));
}

string KeyList::GetConnection(string key)
{
    if ( connections_.count(key) != 0 )
        return connections_[key]->GetString();
    else
        return "";
}
