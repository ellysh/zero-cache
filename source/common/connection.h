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
    Connection(std::string& connection);
    Connection(const char* connection);

    void SetHost(std::string host);
    std::string& GetHost();

    void SetPort(port_t port);
    port_t GetPort();

    std::string& GetProtocol();
    std::string GetString() const;

private:
    std::string protocol_;
    std::string host_;
    port_t port_;

    void Constructor(std::string& connection);
};

}

#endif
