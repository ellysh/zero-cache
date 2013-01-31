#include "client_base.h"

#include <assert.h>
#include <stdlib.h>

#include "connection.h"
#include "functions.h"
#include "request.h"

using namespace std;
using namespace zero_cache;

static const long kReadAnswerTimeout = 10;

ClientBase::ClientBase(const char* log_file, Connection connection, const SocketType type) :
    Debug(log_file), socket_(type), request_(NULL)
{
    srand(time(NULL));

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

void ClientBase::SetHost(const string host)
{
    if ( request_ != NULL )
        delete request_;

    request_ = new Request(id_, host);
}

zmq_msg_t* ClientBase::SendRequest()
{
    zmq_msg_t* result = NULL;

    do
    {
        request_->Send(socket_);
        result = ReceiveAnswer();

        if (result == NULL )
            usleep(rand() % 100);
    }
    while ( result == NULL );

    return result;
}

zmq_msg_t* ClientBase::ReceiveAnswer()
{
    if ( ! answer_.Receive(socket_, kReadAnswerTimeout) )
        return NULL;

    return answer_.GetMsg();
}
