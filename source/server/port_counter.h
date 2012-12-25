#ifndef PORT_COUNTER_H
#define PORT_COUNTER_H

#include <string>

#include "types_zcache.h"

namespace zero_cache
{

class PortCounter
{
public:
    PortCounter(port_t port, int limit);

    void Increment();
    port_t GetPort();
    bool IsLimit();

private:
    int limit_;
    int counter_;
    port_t port_;
};

}

#endif
