#include "client.h"

#include "debug.h"
#include "types.h"

using namespace std;
using namespace zero_cache;

Client::Client(string log_file) : DebugClient(log_file)
{
    context_ = zctx_new();
    socket_ = zsocket_new(context_, ZMQ_DEALER);

    zsocket_connect(socket_, "tcp://localhost:5570");
    zsocket_set_hwm(socket_, 10);
}

Client::~Client()
{
    zctx_destroy(&context_);
}

void Client::WriteData(string key, void* data, size_t size)
{
    debug_->Log() << "Client::WriteData() - key = " << key << " data_size = " << size << endl;

    Command command = kSet;

    zframe_t* command_frame = zframe_new(&command, sizeof(Command));
    zframe_t* key_frame = zframe_new(key.c_str(), key.size());
    zframe_t* data_frame = zframe_new(data, size);

    zframe_send(&command_frame, socket_, ZFRAME_MORE);
    zframe_send(&key_frame, socket_, ZFRAME_MORE);
    zframe_send(&data_frame, socket_, 0);
}

void* Client::ReadData(string key)
{
    /* FIXME: Implement this method */
    return NULL;
}
