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

    char empty;
    command_frame_ = zframe_new(&empty, sizeof(empty));
    key_frame_ = zframe_new(&empty, sizeof(empty));
    data_frame_ = zframe_new(&empty, sizeof(empty));
}

Client::~Client()
{
    zframe_destroy(&data_frame_);
    zframe_destroy(&key_frame_);
    zframe_destroy(&command_frame_);

    zsocket_destroy(context_, socket_);
    zctx_destroy(&context_);
}

void Client::WriteData(string key, void* data, size_t size)
{
    Log() << "Client::WriteData() - key = " << key << " data_size = " << size << endl;

    Command command = kWrite;

    zframe_reset(command_frame_, &command, sizeof(Command));
    zframe_reset(key_frame_, key.c_str(), key.size());
    zframe_reset(data_frame_, data, size);

    zframe_send(&command_frame_, socket_, ZFRAME_MORE + ZFRAME_REUSE);
    zframe_send(&key_frame_, socket_, ZFRAME_MORE + ZFRAME_REUSE);
    zframe_send(&data_frame_, socket_, ZFRAME_REUSE);
}

void Client::SendReadRequest(string key)
{
    Command command = kRead;

    zframe_reset(command_frame_, &command, sizeof(Command));
    zframe_reset(key_frame_, key.c_str(), key.size());

    zframe_send(&command_frame_, socket_, ZFRAME_MORE + ZFRAME_REUSE);
    zframe_send(&key_frame_, socket_, ZFRAME_REUSE);
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
