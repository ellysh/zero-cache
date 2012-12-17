#ifndef REGISTRAR_H
#define REGISTRAR_H

#include <set>

#include "types_zcache.h"
#include "socket.h"
#include "debug.h"
#include "connection.h"

namespace zero_cache
{

class KeyList;

class Registrar : protected Debug
{
private:
    typedef std::set<std::string> ConnectionSet;

public:
    Registrar(std::string log_file, Connection connection, SocketType type = kDealer);
    virtual ~Registrar();

    void Start();

    void SetKeyLimit(int limit);
    void SetQueueSize(int size);

private:
    int queue_size_;
    Socket socket_;
    KeyList* key_list_;
    ConnectionSet connections_;

    void ProcessMessage();

    DISALLOW_COPY_AND_ASSIGN(Registrar)
};

}

#endif
