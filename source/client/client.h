#ifndef CLIENT_H
#define CLIENT_H

#include <string>
#include <zmq.h>

#include "debug.h"
#include "types_zcache.h"
#include "socket.h"

namespace zero_cache
{

class Connection;

class Client : protected Debug
{
public:
    Client(const char* log_file, Connection connection, SocketType type);
    virtual ~Client();

    void WriteData(std::string& key, void* data, size_t size);
    void* ReadData(std::string& key);

    void SetHost(std::string& host);
    void SetQueueSize(int size);

private:
    Socket socket_;
    zmq_msg_t host_msg_;
    zmq_msg_t id_msg_;
    zmq_msg_t command_msg_;
    zmq_msg_t key_msg_;
    zmq_msg_t data_msg_;

    void SendReadRequest(std::string& key);
    void* ReceiveReadAnswer();

    DISALLOW_COPY_AND_ASSIGN(Client);
};

}

#endif
