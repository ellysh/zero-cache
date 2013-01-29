#ifndef REGISTRAR_CLIENT_H
#define REGISTRAR_CLIENT_H

#include <string>
#include <map>

#include "debug.h"
#include "types_zcache.h"
#include "socket.h"
#include "client_list.h"
#include "client_base.h"

namespace zero_cache
{

class Client;

class RegistrarClient : public ClientBase
{
public:
    RegistrarClient(const char* log_file, Connection connection, SocketType type);
    virtual ~RegistrarClient() {};

    virtual void SetQueueSize(int size);
    virtual void SetHost(std::string host);

    void WriteData(std::string key, void* data, size_t size);
    void* ReadData(std::string key);
    KeyArray GetKeys();

private:
    ClientList clients_;

    void AddKey(std::string& key);
    Client* GetClient(std::string& key);
    port_t SendPortRequest(std::string& key);
    port_t ReceivePort(zmq_msg_t& key);
    KeyArray ReceiveKeys();
};

}

#endif
