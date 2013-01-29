#include "client_base.h"

#include "connection.h"
#include "functions.h"

using namespace std;
using namespace zero_cache;

ClientBase::ClientBase(const char* log_file, Connection connection, SocketType type) : Debug(log_file), socket_(type)
{
    Log("ClientBase::ClientBase() - connect %s\n", connection.GetString().c_str());
    socket_.ConnectOut(connection);

    port_t* id = new port_t(GenerateId(this));
    connection.SetPort(*id);

    SetHost(connection.GetHost());

    if ( connection.GetProtocol() == kTcpProtocol )
        connection.SetHost("*:");

    Log("ClientBase::ClientBase() - bind %s\n", connection.GetString().c_str());
    socket_.BindIn(connection);
    socket_.SetQueueSize(10);

    zmq_msg_init_data(&id_msg_, id, sizeof(*id), MsgDataFree, NULL);

    zmq_msg_init(&command_msg_);
    zmq_msg_init(&key_msg_);
}

ClientBase::~ClientBase()
{
    zmq_msg_close(&key_msg_);
    zmq_msg_close(&command_msg_);
    zmq_msg_close(&id_msg_);
    zmq_msg_close(&host_msg_);
}

void ClientBase::SetHost(string host)
{
    MsgInitString(host_msg_, host);
}
