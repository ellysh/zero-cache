#ifndef UNTYPED_CLIENT_H
#define UNTYPED_CLIENT_H

#include "debug.h"
#include "zero_cache.h"

namespace zero_cache
{

class UntypedClient : protected Debug
{
public:
    UntypedClient(const char* log_file = "");
    virtual ~UntypedClient();

    void WriteData(const size_t index, const void* value);
    void ReadData(const size_t index, void* result) const;

private:
    int dev_file_;
};

}

#endif
