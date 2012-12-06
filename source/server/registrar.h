#ifndef REGISTRAR_H
#define REGISTRAR_H

#include "types_zcache.h"
#include "debug.h"
#include "key_list.h"

namespace zero_cache
{

class Registrar : protected Debug
{
public:
    Registrar(std::string log_file, std::string connection);
    virtual ~Registrar();

    void Start();

private:
    KeyList key_list_;
    void* socket_;
    zmq_pollitem_t items_[1];
    zctx_t* context_;

    void ProcessMessage();

    DISALLOW_COPY_AND_ASSIGN(Registrar)
};

}

#endif
