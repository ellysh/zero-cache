#ifndef REGISTRAR_CLIENT_H
#define REGISTRAR_CLIENT_H

#include <string>
#include <czmq.h>

#include "debug.h"
#include "types_zcache.h"

namespace zero_cache
{

class RegistrarClient : protected Debug
{
public:
    RegistrarClient(std::string log_file = "", std::string connection = "tcp://localhost:5570");
    virtual ~RegistrarClient();

    void WriteData(std::string key, void* data, size_t size);
    void* ReadData(std::string key);

private:
    zctx_t* context_;
    void* socket_;

    DISALLOW_COPY_AND_ASSIGN(RegistrarClient);
};

}

#endif
