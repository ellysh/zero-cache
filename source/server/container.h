#ifndef CONTAINER_H
#define CONTAINER_H

#include <string>
#include <map>

#include "types_zcache.h"

namespace zero_cache
{

class Container
{
public:
    typedef std::map<std::string, void*> DataMap;

public:
    Container() {};
    ~Container();

    void WriteData(const std::string& key, const void* data);
    void* ReadData(const std::string& key) const;

private:
    mutable DataMap map_;

    DISALLOW_COPY_AND_ASSIGN(Container)
};

}

#endif
