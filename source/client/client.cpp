#include "client.h"

#include "connection.h"

using namespace std;
using namespace zero_cache;

static const long kReadAnswerTimeout = 1000;

Client::Client(string log_file, Connection connection, SocketType type) : Debug(log_file), socket_(type)
{
    srand(time(NULL));
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

    void* result = NULL;

    while ( result == NULL )
    {
        SendReadRequest(key);
        result = ReceiveReadAnswer();
        usleep(rand() % 1000);
    }

    return result;
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

    zframe_t* key_frame = socket_.PopFrame();

    if ( ! zframe_eq(key_frame, key_frame_) )
    {
        zframe_destroy(&key_frame);
        return NULL;
    }

    zframe_t* frame = socket_.PopFrame();
    void* data = malloc(zframe_size(frame));
    memcpy(data, zframe_data(frame), zframe_size(frame));
    zframe_destroy(&frame);

    return data;
}

void Client::SetQueueSize(int size)
{
    socket_.SetQueueSize(size);
}
