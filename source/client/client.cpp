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

void Client::WriteData(const string& key, const Package package) const
{
    Log("Client::WriteData() - key = %s data_size = %lu\n", key.c_str(), package.GetSize());

    request_->SetCommand(kWrite);
    request_->SetKey(key);
    request_->SetData(package.GetData(), package.GetSize());

    request_->Send(socket_);
}

Package Client::ReadData(const string& key)
{
    Log("Client::ReadData() - key = %s\n", key.c_str());

    request_->SetCommand(kRead);
    request_->SetKey(key);

    SendRequest();

    Package result(answer_.GetData(), answer_.GetSize());

    return result;
}

void Client::SetQueueSize(const int size)
{
    socket_.SetQueueSize(size);
}
