#include "reactor.h"

#include <assert.h>

#include "interrupt_signal.h"
#include "functions.h"
#include "connection.h"

using namespace std;
using namespace zero_cache;

Reactor::Reactor(const char* log_file, Connection connection, SocketType type) :
    Debug(log_file), socket_(type), connection_(connection), out_sockets_(type)
{
    socket_.BindIn(connection);
    socket_.SetQueueSize(1000);
}

void Reactor::Start()
{
    while (true)
        ProcessMessage();
}

void Reactor::ProcessMessage()
{
    socket_.ReceiveMsg();

    zmq_msg_t command;
    socket_.PopMsg(command);
    zmq_msg_t key;
    socket_.PopMsg(key);

    string key_str = MsgToString(key);

    zmq_msg_t id_msg;
    if ( ! socket_.PopMsg(id_msg) )
        return;
    port_t id = MsgToPort(id_msg);

    zmq_msg_t host_msg;
    if ( ! socket_.PopMsg(host_msg) )
        return;
    string host = MsgToString(host_msg);

    connection_.SetHost(host);
    out_sockets_.CreateSocket(connection_, id);

    if ( DecodeCommand(command) == kWrite )
        WriteData(key_str);

    if ( DecodeCommand(command) == kRead )
        ReadData(key_str, id);

    zmq_msg_close(&key);
    zmq_msg_close(&command);
}

void Reactor::WriteData(string& key)
{
    zmq_msg_t data;
    socket_.PopMsg(data);

    Log("write: key = %s", key.c_str());
    PrintMsg(data);

    container_.WriteData(key, data);
    zmq_msg_close(&data);
}

void Reactor::ReadData(string& key, port_t id)
{
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

    out_sockets_.GetSocket(id).SendMsg(*data, 0);

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
