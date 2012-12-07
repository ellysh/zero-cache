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
    zsocket_set_hwm(socket_, 1);
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
    AddKey(key);

    return clients_[key];
}

void RegistrarClient::AddKey(string key)
{
    if ( clients_.count(key) != 0 )
        return;

    /* FIXME: Check counters of existing clients to limit before add new client.
     * Attach new key to one of them if possible */

    zframe_t* key_frame = zframe_new(key.c_str(), key.size());

    zframe_send(&key_frame, socket_, ZFRAME_REUSE);

    string connection = ReceiveAnswer(key_frame);

    Log() << "RegistrarClient::AddKey() - connection = " << connection << endl;

    Client* client = new Client("", connection);
    clients_.insert(KeyClient::value_type(key, client));

    zframe_destroy(&key_frame);
}

string RegistrarClient::ReceiveAnswer(zframe_t* key)
{
    zmq_pollitem_t items[] = { { socket_, 0, ZMQ_POLLIN, 0 } };

    if ( zmq_poll(items, 1, kReadAnswerTimeout) <= 0 )
        Log() << "RegistrarClient::AddKey() - error = " << zmq_strerror(zmq_errno()) << " (" << zmq_errno << ")" << endl;

    zmsg_t* msg = zmsg_recv(socket_);
    zframe_t* key_frame = zmsg_pop(msg);

    Log() << "RegistrarClient::ReceiveAnswer() - send_key = " << zframe_strdup(key) << " recv_key = " << zframe_strdup(key_frame) << endl;

    /* FIXME: Implement request resend if have been received wrong key */
#if 0
    if ( ! zframe_eq(key_frame, key) )
        return "";
#endif

    zframe_t* connection_frame = zmsg_pop(msg);
    char* buffer =  zframe_strdup(connection_frame);
    string connection = buffer;
    free(buffer);

    return connection;
}
