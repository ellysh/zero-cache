#include "connection.h"

#include "functions.h"
#include "speaker.h"

using namespace std;
using namespace zero_cache;

Connection::Connection(const string& connection)
{
    Constructor(connection);
}

Connection::Connection(const char* connection)
{
    string connection_str(connection);

    Constructor(connection_str);
}

void Connection::Constructor(const string& connection)
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

void Connection::SetHost(const string host)
{
    host_ = host;
}

string& Connection::GetHost() const
{
    return host_;
}

void Connection::SetPort(const port_t port)
{
    port_ = port;
}

port_t Connection::GetPort() const
{
    return port_;
}

string& Connection::GetProtocol() const
{
    return protocol_;
}

string Connection::GetString() const
{
    char port[100];
    sprintf(port, "%lu", port_);
    string result = protocol_ + host_ + port;
    return result;
}
