#include "client_base.h"

#include <assert.h>

#include "connection.h"
#include "functions.h"
#include "request.h"

using namespace std;
using namespace zero_cache;

ClientBase::ClientBase(const char* log_file, Connection connection, SocketType type) : Debug(log_file), socket_(type)
{
    Log("ClientBase::ClientBase() - connect %s\n", connection.GetString().c_str());
    socket_.ConnectOut(connection);

    id_ = new port_t(GenerateId(this));
    connection.SetPort(*id_);

    if ( connection.GetProtocol() == kTcpProtocol )
        connection.SetHost("*:");

    Log("ClientBase::ClientBase() - bind %s\n", connection.GetString().c_str());
    socket_.BindIn(connection);
    socket_.SetQueueSize(10);
}

ClientBase::~ClientBase()
{
    delete id_;

    assert( request_ != NULL );
    delete request_;
}

void ClientBase::SetHost(string host)
{
    request_ = new Request(*id_, host);
}
