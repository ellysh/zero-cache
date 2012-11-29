#ifndef CONTAINER_H
#define CONTAINER_H

#include <string>
#include <map>

#include <czmq.h>

namespace zero_cache
{

class Container
{
private:
    typedef std::map<std::string, zframe_t*> DataMap;

public:
    ~Container();

    void WriteData(std::string key, zframe_t* data);
    zframe_t* ReadData(std::string key);

protected:
    DataMap map_;
};

}

#endif
