#include "socket_list.h"

#include <algorithm>

#include "socket.h"
#include "connection.h"

using namespace std;
using namespace zero_cache;

static void RemoveSocket(SocketList::PortSocket::value_type socket_pair)
{
    delete socket_pair.second;
}

SocketList::~SocketList()
{
    for_each(sockets_.begin(), sockets_.end(),
             RemoveSocket);

    sockets_.clear();
}

Socket& SocketList::GetSocket(port_t port)
{
    return *sockets_[port];
}

void SocketList::CreateSocket(Connection& connection, port_t port)
{
    if ( sockets_.count(port) != 0 )
        return;

    Connection new_connection(connection);
    new_connection.SetPort(port);

    Socket* socket = new Socket(type_);
    socket->ConnectOut(new_connection);
    sockets_.insert(PortSocket::value_type(port, socket));
}
