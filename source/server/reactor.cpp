#include "reactor.h"

#include <czmq.h>

#include "zsignal.h"
#include "functions.h"
#include "connection.h"

using namespace std;
using namespace zero_cache;

Reactor::Reactor(const char* log_file, Connection connection, SocketType type) :
    Debug(log_file), socket_(type), connection_(connection)
{
    socket_.BindIn(connection);
    socket_.SetQueueSize(1000);
}

Reactor::~Reactor()
{
    /* FIXME: Clean up the out_sockets_ map here */
}

void Reactor::Start()
{
    while (true)
        ProcessMessage();
}

static Command DecodeCommand(zframe_t* frame)
{
    Command command = kWrite;
    zframe_t* set_frame = zframe_new(&command, sizeof(Command));

    if ( zframe_eq(frame, set_frame) )
        command = kWrite;
    else
        command = kRead;

    zframe_destroy(&set_frame);

    return command;
}

void Reactor::ProcessMessage()
{
    socket_.ReceiveMsg();

    zframe_t* command = socket_.PopFrame();
    zframe_t* key =  socket_.PopFrame();
    string key_str = FrameToString(key);

    zframe_t* id_frame =  socket_.PopFrame();
    port_t id = FrameToPort(id_frame);

    AddOutSocket(id);

    if ( DecodeCommand(command) == kWrite )
        WriteData(key_str);

    if ( DecodeCommand(command) == kRead )
        ReadData(key_str, id);

    zframe_destroy(&key);
    zframe_destroy(&command);
}

void Reactor::WriteData(string& key)
{
    zframe_t* data = socket_.PopFrame();

    Log() << "write: key = " << key;
    PrintFrame(data);

    container_.WriteData(key, data);
    zframe_destroy(&data);
}

void Reactor::ReadData(string& key, port_t id)
{
    Log() << "read: key = " << key;

    zframe_t* data = container_.ReadData(key);
    bool is_data_empty = false;

    if ( data == NULL )
    {
        is_data_empty = true;
        data = zframe_new(NULL, 0);
    }

    PrintFrame(data);

    zframe_t* key_frame = zframe_new(key.c_str(), key.size());
    out_sockets_[id]->SendFrame(key_frame, ZFRAME_MORE);
    out_sockets_[id]->SendFrame(data, ZFRAME_REUSE);

    if ( is_data_empty )
        zframe_destroy(&data);
}

void Reactor::AddOutSocket(port_t id)
{
    if ( out_sockets_.count(id) != 0 )
        return;

    Connection connection(connection_);
    connection.SetPort(id);

    /* FIXME: Specify the correct type for this socket */
    Socket* socket = new Socket();
    socket->ConnectOut(connection);
    out_sockets_.insert(PortSocket::value_type(id, socket));
}

void Reactor::SetQueueSize(int size)
{
    socket_.SetQueueSize(size);
}
