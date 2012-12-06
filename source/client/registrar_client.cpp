#include "registrar_client.h"

#include "client.h"

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

    GetClient(key)->WriteData(key, data, size);
}

void* RegistrarClient::ReadData(string key)
{
    Log() << "RegistrarClient::ReadData() - key = " << key << endl;

    return GetClient(key)->ReadData(key);
}

Client* RegistrarClient::GetClient(string key)
{
    /* FIXME: Implement this method */

    return NULL;
}
