#ifndef CLIENT_WRAP_H
#define CLIENT_WRAP_H

#include <string>

#include "types_zcache.h"
#include "client_wrap.h"
#include "connection.h"
#include "registrar_client.h"

namespace zero_cache
{

class ClientWrap
{
public:
    ClientWrap(const char* log_file, Connection connection, const SocketType type);

    void SetQueueSize(const int size);
    void SetHost(const std::string host);

    void WriteLong(const std::string key, const long value);
    void WriteDouble(const std::string key, const double value);
    void WriteString(const std::string key, const std::string value);

    long ReadLong(const std::string key) const;
    double ReadDouble(const std::string key) const;
    std::string ReadString(const std::string key) const;

    KeyArray GetKeys();

private:
    RegistrarClient client_;
};

}

#endif
