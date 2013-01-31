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
    void SetData(zmq_msg_t* data);

    port_t GetPort();
    KeyArray GetKeys();
    void* GetData();
    zmq_msg_t* GetMsg();

    void Send(Socket& socket);
    bool Receive(Socket& socket, long timeout = -1);

private:
    zmq_msg_t msg_;
};

}

#endif
