#include "connection.h"

#include <stdlib.h>
#include <stdio.h>

using namespace std;
using namespace zero_cache;

Connection::Connection(string connection, int limit) : limit_(limit), counter_(1)
{
    size_t pos = connection.find_last_of('/') + 1;
    string port = connection.substr(pos, connection.size());

    int num_port = atoi(port.c_str());
    num_port++;

    char new_port[100];
    sprintf(new_port, "%d", num_port);

    connection_ = connection.substr(0, pos);
    connection_ += new_port;
}

void Connection::IncrementCounter()
{
    counter_++;
}

bool Connection::IsCounterLimit()
{
    if ( counter_ >= limit_ )
        return true;
    else
        return false;
}

string Connection::GetConnection()
{
    return connection_;
}
