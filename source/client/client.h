#ifndef CLIENT_H
#define CLIENT_H

#include <string>
#include <zmq.h>

#include "debug.h"
#include "types_zcache.h"
#include "client_base.h"

namespace zero_cache
{

class Connection;

class Client : public ClientBase
{
public:
    Client(const char* log_file, Connection connection, SocketType type);
    virtual ~Client() {};

    virtual void SetQueueSize(int size);

    void WriteData(std::string& key, void* data, size_t size);
    void* ReadData(std::string& key);

private:
    zmq_msg_t* SendRequest(std::string& key);
    zmq_msg_t* ReceiveAnswer();
};

}

#endif
