#include "client.h"

using namespace std;
using namespace zero_cache;

static const long kReadAnswerTimeout = 1000;

Client::Client(string log_file, string connection) : Debug(log_file)
{
    context_ = zctx_new();
    socket_ = zsocket_new(context_, ZMQ_DEALER);

    zsocket_connect(socket_, connection.c_str());
    zsocket_set_hwm(socket_, 10);
}

Client::~Client()
{
    zsocket_destroy(context_, socket_);
    zctx_destroy(&context_);
}

void Client::WriteData(string key, void* data, size_t size)
{
    Log() << "Client::WriteData() - key = " << key << " data_size = " << size << endl;

    Command command = kWrite;

    zframe_t* command_frame = zframe_new(&command, sizeof(Command));
    zframe_t* key_frame = zframe_new(key.c_str(), key.size());
    zframe_t* data_frame = zframe_new(data, size);

    zframe_send(&command_frame, socket_, ZFRAME_MORE);
    zframe_send(&key_frame, socket_, ZFRAME_MORE);
    zframe_send(&data_frame, socket_, 0);
}

void Client::SendReadRequest(string key)
{
    Command command = kRead;

    zframe_t* command_frame = zframe_new(&command, sizeof(Command));
    zframe_t* key_frame = zframe_new(key.c_str(), key.size());

    zframe_send(&command_frame, socket_, ZFRAME_MORE);
    zframe_send(&key_frame, socket_, 0);
}

void* Client::ReceiveReadAnswer()
{
    zmq_pollitem_t items[] = { { socket_, 0, ZMQ_POLLIN, 0 } };

    if ( zmq_poll(items, 1, kReadAnswerTimeout) <= 0 )
    {
        Log() << "Client::ReceiveReadAnswer() - error = " << zmq_strerror(zmq_errno()) << " (" << zmq_errno << ")" << endl;
        return NULL;
    }

    zmsg_t* msg = zmsg_recv(socket_);

    zframe_t* frame = zmsg_pop(msg);
    void* data = malloc(zframe_size(frame));
    memcpy(data, zframe_data(frame), zframe_size(frame));

    zmsg_destroy(&msg);

    return data;
}

void* Client::ReadData(string key)
{
    Log() << "Client::ReadData() - key = " << key << endl;

    SendReadRequest(key);

    return ReceiveReadAnswer();
}

void Client::SetQueueSize(int size)
{
    zsocket_set_hwm(socket_, size);
}
