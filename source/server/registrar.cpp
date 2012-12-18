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

Registrar::Registrar(string log_file, Connection connection, SocketType type) :
    Debug(log_file), socket_(type), queue_size_(1000), connection_(connection)
{
    socket_.Bind(connection);
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
    char* connection = static_cast<char*>(args);

    Reactor reactor("", connection, gSocketType);

    reactor.SetQueueSize(gQueueSize);

    reactor.Start();
}

void Registrar::ProcessMessage()
{
    socket_.ReceiveMsg();

    zframe_t* key = socket_.PopFrame();
    string key_str = FrameToString(key);

    Log() << "Registrar::ProcessMessage() - key = " << key_str << endl;
    key_list_->AddKey(key_str);

    int port = key_list_->GetPort(key_str);

    if ( ports_.count(port) == 0 )
    {
        Connection connection(connection_);
        connection.SetPort(port);

        Log() << "zthread_new() - connection = " << connection.GetString() << endl;
        gQueueSize = queue_size_;
        zthread_new(ReactorStart, const_cast<char*>(connection.GetString().c_str()));
        ports_.insert(port);
    }

    zframe_t* port_frame = zframe_new(&port, sizeof(port));
    socket_.SendFrame(key, ZFRAME_MORE);
    socket_.SendFrame(port_frame, 0);

    Log() << "Registrar::ProcessMessage() - send answer = " << port << endl;
}

void Registrar::SetKeyLimit(int limit)
{
    key_list_->SetKeyLimit(limit);
}

void Registrar::SetQueueSize(int size)
{
    queue_size_ = size;
}
