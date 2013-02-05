#ifndef PACKAGE_H
#define PACKAGE_H

#include <cstring>

namespace zero_cache
{

class Package
{
public:
    Package(const void* data, const size_t size) : data_(data), size_(size) {};

    void* GetData() const;
    size_t GetSize() const;

    void FreeData();

private:
    const void* data_;
    size_t size_;
};

}

#endif
