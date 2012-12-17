#ifndef CONNECTION_COUNTER_H
#define CONNECTION_COUNTER_H

#include <string>

namespace zero_cache
{

class ConnectionCounter
{
public:
    ConnectionCounter(std::string prev_connection, int limit);

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
