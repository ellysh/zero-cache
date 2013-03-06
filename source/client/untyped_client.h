#ifndef UNTYPED_CLIENT_H
#define UNTYPED_CLIENT_H

#include "debug.h"
#include "types_zcache.h"

namespace zero_cache
{

class UntypedClient : protected Debug
{
public:
    UntypedClient(const char* log_file = "");
    virtual ~UntypedClient();

    void WriteValue(const size_t index, const void* value, const size_t size);
    void ReadValue(const size_t index, void* result, const size_t size) const;

    void WriteArray(const size_t index, const void* array, const size_t size);
    void ReadArray(const size_t index, void* result, const size_t size) const;

private:
    int dev_file_;

    DISALLOW_COPY_AND_ASSIGN(UntypedClient)
};

}

#endif
