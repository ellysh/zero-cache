#include "client.h"

#include "connection.h"
#include "functions.h"

using namespace std;
using namespace zero_cache;

static const long kReadAnswerTimeout = 1000;

Client::Client(const char* log_file, Connection connection, SocketType type) : Debug(log_file), socket_(type)
{
    srand(time(NULL));

    Log() << "Client::Client() - connect " << connection.GetString() << endl;
    socket_.ConnectOut(connection);

    port_t id = GenerateId(this);
    connection.SetPort(id);

    SetHost(connection.GetHost());

    if ( connection.GetProtocol() == kTcpProtocol )
        connection.SetHost("*:");

    Log() << "Client::Client() - bind " << connection.GetString() << endl;
    socket_.BindIn(connection);
    socket_.SetQueueSize(10);

    char empty;
    id_frame_ = zframe_new(&id, sizeof(id));
    command_frame_ = zframe_new(&empty, sizeof(empty));
    key_frame_ = zframe_new(&empty, sizeof(empty));
    data_frame_ = zframe_new(&empty, sizeof(empty));
}

Client::~Client()
{
    zframe_destroy(&data_frame_);
    zframe_destroy(&key_frame_);
    zframe_destroy(&command_frame_);
    zframe_destroy(&id_frame_);
    zframe_destroy(&host_frame_);
}

void Client::WriteData(string& key, void* data, size_t size)
{
    Log() << "Client::WriteData() - key = " << key << " data_size = " << size << endl;

    Command command = kWrite;

    zframe_reset(command_frame_, &command, sizeof(Command));
    zframe_reset(key_frame_, key.c_str(), key.size());
    zframe_reset(data_frame_, data, size);

    socket_.SendFrame(command_frame_, ZFRAME_REUSE + ZFRAME_MORE);
    socket_.SendFrame(key_frame_, ZFRAME_REUSE + ZFRAME_MORE);
    socket_.SendFrame(id_frame_, ZFRAME_REUSE + ZFRAME_MORE);
    socket_.SendFrame(host_frame_, ZFRAME_REUSE + ZFRAME_MORE);
    socket_.SendFrame(data_frame_, ZFRAME_REUSE);
}

void* Client::ReadData(string& key)
{
    Log() << "Client::ReadData() - key = " << key << endl;

    void* result = NULL;

    while ( result == NULL )
    {
        SendReadRequest(key);
        result = ReceiveReadAnswer();

        if (result == NULL )
            usleep(rand() % 1000);
    }

    return result;
}

void Client::SendReadRequest(string& key)
{
    Command command = kRead;

    zframe_reset(command_frame_, &command, sizeof(Command));
    zframe_reset(key_frame_, key.c_str(), key.size());

    socket_.SendFrame(command_frame_, ZFRAME_REUSE + ZFRAME_MORE);
    socket_.SendFrame(key_frame_, ZFRAME_REUSE + ZFRAME_MORE);
    socket_.SendFrame(id_frame_, ZFRAME_REUSE + ZFRAME_MORE);
    socket_.SendFrame(host_frame_, ZFRAME_REUSE);
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

void Client::SetHost(string host)
{
    host_frame_ = zframe_new(host.c_str(), host.size());
}

void Client::SetQueueSize(int size)
{
    socket_.SetQueueSize(size);
}
