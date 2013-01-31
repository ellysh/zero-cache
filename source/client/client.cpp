#include "client.h"

#include <stdlib.h>

#include "connection.h"
#include "request.h"

using namespace std;
using namespace zero_cache;

static const long kReadAnswerTimeout = 1000;

Client::Client(const char* log_file, Connection connection, SocketType type) : ClientBase(log_file, connection, type)
{
    srand(time(NULL));

    SetHost(connection.GetHost());
}

void Client::WriteData(string& key, void* data, size_t size)
{
    Log("Client::WriteData() - key = %s data_size = %lu\n", key.c_str(), size);

    request_->SetCommand(kWrite);
    request_->SetKey(key);
    request_->SetData(data, size);

    request_->Send(socket_);
}

void* Client::ReadData(string& key)
{
    Log("Client::ReadData() - key = %s\n", key.c_str());

    request_->SetCommand(kRead);
    request_->SetKey(key);

    SendRequest(key);

    return answer_.GetData();
}

zmq_msg_t* Client::SendRequest(string& key)
{
    zmq_msg_t* result = NULL;

    do
    {
        request_->Send(socket_);
        result = ReceiveAnswer();

        if (result == NULL )
            usleep(rand() % 1000);
    }
    while ( zmq_msg_size(result) == 0 );

    return result;
}

zmq_msg_t* Client::ReceiveAnswer()
{
    if ( ! answer_.Receive(socket_, kReadAnswerTimeout) )
        return NULL;

    return answer_.GetMsg();
}

void Client::SetQueueSize(int size)
{
    socket_.SetQueueSize(size);
}
