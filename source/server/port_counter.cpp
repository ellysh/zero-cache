#include "port_counter.h"

#include "functions.h"

using namespace std;
using namespace zero_cache;

PortCounter::PortCounter(string connection, int limit) : limit_(limit), counter_(1)
{
    connection_ = IncrementPort(connection, 2);
}

void PortCounter::Increment()
{
    counter_++;
}

bool PortCounter::IsLimit()
{
    if ( counter_ >= limit_ )
        return true;
    else
        return false;
}

string PortCounter::GetString()
{
    return connection_;
}
