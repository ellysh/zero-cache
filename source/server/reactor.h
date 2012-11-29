#ifndef REACTOR_H
#define REACTOR_H

#include "debug_client.h"

namespace zero_cache
{

class Reactor : public DebugClient
{
public:
    Reactor(std::string log_file = "") : DebugClient(log_file), is_start_(false) {};
    virtual ~Reactor() {};

    void Start();

protected:
    bool is_start_;
};

}

#endif
