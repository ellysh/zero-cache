#ifndef CLIENT_TYPED_H
#define CLIENT_TYPED_H

#include <string>

namespace zero_cache
{

class ClientTyped
{
public:
    ClientTyped(const char* log_file);

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
