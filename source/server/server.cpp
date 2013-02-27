#include "server.h"

#include "interrupt_signal.h"

using namespace std;
using namespace zero_cache;

Server::Server(const char* log_file, Connection connection, const SocketType type) :
    Debug(log_file)
{
    /* FIXME: Implement this method */
}

void Server::Start(const long timeout)
{
    AssignSignalHandler();

    while ( ! gIsInterrupt )
        ProcessMessage(timeout);
}

bool Server::ProcessMessage(const long timeout)
{
    /* FIXME: Implement this method */
}
