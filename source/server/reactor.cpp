#include "reactor.h"

#include <czmq.h>

#include "zsignal.h"

using namespace std;
using namespace zero_cache;

Reactor::Reactor(string log_file, string connection) : Debug(log_file)
{
    socket_.Bind(connection);
    socket_.SetQueueSize(1000);
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
    char* key_str = zframe_strdup(key);

    if ( DecodeCommand(command) == kWrite )
        WriteData(key_str);

    if ( DecodeCommand(command) == kRead )
        ReadData(key_str);

    free(key_str);
    zframe_destroy(&key);
    zframe_destroy(&command);
}

void Reactor::WriteData(char* key_str)
{
    zframe_t* data = socket_.PopFrame();

    Log() << "write: key = " << key_str;
    PrintFrame(data);

    container_.WriteData(string(key_str), data);
    zframe_destroy(&data);
}

void Reactor::ReadData(char* key_str)
{
    Log() << "read: key = " << key_str;

    zframe_t* data = container_.ReadData(string(key_str));
    bool is_data_empty = false;

    if ( data == NULL )
    {
        is_data_empty = true;
        data = zframe_new(NULL, 0);
    }

    PrintFrame(data);

    socket_.SendFrame(data, ZFRAME_REUSE);

    if ( is_data_empty )
        zframe_destroy(&data);
}

void Reactor::SetQueueSize(int size)
{
    socket_.SetQueueSize(size);
}
