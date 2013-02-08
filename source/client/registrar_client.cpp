#include "registrar_client.h"

#include "client.h"
#include "request.h"
#include "functions.h"

#define PRINTF Log
#include "speed_test.h"

using namespace std;
using namespace zero_cache;

RegistrarClient::RegistrarClient(const char* log_file, Connection connection, const SocketType type) :
    ClientBase(log_file, connection, type), clients_(connection, type)
{
    SetHost(connection.GetHost());
}

string RegistrarClient::GetKeys()
{
    request_->SetCommand(kGetKeys);

    SendRequest();

    return answer_.GetKeys();
}

void RegistrarClient::WriteData(const string key, const Package package)
{
    Log("RegistrarClient::WriteData() - key = %s data_size = %lu\n", key.c_str(), package.GetSize());

    PRE_TIME_MEASURE("RegistrarClient::WriteData() ")

    GetClient(key)->WriteData(key, package);

    POST_TIME_MEASURE
}

Package RegistrarClient::ReadData(string key)
{
    Log("RegistrarClient::ReadData() - key = %s\n", key.c_str());

    PRE_TIME_MEASURE("RegistrarClient::ReadData() ")

    Package result = GetClient(key)->ReadData(key);

    POST_TIME_MEASURE

    return result;
}

Client* RegistrarClient::GetClient(const string& key)
{
    AddKey(key);

    return clients_.GetClient(key);
}

void RegistrarClient::AddKey(const string& key)
{
    if ( clients_.IsKeyExist(key) )
        return;

    port_t port = SendPortRequest(key);

    Log("RegistrarClient::AddKey() - add key = %s port = %lu\n", key.c_str(), port);

    clients_.AddKey(key, port);

    clients_.CreateClient(port);
}

port_t RegistrarClient::SendPortRequest(const string& key)
{
    request_->SetCommand(kGetPort);
    request_->SetKey(key);

    SendRequest();

    return answer_.GetPort();
}

void RegistrarClient::SetHost(string host)
{
    ClientBase::SetHost(host);

    clients_.SetHost(host);
}

void RegistrarClient::SetQueueSize(int size)
{
    clients_.SetQueueSize(size);
}
