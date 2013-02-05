#ifndef CLIENT_H
#define CLIENT_H

#include <string>

#include "types_zcache.h"
#include "client_base.h"
#include "package.h"

namespace zero_cache
{

class Connection;

class Client : public ClientBase
{
public:
    Client(const char* log_file, Connection connection, const SocketType type);
    virtual ~Client() {};

    virtual void SetQueueSize(const int size);

    void WriteData(const std::string& key, const Package package) const;
    Package ReadData(const std::string& key);
};

}

#endif
