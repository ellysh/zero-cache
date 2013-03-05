#ifndef TYPED_CLIENT_H
#define TYPED_CLIENT_H

#include "untyped_client.h"

namespace zero_cache
{

class TypedClient
{
public:
    TypedClient(const char* log_file = "");

    void WriteLong(const size_t index, const long value);
    void WriteDouble(const size_t index, const double value);

    long ReadLong(const size_t index) const;
    double ReadDouble(const size_t index) const;

private:
    UntypedClient client_;
};

}

#endif
