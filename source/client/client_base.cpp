#include "client_base.h"

#include <assert.h>

#include "connection.h"
#include "functions.h"
#include "request.h"

using namespace std;
using namespace zero_cache;

ClientBase::ClientBase(const char* log_file, Connection connection, SocketType type) :
    Debug(log_file), socket_(type), request_(NULL)
{
    Log("ClientBase::ClientBase() - connect %s\n", connection.GetString().c_str());
    socket_.ConnectOut(connection);

    id_ = GenerateId(this);
    connection.SetPort(id_);

    if ( connection.GetProtocol() == kTcpProtocol )
        connection.SetHost("*:");

    Log("ClientBase::ClientBase() - bind %s\n", connection.GetString().c_str());
    socket_.BindIn(connection);
    socket_.SetQueueSize(10);
}

ClientBase::~ClientBase()
{
    assert( request_ != NULL );
    delete request_;
}

void ClientBase::SetHost(string host)
{
    if ( request_ != NULL )
        delete request_;

    request_ = new Request(id_, host);
}
