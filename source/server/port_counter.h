#ifndef PORT_COUNTER_H
#define PORT_COUNTER_H

#include <string>

namespace zero_cache
{

class PortCounter
{
public:
    PortCounter(int port, int limit);

    void Increment();
    int GetPort();
    bool IsLimit();

private:
    int limit_;
    int counter_;
    int port_;
};

}

#endif
