#include "port_counter.h"

#include "functions.h"

using namespace std;
using namespace zero_cache;

PortCounter::PortCounter(port_t port, int limit) : limit_(limit), counter_(1)
{
    port_ = port + 1;
}

void PortCounter::Increment()
{
    counter_++;
}

bool PortCounter::IsLimit() const
{
    if ( counter_ >= limit_ )
        return true;
    else
        return false;
}

port_t PortCounter::GetPort() const
{
    return port_;
}
