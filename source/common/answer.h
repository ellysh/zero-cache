#ifndef ANSWER_H
#define ANSWER_H

#include <zmq.h>

#include "types_zcache.h"

namespace zero_cache
{

class Socket;

class Answer
{
public:
    Answer();
    ~Answer();

    void SetPort(port_t port);
    void SetKeys(KeyArray& keys);
    void SetData(void* data, size_t size);

    port_t GetPort();
    KeyArray GetKeys();
    zmq_msg_t& GetData();

    void Send(Socket& socket);
    void Receive(Socket& socket);

private:
    zmq_msg_t msg_;
};

}

#endif
