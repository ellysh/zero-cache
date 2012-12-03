#include "reactor.h"

#include <czmq.h>

#include "reactor_loop.h"
#include "debug.h"
#include "types.h"

using namespace std;
using namespace zero_cache;

static const int kThreadCreationDelay = 1000 * 1000;

Reactor::Reactor(string log_file) : DebugClient(log_file), is_start_(false)
{
    context_ = zctx_new ();
    socket_ = zsocket_new(context_, ZMQ_DEALER);

    zsocket_bind(socket_, "tcp://*:5570");
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
    if ( is_start_ )
        return;

    is_start_ = true;

    zthread_new(ReactorLoop, this);

    usleep(kThreadCreationDelay);
}

static Command GetCommand(zframe_t* frame)
{
    Command command = kSet;
    zframe_t* set_frame = zframe_new(&command, sizeof(Command));

    if ( zframe_eq(frame, set_frame) )
        command = kSet;
    else
       command = kGet;

    zframe_destroy(&set_frame);

    return command;
}

void Reactor::ProcessMessage()
{
    /* FIXME: Split this method to submethods */
    if ( zmq_poll(items_, 1, -1) == -1 )
        debug_->Log() << "ReactorLoop() - error = " << zmq_strerror(zmq_errno()) << endl;

    if ( ! (items_[0].revents & ZMQ_POLLIN) )
        return;

    zmsg_t* msg = zmsg_recv(socket_);
    assert( msg != NULL );
    zframe_t* command = zmsg_pop(msg);
    zframe_t* key = zmsg_pop(msg);
    char* key_str = zframe_strdup(key);

    if ( GetCommand(command) == kSet )
    {
        zframe_t* data = zmsg_pop(msg);
#ifdef __DEBUG__
        char* data_hex = zframe_strhex(data);
        debug_->Log() << "set: key = " << key_str << " data = " << data_hex << endl;
        free(data_hex);
#endif
        container_.WriteData(string(key_str), data);
        zframe_destroy(&data);
    }

    if ( GetCommand(command) == kGet )
    {
        debug_->Log() << "get: key = " << key_str;
        zframe_t* data = container_.ReadData(string(key_str));
        bool is_data_empty = false;

        if ( data == NULL )
        {
            is_data_empty = true;
            data = zframe_new(NULL, 0);
        }

#ifdef __DEBUG__
        char* data_hex = zframe_strhex(data);
        debug_->Log() << " data = " << data_hex << endl;
        free(data_hex);
#endif
        zframe_send(&data, socket_, ZFRAME_REUSE);
        if ( is_data_empty )
            zframe_destroy(&data);
    }

    free(key_str);
    zframe_destroy(&key);
    zframe_destroy(&command);
    zmsg_destroy(&msg);
}
