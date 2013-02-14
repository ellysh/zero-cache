#ifndef REQUEST_H
#define REQUEST_H

#include <string>

#include <zmq.h>

#include "types_zcache.h"

namespace zero_cache
{

class Socket;

class Request
{
public:
    Request();
    Request(const port_t id, const std::string& host);
    ~Request();

    void SetCommand(const Command command);
    void SetKey(const std::string& key);
    void SetData(const void* data, const size_t size);

    port_t GetId() const;
    std::string GetHost() const;
    Command& GetCommand() const;
    std::string GetKey() const;
    zmq_msg_t& GetData() const;

    void Send(const Socket& socket) const;
    void Receive(Socket& socket, long timeout = -1);

private:
    zmq_msg_t command_msg_;
    zmq_msg_t id_msg_;
    zmq_msg_t host_msg_;
    zmq_msg_t key_msg_;
    mutable zmq_msg_t data_msg_;

    void Constructor();

    DISALLOW_COPY_AND_ASSIGN(Request);
};

}

#endif
