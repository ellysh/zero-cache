#include "registrar_client.h"

using namespace std;
using namespace zero_cache;

static const long kReadAnswerTimeout = 1000;

RegistrarClient::RegistrarClient(string log_file, string connection) : Debug(log_file)
{
    context_ = zctx_new();
    socket_ = zsocket_new(context_, ZMQ_DEALER);

    zsocket_connect(socket_, connection.c_str());
    zsocket_set_hwm(socket_, 10);
}

RegistrarClient::~RegistrarClient()
{
    zsocket_destroy(context_, socket_);
    zctx_destroy(&context_);
}

void RegistrarClient::WriteData(string key, void* data, size_t size)
{
    Log() << "RegistrarClient::WriteData() - key = " << key << " data_size = " << size << endl;

    /* FIXME: Implement this method */
}

void* RegistrarClient::ReadData(string key)
{
    Log() << "RegistrarClient::ReadData() - key = " << key << endl;

    /* FIXME: Implement this method */

    return NULL;
}
