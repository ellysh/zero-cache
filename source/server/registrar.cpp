#include "registrar.h"

#include "interrupt_signal.h"
#include "reactor.h"
#include "key_list.h"
#include "functions.h"
#include "connection.h"
#include "thread.h"

using namespace std;
using namespace zero_cache;

static int gQueueSize = 1000;
static SocketType gSocketType;

Registrar::Registrar(const char* log_file, Connection connection, SocketType type) :
    Debug(log_file), socket_(type), connection_(connection)
{
    socket_.BindIn(connection);
    socket_.SetQueueSize(1);

    key_list_ = new KeyList(connection);

    gSocketType = type;
}

Registrar::~Registrar()
{
    delete key_list_;
}

void Registrar::Start()
{
    s_catch_signals();

    while ( ! s_interrupted )
        ProcessMessage();
}

static void* ReactorStart(void* args)
{
    string* connection = static_cast<string*>(args);

    Reactor reactor("", *connection, gSocketType);

    delete connection;

    reactor.SetQueueSize(gQueueSize);

    reactor.Start();
}

void Registrar::ProcessMessage()
{
    /* FIXME: Refactoring this method */

    socket_.ReceiveMsg();

    zmq_msg_t command;
    socket_.PopMsg(command);

    if ( DecodeCommand(command) == kGetPort )
    {
        zmq_msg_t key_msg;
        socket_.PopMsg(key_msg);
        string key = MsgToString(key_msg);

        StartReactor(key);

        SendPort(key);
    }

    if ( DecodeCommand(command) == kGetKeys )
    {
        SendKeys();
    }
}

void Registrar::StartReactor(string& key)
{
    Log("Registrar::StartReactor() - key = %s\n", key.c_str());
    key_list_->AddKey(key);

    port_t port = key_list_->GetPort(key);

    if ( ports_.count(port) != 0 )
        return;

    Connection connection(connection_);
    connection.SetPort(port);

    string* connection_str = new string(connection.GetString());
    Log("CreateThread() - connection = %s\n", connection.GetString().c_str());

    CreateThread(ReactorStart, (void*)connection_str);
    ports_.insert(port);
}

void Registrar::SendPort(string& key)
{
    zmq_msg_t id_msg;
    socket_.PopMsg(id_msg);
    port_t id = MsgToPort(id_msg);

    zmq_msg_t host_msg;
    socket_.PopMsg(host_msg);
    string host = MsgToString(host_msg);

    Connection connection(connection_);
    connection.SetPort(id);
    connection.SetHost(host);
    socket_.ConnectOut(connection);

    port_t port = key_list_->GetPort(key);

    zmq_msg_t port_msg;
    MsgInitData(port_msg, &port, sizeof(port));

    socket_.SendMsg(port_msg, 0);

    Log("Registrar::SendPort() - send answer = %lu to %s\n", port, connection.GetString().c_str());
}

void Registrar::SendKeys()
{
    /* FIXME: This method looks like SendPort one */

    zmq_msg_t id_msg;
    socket_.PopMsg(id_msg);
    port_t id = MsgToPort(id_msg);

    zmq_msg_t host_msg;
    socket_.PopMsg(host_msg);
    string host = MsgToString(host_msg);

    Connection connection(connection_);
    connection.SetPort(id);
    connection.SetHost(host);
    socket_.ConnectOut(connection);

    KeyArray keys = key_list_->GetKeys();

    zmq_msg_t keys_msg;
    MsgInitData(keys_msg, &keys[0], keys.size());

    socket_.SendMsg(keys_msg, 0);

    Log("Registrar::SendKeys() - send answer to %s\n", connection.GetString().c_str());
}

void Registrar::SetKeyLimit(int limit)
{
    key_list_->SetKeyLimit(limit);
}

void Registrar::SetQueueSize(int size)
{
    gQueueSize = size;
}
