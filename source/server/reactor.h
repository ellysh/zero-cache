#ifndef REACTOR_H
#define REACTOR_H

#include "container.h"
#include "types_zcache.h"
#include "server_base.h"

namespace zero_cache
{

class Connection;

class Reactor : public ServerBase
{
public:
    Reactor(const char* log_file, Connection connection, SocketType type = kDealer);
    virtual ~Reactor() {};

    virtual void SetQueueSize(int size);

protected:
    virtual void PerformCommand();

private:
    Container container_;

    void WriteData();
    void ReadData();
};

}

#endif
