#ifndef REGISTRAR_CLIENT_H
#define REGISTRAR_CLIENT_H

#include <string>
#include <map>

#include "debug.h"
#include "types_zcache.h"
#include "socket.h"
#include "client_list.h"

namespace zero_cache
{

class Client;

class RegistrarClient : protected Debug
{
public:
    RegistrarClient(const char* log_file, Connection connection, SocketType type);
    virtual ~RegistrarClient() {};

    void WriteData(std::string key, void* data, size_t size);
    void* ReadData(std::string key);

    void SetQueueSize(int size);

private:
    Socket socket_;
    ClientList clients_;
    port_t id_;

    void AddKey(std::string& key);
    Client* GetClient(std::string& key);
    int ReceivePort(std::string& key);
    int ReceiveAnswer(zframe_t* key);
};

}

#endif
