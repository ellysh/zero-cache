#include "reactor.h"

#include <assert.h>

#include "functions.h"
#include "connection.h"
#include "socket_list.h"

using namespace std;
using namespace zero_cache;

Reactor::Reactor(const char* log_file, Connection connection, SocketType type) :
    ServerBase(log_file, connection, type), connection_(connection)
{
}

void Reactor::ProcessMessage()
{
    request_.Receive(socket_);

    connection_.SetHost(request_.GetHost());

    SocketList* out_sockets = SocketList::Instance();
    out_sockets->CreateSocket(connection_, request_.GetId());

    if ( request_.GetCommand() == kWrite )
        WriteData();

    if ( request_.GetCommand() == kRead )
        ReadData();
}

void Reactor::WriteData()
{
    zmq_msg_t& data = request_.GetData();
    string key = request_.GetKey();

    Log("write: key = %s", key.c_str());
    PrintMsg(data);

    container_.WriteData(key, data);
}

void Reactor::ReadData()
{
    string key = request_.GetKey();
    Log("read: key = %s", key.c_str());

    zmq_msg_t* data = container_.ReadData(key);
    bool is_data_empty = false;

    if ( data == NULL )
    {
        is_data_empty = true;
        data = new zmq_msg_t();
        zmq_msg_init(data);
    }

    PrintMsg(*data);

    answer_.SetData(data);
    SocketList* out_sockets = SocketList::Instance();
    Socket& socket = out_sockets->GetSocket(request_.GetId());
    answer_.Send(socket);

    if ( is_data_empty )
    {
        zmq_msg_close(data);
        delete data;
    }
}

void Reactor::SetQueueSize(int size)
{
    socket_.SetQueueSize(size);
}
