#include "connection_counter.h"

#include "functions.h"

using namespace std;
using namespace zero_cache;

ConnectionCounter::ConnectionCounter(string connection, int limit) : limit_(limit), counter_(1)
{
    connection_ = IncrementPort(connection, 2);
}

void ConnectionCounter::Increment()
{
    counter_++;
}

bool ConnectionCounter::IsLimit()
{
    if ( counter_ >= limit_ )
        return true;
    else
        return false;
}

string ConnectionCounter::GetString()
{
    return connection_;
}
