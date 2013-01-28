#include "registrar_client.h"

#include <string.h>
#include <stdlib.h>

#include "client.h"
#include "functions.h"

#define PRINTF Log
#include "speed_test.h"

using namespace std;
using namespace zero_cache;

static const long kReadAnswerTimeout = 10;

RegistrarClient::RegistrarClient(const char* log_file, Connection connection, SocketType type) :
    Debug(log_file), socket_(type), clients_(connection, type)
{
    srand(time(NULL));

    Log("RegistrarClient::RegistrarClient() - connect to %s\n", connection.GetString().c_str());
    socket_.ConnectOut(connection);

    id_ = GenerateId(this);
    connection.SetPort(id_);

    SetHost(connection.GetHost());

    if ( connection.GetProtocol() == kTcpProtocol )
        connection.SetHost("*:");

    Log("RegistrarClient::RegistrarClient() - bind to %s\n", connection.GetString().c_str());
    socket_.BindIn(connection);
    socket_.SetQueueSize(1);
}

KeyArray RegistrarClient::GetKeys()
{
    KeyArray keys;
    Command command = kGetKeys;

    zmq_msg_t command_msg;
    zmq_msg_init_data(&command_msg, &command, sizeof(command), NULL, NULL);

    zmq_msg_t id_msg;
    zmq_msg_init_data(&id_msg, &id_, sizeof(id_), NULL, NULL);

    zmq_msg_t host_msg;
    zmq_msg_init_data(&host_msg, (void*)host_.c_str(), host_.size(), NULL, NULL);

    socket_.SendMsg(command_msg, ZMQ_SNDMORE);
    socket_.SendMsg(id_msg, ZMQ_SNDMORE);
    socket_.SendMsg(host_msg, 0);

    keys = ReceiveKeys();

    return keys;
}

KeyArray RegistrarClient::ReceiveKeys()
{
    if ( ! socket_.ReceiveMsg(kReadAnswerTimeout) )
        return KeyArray();

    zmq_msg_t keys_msg;
    socket_.PopMsg(keys_msg);

    KeyArray keys;
    keys.swap(*((KeyArray*)zmq_msg_data(&keys_msg)));

    zmq_msg_close(&keys_msg);

    return keys;
}

void RegistrarClient::WriteData(string key, void* data, size_t size)
{
    Log("RegistrarClient::WriteData() - key = %s data_size = %lu\n", key.c_str(), size);

    PRE_TIME_MEASURE("RegistrarClient::WriteData() ")

    GetClient(key)->WriteData(key, data, size);

    POST_TIME_MEASURE
}

void* RegistrarClient::ReadData(string key)
{
    Log("RegistrarClient::ReadData() - key = %s\n", key.c_str());

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

    port_t port = SendPortRequest(key);

    Log("RegistrarClient::AddKey() - add key = %s port = %lu\n", key.c_str(), port);

    clients_.AddKey(key, port);

    clients_.CreateClient(port);
}

port_t RegistrarClient::SendPortRequest(string& key)
{
    Command command = kGetPort;
    zmq_msg_t command_msg;
    zmq_msg_init_data(&command_msg, &command, sizeof(command), NULL, NULL);

    zmq_msg_t key_msg;
    zmq_msg_init_data(&key_msg, (void*)key.c_str(), key.size(), NULL, NULL);

    zmq_msg_t id_msg;
    zmq_msg_init_data(&id_msg, &id_, sizeof(id_), NULL, NULL);

    zmq_msg_t host_msg;
    zmq_msg_init_data(&host_msg, (void*)host_.c_str(), host_.size(), NULL, NULL);

    port_t port = kErrorPort;

    while ( port == kErrorPort )
    {
        socket_.SendMsg(command_msg, ZMQ_SNDMORE);
        socket_.SendMsg(key_msg, ZMQ_SNDMORE);
        socket_.SendMsg(id_msg, ZMQ_SNDMORE);
        socket_.SendMsg(host_msg, 0);

        port = ReceivePort(key_msg);

        if ( port == kErrorPort )
            usleep((rand() % 1000) * 100);
    }

    zmq_msg_close(&host_msg);
    zmq_msg_close(&id_msg);
    zmq_msg_close(&key_msg);

    return port;
}

port_t RegistrarClient::ReceivePort(zmq_msg_t& key)
{
    if ( ! socket_.ReceiveMsg(kReadAnswerTimeout) )
        return kErrorPort;

    zmq_msg_t key_msg;
    socket_.PopMsg(key_msg);

    if ( ! IsMsgEqual(key_msg, key) )
    {
        zmq_msg_close(&key_msg);
        return kErrorPort;
    }

    zmq_msg_t connection_msg;
    socket_.PopMsg(connection_msg);
    port_t port = MsgToPort(connection_msg);

    zmq_msg_close(&key_msg);
    zmq_msg_close(&connection_msg);

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
