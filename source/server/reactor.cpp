#include "reactor.h"

#include <czmq.h>

#include "zsignal.h"

using namespace std;
using namespace zero_cache;

Reactor::Reactor(string log_file, string connection) : Debug(log_file)
{
    context_ = zctx_new ();
    socket_ = zsocket_new(context_, ZMQ_DEALER);

    zsocket_bind(socket_, connection.c_str());
    zsocket_set_hwm(socket_, 1000);

    zmq_pollitem_t items[1] = { { socket_, 0, ZMQ_POLLIN, 0 } };
    memcpy(&items_, &items, sizeof(items));
}

Reactor::~Reactor()
{
    zsocket_destroy(context_, socket_);
    zctx_destroy(&context_);
}

void Reactor::Start()
{
    s_catch_signals ();

    while ( ! s_interrupted )
        ProcessMessage();
}

static Command DecodeCommand(zframe_t* frame)
{
    Command command = kWrite;
    zframe_t* set_frame = zframe_new(&command, sizeof(Command));

    if ( zframe_eq(frame, set_frame) )
        command = kWrite;
    else
        command = kRead;

    zframe_destroy(&set_frame);

    return command;
}

void Reactor::ProcessMessage()
{
    if ( zmq_poll(items_, 1, -1) == -1 )
        Log() << "Reactor::ProcessMessage() - error = " << zmq_strerror(zmq_errno()) << endl;

    if ( ! (items_[0].revents & ZMQ_POLLIN) )
        return;

    zmsg_t* msg = zmsg_recv(socket_);
    assert( msg != NULL );
    zframe_t* command = zmsg_pop(msg);
    zframe_t* key = zmsg_pop(msg);
    char* key_str = zframe_strdup(key);

    if ( DecodeCommand(command) == kWrite )
        WriteData(key_str, msg);

    if ( DecodeCommand(command) == kRead )
        ReadData(key_str);

    free(key_str);
    zframe_destroy(&key);
    zframe_destroy(&command);
    zmsg_destroy(&msg);
}

void Reactor::WriteData(char* key_str, zmsg_t* msg)
{
    zframe_t* data = zmsg_pop(msg);

    Log() << "write: key = " << key_str;
    PrintFrame(data);

    container_.WriteData(string(key_str), data);
    zframe_destroy(&data);
}

void Reactor::ReadData(char* key_str)
{
    Log() << "read: key = " << key_str;

    zframe_t* data = container_.ReadData(string(key_str));
    bool is_data_empty = false;

    if ( data == NULL )
    {
        is_data_empty = true;
        data = zframe_new(NULL, 0);
    }

    PrintFrame(data);

    zframe_send(&data, socket_, ZFRAME_REUSE);

    if ( is_data_empty )
        zframe_destroy(&data);
}

void Reactor::SetQueueSize(int size)
{
    zsocket_set_hwm(socket_, size);
}
