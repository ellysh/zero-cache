#include "registrar_client.h"

#include <algorithm>

#include "client.h"
#include "functions.h"

#define STREAM Log()
#include "speed_test.h"

using namespace std;
using namespace zero_cache;

static const long kReadAnswerTimeout = 10;
static const long kInitServerDelay = 1000;

static SocketType gSocketType;

RegistrarClient::RegistrarClient(string log_file, Connection connection, SocketType type) :
    Debug(log_file), socket_(type), queue_size_(10)
{
    srand(time(NULL));

    socket_.Connect(connection.GetString());
    socket_.SetQueueSize(1);

    gSocketType = type;
}

static void RemoveClient(RegistrarClient::ConnectionClient::value_type client_pair)
{
    delete client_pair.second;
}

RegistrarClient::~RegistrarClient()
{
    for_each(clients_.begin(), clients_.end(),
             RemoveClient);

    clients_.clear();
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

Client* RegistrarClient::GetClient(string key)
{
    AddKey(key);

    return clients_[connections_[key]];
}

void RegistrarClient::AddKey(string key)
{
    /* FIXME: Split this method to sub-methods */

    if ( connections_.count(key) != 0 )
        return;

    string connection = "";
    zframe_t* key_frame = zframe_new(key.c_str(), key.size());
    while ( connection.empty() )
    {
        socket_.SendFrame(key_frame, ZFRAME_REUSE);
        connection = ReceiveAnswer(key_frame);

        usleep((rand() % 1000) * 1000);
    }

    Log() << "RegistrarClient::AddKey() - add key = " << key << " connection = " << connection << endl;

    connections_.insert(KeyConnection::value_type(key, connection));

    if ( clients_.count(connection) == 0 )
    {
        Client* client = new Client("", Connection(connection), gSocketType);
        client->SetQueueSize(queue_size_);
        clients_.insert(ConnectionClient::value_type(connection, client));

        Log() << "RegistrarClient::AddKey() - add client = " << client << " connection = " << connection << endl;
        usleep(kInitServerDelay);
    }

    zframe_destroy(&key_frame);
}

string RegistrarClient::ReceiveAnswer(zframe_t* key)
{
    if ( ! socket_.ReceiveMsg(kReadAnswerTimeout) )
        return "";

    zframe_t* key_frame = socket_.PopFrame();

    if ( ! zframe_eq(key_frame, key) )
    {
        zframe_destroy(&key_frame);
        return "";
    }

    zframe_t* connection_frame = socket_.PopFrame();
    string connection = FrameToString(connection_frame);

    zframe_destroy(&key_frame);
    zframe_destroy(&connection_frame);

    return connection;
}

void RegistrarClient::SetQueueSize(int size)
{
    queue_size_ = size;
}
