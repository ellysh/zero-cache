#ifndef REGISTRAR_H
#define REGISTRAR_H

#include <set>

#include "types_zcache.h"
#include "socket.h"
#include "debug.h"
#include "request.h"
#include "connection.h"

namespace zero_cache
{

class KeyList;

class Registrar : protected Debug
{
private:
    typedef std::set<port_t> PortSet;

public:
    Registrar(const char* log_file, Connection connection, SocketType type = kDealer);
    virtual ~Registrar();

    void Start();

    void SetKeyLimit(int limit);
    void SetQueueSize(int size);

private:
    Socket socket_;
    Connection connection_;
    KeyList* key_list_;
    PortSet ports_;
    Request request_;

    void ProcessMessage();
    void StartReactor();
    void SendPort();
    void SendKeys();

    DISALLOW_COPY_AND_ASSIGN(Registrar)
};

}

#endif
