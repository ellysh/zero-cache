#ifndef REACTOR_H
#define REACTOR_H

#include <string>

#include "debug.h"
#include "container.h"
#include "socket.h"
#include "types_zcache.h"
#include "connection.h"

namespace zero_cache
{

class Connection;

class Reactor : protected Debug
{
private:
    typedef std::map<port_t, Socket*> PortSocket;

public:
    Reactor(const char* log_file, Connection connection, SocketType type = kDealer);
    virtual ~Reactor();

    void Start();

    void SetQueueSize(int size);

private:
    Socket socket_;
    Connection connection_;
    Container container_;
    PortSocket out_sockets_;

    void ProcessMessage();
    void WriteData(std::string& key);
    void ReadData(std::string& key, port_t id);
    void AddOutSocket(port_t id);
};

}

#endif
