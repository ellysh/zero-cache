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
    request_.Receive(socket_);

    if ( request_.GetCommand() == kGetPort )
    {
        StartReactor();
        SendPort();
    }

    if ( request_.GetCommand() == kGetKeys )
        SendKeys();
}

void Registrar::StartReactor()
{
    string key = request_.GetKey();

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

void Registrar::SendPort()
{
    string key = request_.GetKey();

    Connection connection(connection_);
    connection.SetPort(request_.GetId());
    connection.SetHost(request_.GetHost());
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

    Connection connection(connection_);
    connection.SetPort(request_.GetId());
    connection.SetHost(request_.GetHost());
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
