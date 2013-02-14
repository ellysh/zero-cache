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

    void SetPort(const port_t port);
    void SetKeys(const std::string& keys);
    void SetData(zmq_msg_t* const data);

    port_t GetPort() const;
    std::string GetKeys() const;
    void* GetData() const;
    zmq_msg_t* GetMsg() const;
    size_t GetSize() const;

    void Send(Socket& socket) const;
    bool Receive(Socket& socket, long timeout = -1);

private:
    mutable zmq_msg_t msg_;

    DISALLOW_COPY_AND_ASSIGN(Answer);
};

}

#endif
