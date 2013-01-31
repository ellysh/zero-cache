#include "client.h"

#include "connection.h"
#include "request.h"

using namespace std;
using namespace zero_cache;

Client::Client(const char* log_file, Connection connection, SocketType type) : ClientBase(log_file, connection, type)
{
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

void Client::SetQueueSize(int size)
{
    socket_.SetQueueSize(size);
}
