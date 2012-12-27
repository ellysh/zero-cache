#ifndef CLIENT_H
#define CLIENT_H

#include <string>
#include <czmq.h>

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

    void SetHost(std::string host);
    void SetQueueSize(int size);

private:
    Socket socket_;
    zframe_t* host_frame_;
    zframe_t* id_frame_;
    zframe_t* command_frame_;
    zframe_t* key_frame_;
    zframe_t* data_frame_;

    void SendReadRequest(std::string& key);
    void* ReceiveReadAnswer();

    DISALLOW_COPY_AND_ASSIGN(Client);
};

}

#endif
