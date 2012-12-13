#ifndef REGISTRAR_CLIENT_H
#define REGISTRAR_CLIENT_H

#include <string>
#include <map>

#include "debug.h"
#include "types_zcache.h"
#include "socket.h"

namespace zero_cache
{

class Client;

class RegistrarClient : protected Debug
{
public:
    typedef std::map<std::string, std::string> KeyConnection;
    typedef std::map<std::string, Client*> ConnectionClient;

public:
    RegistrarClient(std::string log_file, std::string connection, SocketType type);
    virtual ~RegistrarClient();

    void WriteData(std::string key, void* data, size_t size);
    void* ReadData(std::string key);

    void SetQueueSize(int size);

private:
    int queue_size_;
    Socket socket_;
    KeyConnection connections_;
    ConnectionClient clients_;

    void AddKey(std::string key);
    Client* GetClient(std::string key);
    std::string ReceiveAnswer(zframe_t* key);
};

}

#endif
