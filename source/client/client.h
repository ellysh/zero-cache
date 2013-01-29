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
    virtual ~Client();

    void WriteData(std::string& key, void* data, size_t size);
    void* ReadData(std::string& key);

    void SetQueueSize(int size);

private:
    zmq_msg_t data_msg_;

    void SendReadRequest(std::string& key);
    void* ReceiveReadAnswer();
};

}

#endif
