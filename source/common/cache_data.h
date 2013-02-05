#ifndef CACHE_DATA_H
#define CACHE_DATA_H

#include "types_zcache.h"

namespace zero_cache
{

struct CacheData
{
    CacheData(const void* data_, const size_t size_) : data(data_), size(size_) {};

    const void* data;
    const size_t size;
};

}

#endif
