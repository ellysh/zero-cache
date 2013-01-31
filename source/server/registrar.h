#ifndef REGISTRAR_H
#define REGISTRAR_H

#include <set>

#include "types_zcache.h"
#include "socket.h"
#include "connection.h"
#include "server_base.h"

namespace zero_cache
{

class KeyList;

class Registrar : public ServerBase
{
private:
    typedef std::set<port_t> PortSet;

public:
    Registrar(const char* log_file, Connection connection, SocketType type = kDealer);
    virtual ~Registrar();

    virtual void SetQueueSize(int size);

    void SetKeyLimit(int limit);

protected:
    virtual void ProcessMessage();

private:
    Connection connection_;
    KeyList* key_list_;
    PortSet ports_;

    void StartReactor();
    void SendAnswer();
    void SetPortAnswer();
    void SetKeysAnswer();
};

}

#endif
