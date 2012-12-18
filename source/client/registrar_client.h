#ifndef REGISTRAR_CLIENT_H
#define REGISTRAR_CLIENT_H

#include <string>
#include <map>

#include "debug.h"
#include "types_zcache.h"
#include "socket.h"
#include "connection.h"

namespace zero_cache
{

class Client;

class RegistrarClient : protected Debug
{
public:
    typedef std::map<std::string, std::string> KeyConnection;
    typedef std::map<std::string, Client*> ConnectionClient;

public:
    RegistrarClient(std::string log_file, Connection connection, SocketType type);
    virtual ~RegistrarClient();

    void WriteData(std::string key, void* data, size_t size);
    void* ReadData(std::string key);

    void SetQueueSize(int size);

private:
    Socket socket_;
    int queue_size_;
    Connection connection_;
    KeyConnection connections_;
    ConnectionClient clients_;

    void AddKey(std::string key);
    Client* GetClient(std::string key);
    int ReceivePort(std::string key);
    int ReceiveAnswer(zframe_t* key);
    /* FIXME: Don't pass key parameter to CreateClient method */
    void CreateClient(std::string key, int port);
};

}

#endif
