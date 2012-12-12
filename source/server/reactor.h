#ifndef REACTOR_H
#define REACTOR_H

#include <string>

#include "debug.h"
#include "container.h"
#include "socket.h"

namespace zero_cache
{

class Reactor : protected Debug
{
public:
    Reactor(std::string log_file, std::string connection);
    virtual ~Reactor() {};

    void Start();

    void SetQueueSize(int size);

private:
    Socket socket_;
    Container container_;

    void ProcessMessage();
    void WriteData(std::string& key);
    void ReadData(std::string& key);
};

}

#endif
