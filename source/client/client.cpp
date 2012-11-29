#include "client.h"

#include "debug.h"

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

void Client::WriteString(std::string data)
{
    debug_->Log() << "Client::WriteString() - data = " << data << endl;
    zstr_send(socket_, data.c_str());
}

void WriteData(std::string key, void* data, size_t size)
{
    /* FIXME: Implement this method */
#if 0
    zframe_t* frame = zframe_new(data, size);
    zframe_destroy(frame);
#endif
}

void* ReadData(std::string key)
{
    /* FIXME: Implement this method */
    return NULL;
}
