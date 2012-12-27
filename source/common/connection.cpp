#include "connection.h"

#include "functions.h"
#include "speaker.h"

using namespace std;
using namespace zero_cache;

Connection::Connection(string& connection)
{
    Constructor(connection);
}

Connection::Connection(const char* connection)
{
    string connection_str(connection);

    Constructor(connection_str);
}

void Connection::Constructor(string& connection)
{
    size_t pos;
    if ( connection.find(kTcpProtocol) != string::npos )
        pos = connection.find_last_of(':') + 1;
    else if ( connection.find(kIpcProtocol) != string::npos )
        pos = connection.find_last_of('/') + 1;
    else
        Speaker::Instance()->PrintError(kSocketTypeError);

    string port = connection.substr(pos, connection.size());

    port_ = StringToPort(port);
    if ( port_ < 0 )
        Speaker::Instance()->PrintError(kSocketNameError);

    protocol_ = connection.substr(0, 6);
    host_ = connection.substr(6, (pos - 6));
}

void Connection::SetHost(string host)
{
    host_ = host;
}

void Connection::SetPort(port_t port)
{
    port_ = port;
}

port_t Connection::GetPort()
{
    return port_;
}

string& Connection::GetProtocol()
{
    return protocol_;
}

string Connection::GetString()
{
    char port[100];
    sprintf(port, "%lu", port_);
    string result = protocol_ + host_ + port;
    return result;
}
