#ifndef REACTOR_H
#define REACTOR_H

#include "debug_client.h"
#include "container.h"
#include "reactor_loop.h"

namespace zero_cache
{

class Reactor : public DebugClient
{
public:
    Reactor(std::string log_file = "");
    virtual ~Reactor();

    void Start();
    void ProcessMessage();

protected:
    bool is_start_;
    Container container_;
    void* socket_;
    zmq_pollitem_t items_[1];
    zctx_t* context_;
};

}

#endif
