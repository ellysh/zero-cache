#include "package.h"

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
