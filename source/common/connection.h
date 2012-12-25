#ifndef CONNECTION_H
#define CONNECTION_H

#include <string>

#include "types_zcache.h"

namespace zero_cache
{

class Connection
{
public:
    Connection(std::string& connection);
    Connection(const char* connection);

    std::string GetString();
    port_t GetPort();
    void SetPort(port_t port);

private:
    std::string host_;
    port_t port_;

    void Constructor(std::string& connection);
};

}

#endif
