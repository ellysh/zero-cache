#ifndef REACTOR_H
#define REACTOR_H

#include <string>

#include "debug.h"
#include "container.h"
#include "socket.h"
#include "types_zcache.h"
#include "connection.h"
#include "socket_list.h"
#include "request.h"
#include "answer.h"

namespace zero_cache
{

class Connection;

class Reactor : protected Debug
{
public:
    Reactor(const char* log_file, Connection connection, SocketType type = kDealer);
    virtual ~Reactor() {};

    void Start();

    void SetQueueSize(int size);

private:
    Socket socket_;
    Connection connection_;
    SocketList out_sockets_;
    Container container_;
    Request request_;
    Answer answer_;

    void ProcessMessage();
    void WriteData();
    void ReadData();
};

}

#endif
