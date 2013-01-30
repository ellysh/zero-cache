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
    Request(port_t id, std::string& host);
    ~Request();

    void SetCommand(Command command);
    void SetKey(std::string& key);
    void SetData(void* data, size_t size);

    port_t GetId();
    std::string GetHost();
    Command& GetCommand();
    std::string GetKey();
    zmq_msg_t& GetData();

    void Send(Socket& socket);
    void Receive(Socket& socket);

private:
    zmq_msg_t command_msg_;
    zmq_msg_t id_msg_;
    zmq_msg_t host_msg_;
    zmq_msg_t key_msg_;
    zmq_msg_t data_msg_;

    void Constructor();
};

}

#endif
