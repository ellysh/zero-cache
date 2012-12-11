#include "registrar.h"

#include "zsignal.h"
#include "reactor.h"
#include "key_list.h"
#include "functions.h"

using namespace std;
using namespace zero_cache;

static int gQueueSize;

Registrar::Registrar(string log_file, string connection) : Debug(log_file), queue_size_(1000)
{
    socket_.Bind(connection);
    socket_.SetQueueSize(1);

    key_list_ = new KeyList(connection);
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

    Reactor reactor("", connection);

    reactor.SetQueueSize(gQueueSize);

    reactor.Start();
}

void Registrar::ProcessMessage()
{
    socket_.ReceiveMsg();

    zframe_t* key = socket_.PopFrame();
    string key_str = FrameToString(key);

    Log() << "Registrar::ProcessMessage() - key = " << key_str << endl;
    string connection = key_list_->GetConnection(key_str);

    if ( connection.empty() )
    {
        key_list_->AddKey(key_str);
        connection = key_list_->GetConnection(key_str);

        Log() << "zthread_new() - connection = " << connection << endl;
        gQueueSize = queue_size_;
        zthread_new(ReactorStart, const_cast<char*>(connection.c_str()));
    }

    socket_.SendFrame(key, ZFRAME_REUSE + ZFRAME_MORE);
    socket_.SendString(connection);

    Log() << "Registrar::ProcessMessage() - send answer = " << connection << endl;

    zframe_destroy(&key);
}

void Registrar::SetKeyLimit(int limit)
{
    key_list_->SetKeyLimit(limit);
}

void Registrar::SetQueueSize(int size)
{
    queue_size_ = size;
}
