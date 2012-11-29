#include "client.h"

using namespace std;
using namespace zero_cache;

Client::Client()
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

void Client::WriteData(std::string data)
{
    zstr_send(socket_, data.c_str());
}
