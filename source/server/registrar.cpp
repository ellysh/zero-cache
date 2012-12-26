#include "registrar.h"

#include "zsignal.h"
#include "reactor.h"
#include "key_list.h"
#include "functions.h"
#include "connection.h"

using namespace std;
using namespace zero_cache;

static int gQueueSize;
static SocketType gSocketType;

Registrar::Registrar(const char* log_file, Connection connection, SocketType type) :
    Debug(log_file), socket_(type), queue_size_(1000), connection_(connection)
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
    /* FIXME: Split this method */
    socket_.ReceiveMsg();

    zframe_t* key = socket_.PopFrame();
    string key_str = FrameToString(key);

    Log() << "Registrar::ProcessMessage() - key = " << key_str << endl;
    key_list_->AddKey(key_str);

    port_t port = key_list_->GetPort(key_str);

    if ( ports_.count(port) == 0 )
    {
        Connection connection(connection_);
        connection.SetPort(port);

        string* connection_str = new string(connection.GetString());

        Log() << "zthread_new() - connection = " << connection.GetString() << endl;
        gQueueSize = queue_size_;
        zthread_new(ReactorStart, (void*)connection_str);
        ports_.insert(port);
    }

    zframe_t* id_frame = socket_.PopFrame();
    port_t id = FrameToPort(id_frame);

    Connection connection(connection_);
    connection.SetPort(id);
    socket_.ConnectOut(connection);

    zframe_t* port_frame = zframe_new(&port, sizeof(port));
    socket_.SendFrame(key, ZFRAME_MORE);
    socket_.SendFrame(port_frame, 0);

    Log() << "Registrar::ProcessMessage() - send answer = " << port << " to " << connection.GetString() << endl;
}

void Registrar::SetKeyLimit(int limit)
{
    key_list_->SetKeyLimit(limit);
}

void Registrar::SetQueueSize(int size)
{
    queue_size_ = size;
}
