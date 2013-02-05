#include "package.h"

#include <stdlib.h>

using namespace std;
using namespace zero_cache;

void* Package::GetData() const
{
    return const_cast<void*>(data_);
}

size_t Package::GetSize() const
{
    return size_;
}

void Package::FreeData()
{
    free(GetData());
}
