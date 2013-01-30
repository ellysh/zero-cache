#include "client.h"

#include <string.h>
#include <stdlib.h>

#include "connection.h"
#include "functions.h"

using namespace std;
using namespace zero_cache;

static const long kReadAnswerTimeout = 1000;

Client::Client(const char* log_file, Connection connection, SocketType type) : ClientBase(log_file, connection, type)
{
    srand(time(NULL));

    SetHost(connection.GetHost());

    zmq_msg_init(&data_msg_);
}

Client::~Client()
{
    zmq_msg_close(&data_msg_);
}

void Client::WriteData(string& key, void* data, size_t size)
{
    Log("Client::WriteData() - key = %s data_size = %lu\n", key.c_str(), size);

    Command command = kWrite;

    MsgInitData(command_msg_, &command, sizeof(command));
    MsgInitString(key_msg_, key);
    MsgInitData(data_msg_, data, size);

    socket_.SendMsg(command_msg_, ZMQ_SNDMORE);
    socket_.SendMsg(key_msg_, ZMQ_SNDMORE);
    socket_.SendMsg(id_msg_, ZMQ_SNDMORE);
    socket_.SendMsg(host_msg_, ZMQ_SNDMORE);
    socket_.SendMsg(data_msg_, 0);

    zmq_msg_close(&data_msg_);
}

void* Client::ReadData(string& key)
{
    Log("Client::ReadData() - key = %s\n", key.c_str());

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

    MsgInitData(command_msg_, &command, sizeof(Command));
    MsgInitString(key_msg_, key);

    socket_.SendMsg(command_msg_, ZMQ_SNDMORE);
    socket_.SendMsg(key_msg_, ZMQ_SNDMORE);
    socket_.SendMsg(id_msg_, ZMQ_SNDMORE);
    socket_.SendMsg(host_msg_, 0);
}

void* Client::ReceiveReadAnswer()
{
    if ( ! socket_.ReceiveMsg(kReadAnswerTimeout) )
        return NULL;

    zmq_msg_t msg;
    socket_.PopMsg(msg);
    void* data = malloc(zmq_msg_size(&msg));
    memcpy(data, zmq_msg_data(&msg), zmq_msg_size(&msg));
    zmq_msg_close(&msg);

    return data;
}

void Client::SetQueueSize(int size)
{
    socket_.SetQueueSize(size);
}
