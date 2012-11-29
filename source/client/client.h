#ifndef CLIENT_H
#define CLIENT_H

#include <string>
#include <map>

#include <czmq.h>

namespace zero_cache
{

class Client
{
public:
    Client();
    ~Client();

    /* FIXME: Remove this debug method */
    void WriteString(std::string data);
    void WriteData(std::string key, void* data, size_t size);
    void* ReadData(std::string key);

protected:
    zctx_t* context_;
    void* socket_;
};

}

#endif
