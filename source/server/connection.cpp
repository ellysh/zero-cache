#include "connection.h"

#include "functions.h"

using namespace std;
using namespace zero_cache;

Connection::Connection(string connection, int limit) : limit_(limit), counter_(1)
{
    connection_ = IncrementPort(connection, 1);
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

string Connection::GetString()
{
    return connection_;
}
