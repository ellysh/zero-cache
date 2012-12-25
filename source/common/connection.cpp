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
    if ( connection.find("tcp") != string::npos )
        pos = connection.find_last_of(':') + 1;
    else if ( connection.find("ipc") != string::npos )
        pos = connection.find_last_of('/') + 1;
    else
        Speaker::Instance()->PrintError(kSocketTypeError);

    string port = connection.substr(pos, connection.size());

    port_ = StringToInt(port);
    if ( port_ < 0 )
        Speaker::Instance()->PrintError(kSocketNameError);

    host_ = connection.substr(0, pos);
}

const char* Connection::GetString()
{
    char port[100];
    sprintf(port, "%lu", port_);
    string result = host_ + port;
    return result.c_str();
}

port_t Connection::GetPort()
{
    return port_;
}

void Connection::SetPort(port_t port)
{
    port_ = port;
}
