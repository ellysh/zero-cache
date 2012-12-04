#ifndef REACTOR_H
#define REACTOR_H

#include "debug.h"
#include "container.h"

namespace zero_cache
{

class Reactor : protected Debug
{
public:
    Reactor(std::string log_file, std::string connection);
    virtual ~Reactor();

    void Start();

    void SetQueueSize(int size);

protected:
    Container container_;
    void* socket_;
    zmq_pollitem_t items_[1];
    zctx_t* context_;

    void ProcessMessage();
    void WriteData(char* key_str, zmsg_t* msg);
    void ReadData(char* key_str);
};

}

#endif
