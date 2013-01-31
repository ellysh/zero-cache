#ifndef CONNECTION_H
#define CONNECTION_H

#include <string>

#include "types_zcache.h"

namespace zero_cache
{

class Connection
{
public:
    Connection() {};
    Connection(const std::string& connection);
    Connection(const char* connection);

    void SetHost(const std::string host);
    std::string& GetHost() const;

    void SetPort(const port_t port);
    port_t GetPort() const;

    std::string& GetProtocol() const;
    std::string GetString() const;

private:
    mutable std::string protocol_;
    mutable std::string host_;
    mutable port_t port_;

    void Constructor(const std::string& connection);
};

}

#endif
