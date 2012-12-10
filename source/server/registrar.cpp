#include "registrar.h"

#include <czmq.h>

#include "zsignal.h"
#include "reactor.h"
#include "key_list.h"

using namespace std;
using namespace zero_cache;

static int gQueueSize;

Registrar::Registrar(string log_file, string connection) : Debug(log_file), queue_size_(1000)
{
    context_ = zctx_new ();
    socket_ = zsocket_new(context_, ZMQ_DEALER);

    zsocket_bind(socket_, connection.c_str());
    zsocket_set_hwm(socket_, 1);

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
    s_catch_signals();

    while ( ! s_interrupted )
        ProcessMessage();
}

static void* ReactorStart(void* args)
{
    char* connection = static_cast<char*>(args);

    Reactor reactor("", connection);

    reactor.SetQueueSize(gQueueSize);

    reactor.Start();
}

void Registrar::ProcessMessage()
{
    /* FIXME: Split this method to submethods */

    if ( zmq_poll(items_, 1, -1) == -1 )
    {
        Log() << "Registrar::ProcessMessage() - error = " << zmq_strerror(zmq_errno()) << " (" << zmq_errno() << ")" << endl;
        if ( zmq_errno() == ERR_INTERRUPT )
            exit(0);
    }

    if ( ! (items_[0].revents & ZMQ_POLLIN) )
        return;

    zmsg_t* msg = zmsg_recv(socket_);
    assert( msg != NULL );
    zframe_t* key = zmsg_pop(msg);
    char* key_str = zframe_strdup(key);

    Log() << "Registrar::ProcessMessage() - key = " << key_str << endl;
    key_list_->AddKey(key_str);

    string connection = key_list_->GetConnection(key_str);

    if ( connections_.count(connection) == 0 )
    {
        Log() << "zthread_new() - connection = " << connection << endl;
        gQueueSize = queue_size_;
        zthread_new(ReactorStart, const_cast<char*>(connection.c_str()));
        connections_.insert(connection);
    }

    zframe_send(&key, socket_, ZFRAME_REUSE + ZFRAME_MORE);
    zstr_sendf(socket_, connection.c_str());

    Log() << "Registrar::ProcessMessage() - send answer = " << connection << endl;

    free(key_str);
    zframe_destroy(&key);
    zmsg_destroy(&msg);
}

void Registrar::SetKeyLimit(int limit)
{
    key_list_->SetKeyLimit(limit);
}

void Registrar::SetQueueSize(int size)
{
    queue_size_ = size;
}
