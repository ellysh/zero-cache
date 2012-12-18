#ifndef CONTAINER_H
#define CONTAINER_H

#include <string>
#include <map>
#include <czmq.h>

#include "types_zcache.h"

namespace zero_cache
{

class Container
{
public:
    typedef std::map<std::string, zframe_t*> DataMap;

public:
    Container() {};
    ~Container();

    void WriteData(std::string& key, zframe_t* data);
    zframe_t* ReadData(std::string& key);

private:
    DataMap map_;

    DISALLOW_COPY_AND_ASSIGN(Container)
};

}

#endif
