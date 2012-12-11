#include "client.h"

using namespace std;
using namespace zero_cache;

static const long kReadAnswerTimeout = 1000;

Client::Client(string log_file, string connection) : Debug(log_file)
{
    socket_.Connect(connection);
    socket_.SetQueueSize(10);

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
}

void Client::WriteData(string key, void* data, size_t size)
{
    Log() << "Client::WriteData() - key = " << key << " data_size = " << size << endl;

    Command command = kWrite;

    zframe_reset(command_frame_, &command, sizeof(Command));
    zframe_reset(key_frame_, key.c_str(), key.size());
    zframe_reset(data_frame_, data, size);

    socket_.SendFrame(command_frame_, ZFRAME_MORE + ZFRAME_REUSE);
    socket_.SendFrame(key_frame_, ZFRAME_MORE + ZFRAME_REUSE);
    socket_.SendFrame(data_frame_, ZFRAME_REUSE);
}

void* Client::ReadData(string key)
{
    Log() << "Client::ReadData() - key = " << key << endl;

    SendReadRequest(key);

    return ReceiveReadAnswer();
}

void Client::SendReadRequest(string key)
{
    Command command = kRead;

    zframe_reset(command_frame_, &command, sizeof(Command));
    zframe_reset(key_frame_, key.c_str(), key.size());

    socket_.SendFrame(command_frame_, ZFRAME_MORE + ZFRAME_REUSE);
    socket_.SendFrame(key_frame_, ZFRAME_REUSE);
}

void* Client::ReceiveReadAnswer()
{
    if ( ! socket_.ReceiveMsg(kReadAnswerTimeout) )
        return NULL;

    /* FIXME: Check key value of the received message */

    zframe_t* frame = socket_.PopFrame();
    void* data = malloc(zframe_size(frame));
    memcpy(data, zframe_data(frame), zframe_size(frame));

    return data;
}

void Client::SetQueueSize(int size)
{
    socket_.SetQueueSize(size);
}
