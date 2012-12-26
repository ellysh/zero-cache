#include "socket_list.h"

#include <algorithm>

#include "socket.h"

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
