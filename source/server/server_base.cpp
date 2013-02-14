#include "server_base.h"

#include <assert.h>

#include "interrupt_signal.h"
#include "functions.h"
#include "connection.h"
#include "socket_list.h"

using namespace std;
using namespace zero_cache;

ServerBase::ServerBase(const char* log_file, Connection connection, const SocketType type) :
    Debug(log_file), socket_(type), connection_(connection)
{
    SocketList::Instance(type);

    socket_.BindIn(connection);
    socket_.SetQueueSize(1000);
}

void ServerBase::Start(long timeout)
{
    AssignSignalHandler();

    while ( ! gIsInterrupt )
    {
        if ( ! ProcessMessage(timeout) )
        {
            SocketList* out_sockets = SocketList::Instance();
            out_sockets->RemoveSockets();
        }
    }
}

bool ServerBase::ProcessMessage(long timeout)
{
    if ( ! request_.Receive(socket_, timeout) )
        return false;

    connection_.SetHost(request_.GetHost());

    SocketList* out_sockets = SocketList::Instance();
    out_sockets->CreateSocket(connection_, request_.GetId());

    PerformCommand();

    return true;
}
