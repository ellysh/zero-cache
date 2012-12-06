#include "registrar.h"

#include <czmq.h>

#include "zsignal.h"
#include "reactor.h"
#include "key_list.h"

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

    key_list_ = new KeyList(connection);
}

Registrar::~Registrar()
{
    delete key_list_;
    zsocket_destroy(context_, socket_);
    zctx_destroy(&context_);
}

void Registrar::Start()
{
    s_catch_signals ();

    while ( ! s_interrupted )
        ProcessMessage();
}

static void* ReactorStart(void* args)
{
    char* connection = static_cast<char*>(args);

    Reactor reactor("zero_cache.log", connection);

    reactor.Start();
}

void Registrar::ProcessMessage()
{
    /* FIXME: Split this method to submethods */

    if ( zmq_poll(items_, 1, -1) == -1 )
        Log() << "Registrar::ProcessMessage() - error = " << zmq_strerror(zmq_errno()) << endl;

    if ( ! (items_[0].revents & ZMQ_POLLIN) )
        return;

    zmsg_t* msg = zmsg_recv(socket_);
    assert( msg != NULL );
    zframe_t* key = zmsg_pop(msg);
    char* key_str = zframe_strdup(key);

    key_list_->AddKey(key_str);

    zframe_send(&key, socket_, ZFRAME_REUSE + ZFRAME_MORE);

    string connection = key_list_->GetConnection(key_str);
    zthread_new(ReactorStart, const_cast<char*>(connection.c_str()));

    zstr_sendf(socket_, connection.c_str());

    free(key_str);
    zframe_destroy(&key);
    zmsg_destroy(&msg);
}
