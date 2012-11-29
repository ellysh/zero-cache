#ifndef REACTOR_H
#define REACTOR_H

#include <string>
#include <map>

#include <czmq.h>

namespace zero_cache
{

class Reactor
{
private:
    typedef std::map<std::string, int> Data;

public:
    void Start();

protected:
    Data data_;
    bool is_start_;
};

}

#endif
