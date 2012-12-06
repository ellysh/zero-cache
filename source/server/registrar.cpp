#include "registrar.h"

#include <czmq.h>

#include "zsignal.h"

using namespace std;
using namespace zero_cache;

Registrar::Registrar(string log_file, string connection) : Debug(log_file)
{
    context_ = zctx_new ();
    socket_ = zsocket_new(context_, ZMQ_DEALER);

    zsocket_bind(socket_, connection.c_str());
    zsocket_set_hwm(socket_, 1000);

    zmq_pollitem_t items[1] = { { socket_, 0, ZMQ_POLLIN, 0 } };
    memcpy(&items_, &items, sizeof(items));
}

Registrar::~Registrar()
{
    zsocket_destroy(context_, socket_);
    zctx_destroy(&context_);
}

void Registrar::Start()
{
    s_catch_signals ();

    while ( ! s_interrupted )
        ProcessMessage();
}

void Registrar::ProcessMessage()
{
    if ( zmq_poll(items_, 1, -1) == -1 )
        Log() << "Registrar::ProcessMessage() - error = " << zmq_strerror(zmq_errno()) << endl;

    if ( ! (items_[0].revents & ZMQ_POLLIN) )
        return;

    zmsg_t* msg = zmsg_recv(socket_);
    assert( msg != NULL );
    zframe_t* key = zmsg_pop(msg);
    char* key_str = zframe_strdup(key);

    /* FIXME: Add new key and send the client connection string */

    free(key_str);
    zframe_destroy(&key);
    zmsg_destroy(&msg);
}
