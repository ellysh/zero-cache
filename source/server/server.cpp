#include "server.h"

#include "connection.h"

using namespace std;
using namespace zero_cache;

Server::Server(const char* log_file, Connection connection, const SocketType type) :
    Debug(log_file)
{
    /* FIXME: Implement this method */
}

void Server::Start(long timeout)
{
    /* FIXME: Implement this method */
}

bool Server::ProcessMessage(long timeout)
{
    /* FIXME: Implement this method */
}
