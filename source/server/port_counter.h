#ifndef PORT_COUNTER_H
#define PORT_COUNTER_H

#include <string>

namespace zero_cache
{

class PortCounter
{
public:
    PortCounter(std::string prev_connection, int limit);

    void Increment();
    std::string GetString();
    bool IsLimit();

private:
    int limit_;
    int counter_;
    std::string connection_;
};

}

#endif
