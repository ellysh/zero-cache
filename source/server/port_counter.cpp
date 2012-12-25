#include "port_counter.h"

#include "functions.h"

using namespace std;
using namespace zero_cache;

PortCounter::PortCounter(int port, int limit) : limit_(limit), counter_(1)
{
    port_ = port + 1;
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

int PortCounter::GetPort()
{
    return port_;
}
