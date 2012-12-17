#ifndef CONNECTION_H
#define CONNECTION_H

#include <string>

namespace zero_cache
{

class Connection
{
public:
    explicit Connection(std::string connection);

private:
    std::string host_;
    int port_;
};

}

#endif
