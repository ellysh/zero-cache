#include "registrar.h"

#include "zsignal.h"
#include "reactor.h"
#include "key_list.h"
#include "functions.h"
#include "connection.h"

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
    socket_.ReceiveMsg();

    zframe_t* key_frame = socket_.PopFrame();
    string key = FrameToString(key_frame);

    StartReactor(key);

    SendAnswer(key);
}

void Registrar::StartReactor(string& key)
{
    Log() << "Registrar::StartReactor() - key = " << key << endl;
    key_list_->AddKey(key);

    port_t port = key_list_->GetPort(key);

    if ( ports_.count(port) != 0 )
        return;

    Connection connection(connection_);
    connection.SetPort(port);

    string* connection_str = new string(connection.GetString());
    Log() << "zthread_new() - connection = " << connection.GetString() << endl;

    zthread_new(ReactorStart, (void*)connection_str);
    ports_.insert(port);
}

void Registrar::SendAnswer(string& key)
{
    zframe_t* id_frame = socket_.PopFrame();
    port_t id = FrameToPort(id_frame);

    Connection connection(connection_);
    connection.SetPort(id);
    socket_.ConnectOut(connection);

    port_t port = key_list_->GetPort(key);

    zframe_t* key_frame = zframe_new(key.c_str(), key.size());
    zframe_t* port_frame = zframe_new(&port, sizeof(port));
    socket_.SendFrame(key_frame, ZFRAME_MORE);
    socket_.SendFrame(port_frame, 0);

    Log() << "Registrar::ProcessMessage() - send answer = " << port << " to " << connection.GetString() << endl;
}

void Registrar::SetKeyLimit(int limit)
{
    key_list_->SetKeyLimit(limit);
}

void Registrar::SetQueueSize(int size)
{
    gQueueSize = size;
}
