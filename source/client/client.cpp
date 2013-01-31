#include "client.h"

#include "connection.h"
#include "request.h"

using namespace std;
using namespace zero_cache;

Client::Client(const char* log_file, Connection connection, const SocketType type) :
    ClientBase(log_file, connection, type)
{
    SetHost(connection.GetHost());
}

void Client::WriteData(const string& key, const void* data, const size_t size) const
{
    Log("Client::WriteData() - key = %s data_size = %lu\n", key.c_str(), size);

    request_->SetCommand(kWrite);
    request_->SetKey(key);
    request_->SetData(data, size);

    request_->Send(socket_);
}

void* Client::ReadData(const string& key)
{
    Log("Client::ReadData() - key = %s\n", key.c_str());

    request_->SetCommand(kRead);
    request_->SetKey(key);

    SendRequest();

    return answer_.GetData();
}

void Client::SetQueueSize(const int size)
{
    socket_.SetQueueSize(size);
}
