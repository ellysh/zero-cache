#ifndef CONNECTION_H
#define CONNECTION_H

#include <string>

namespace zero_cache
{

class Connection
{
public:
    Connection(std::string prev_connection, int limit);

    void IncrementCounter();
    std::string GetString();
    bool IsCounterLimit();

private:
    int limit_;
    int counter_;
    std::string connection_;
};

}

#endif
