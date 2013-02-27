#ifndef CLIENT_TYPED_H
#define CLIENT_TYPED_H

#include <string>

#include "types_zcache.h"
#include "connection.h"

namespace zero_cache
{

class ClientTyped
{
public:
    ClientTyped(const char* log_file, Connection connection, const SocketType type);

    void WriteLong(const std::string key, const long value);
    void WriteDouble(const std::string key, const double value);
    void WriteString(const std::string key, const std::string value);

    long ReadLong(const std::string key) const;
    double ReadDouble(const std::string key) const;
    std::string ReadString(const std::string key) const;

    std::string GetKeys();
};

}

#endif
