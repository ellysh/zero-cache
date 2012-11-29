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

    void WriteData(std::string data);

    //void WriteData(std::string key, int data);
    //int ReadData(std::string key);

protected:
    zctx_t* context_;
    void* socket_;
};

}

#endif
