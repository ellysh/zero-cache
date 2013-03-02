#ifndef CLIENT_H
#define CLIENT_H

#include <string>

#include "debug.h"
#include "zero_cache.h"

namespace zero_cache
{

class Client : protected Debug
{
public:
    Client(const char* log_file);
    virtual ~Client();

    void WriteLong(const size_t index, const long value);
    void WriteDouble(const size_t index, const double value);

    long ReadLong(const size_t index) const;
    double ReadDouble(const size_t index) const;

private:
    int dev_file_;
};

}

#endif
