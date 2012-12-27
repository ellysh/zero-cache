#include "registrar_client.h"

#include "client.h"
#include "functions.h"

#define STREAM Log()
#include "speed_test.h"

using namespace std;
using namespace zero_cache;

static const long kReadAnswerTimeout = 10;

RegistrarClient::RegistrarClient(const char* log_file, Connection connection, SocketType type) :
    Debug(log_file), socket_(type), clients_(connection, type)
{
    srand(time(NULL));

    Log() << "RegistrarClient::RegistrarClient() - connect to " << connection.GetString() << endl;
    socket_.ConnectOut(connection);

    id_ = GenerateId(this);
    connection.SetPort(id_);

    SetHost(connection.GetHost());

    if ( connection.GetProtocol() == kTcpProtocol )
        connection.SetHost("*:");

    Log() << "RegistrarClient::RegistrarClient() - bind to " << connection.GetString() << endl;
    socket_.BindIn(connection);
    socket_.SetQueueSize(1);
}

void RegistrarClient::WriteData(string key, void* data, size_t size)
{
    Log() << "RegistrarClient::WriteData() - key = " << key << " data_size = " << size << endl;

    PRE_TIME_MEASURE("RegistrarClient::WriteData() ")

    GetClient(key)->WriteData(key, data, size);

    POST_TIME_MEASURE
}

void* RegistrarClient::ReadData(string key)
{
    Log() << "RegistrarClient::ReadData() - key = " << key << endl;

    PRE_TIME_MEASURE("RegistrarClient::ReadData() ")

    void* result = GetClient(key)->ReadData(key);

    POST_TIME_MEASURE

    return result;
}

Client* RegistrarClient::GetClient(string& key)
{
    AddKey(key);

    return clients_.GetClient(key);
}

void RegistrarClient::AddKey(string& key)
{
    if ( clients_.IsKeyExist(key) )
        return;

    int port = ReceivePort(key);

    Log() << "RegistrarClient::AddKey() - add key = " << key << " port = " << port << endl;

    clients_.AddKey(key, port);

    clients_.CreateClient(port);
}

port_t RegistrarClient::ReceivePort(string& key)
{
    port_t port = kErrorPort;
    zframe_t* key_frame = zframe_new(key.c_str(), key.size());
    zframe_t* id_frame = zframe_new(&id_, sizeof(id_));
    zframe_t* host_frame = zframe_new(host_.c_str(), host_.size());

    while ( port == kErrorPort )
    {
        socket_.SendFrame(key_frame, ZFRAME_REUSE + ZFRAME_MORE);
        socket_.SendFrame(id_frame, ZFRAME_REUSE + ZFRAME_MORE);
        socket_.SendFrame(host_frame, ZFRAME_REUSE);
        port = ReceiveAnswer(key_frame);

        if ( port == kErrorPort )
            usleep((rand() % 1000) * 100);
    }

    zframe_destroy(&host_frame);
    zframe_destroy(&id_frame);
    zframe_destroy(&key_frame);

    return port;
}

port_t RegistrarClient::ReceiveAnswer(zframe_t* key)
{
    if ( ! socket_.ReceiveMsg(kReadAnswerTimeout) )
        return kErrorPort;

    zframe_t* key_frame = socket_.PopFrame();

    if ( ! zframe_eq(key_frame, key) )
    {
        zframe_destroy(&key_frame);
        return kErrorPort;
    }

    zframe_t* connection_frame = socket_.PopFrame();
    port_t port = FrameToPort(connection_frame);

    zframe_destroy(&key_frame);
    zframe_destroy(&connection_frame);

    return port;
}

void RegistrarClient::SetHost(string host)
{
    host_ = host;

    clients_.SetHost(host);
}

void RegistrarClient::SetQueueSize(int size)
{
    clients_.SetQueueSize(size);
}
