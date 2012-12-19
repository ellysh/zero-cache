#ifndef CONNECTION_H
#define CONNECTION_H

#include <string>

namespace zero_cache
{

class Connection
{
public:
    Connection(std::string& connection);
    Connection(const char* connection);

    const char* GetString();
    int GetPort();
    void SetPort(int port);

private:
    std::string host_;
    int port_;

    void Constructor(std::string& connection);
};

}

#endif
