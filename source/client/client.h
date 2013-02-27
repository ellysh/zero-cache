#ifndef CLIENT_H
#define CLIENT_H

#include <string>

#include "debug.h"
#include "types_zcache.h"
#include "package.h"
#include "connection.h"

namespace zero_cache
{

class Client : protected Debug
{
public:
    Client(const char* log_file, Connection connection, const SocketType type);
    virtual ~Client() {};

    void WriteData(const std::string& key, const Package package) const;
    Package ReadData(const std::string& key);
    std::string GetKeys();
};

}

#endif
