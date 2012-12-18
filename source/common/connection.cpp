#include "connection.h"

#include <stdio.h>
#include <stdlib.h>

#include "functions.h"

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
        exit(1);

    string port = connection.substr(pos, connection.size());

    port_ = StringToInt(port);
    assert( port_ >= 0 );

    host_ = connection.substr(0, pos);
}

string Connection::GetString()
{
    char port[100];
    sprintf(port, "%d", port_);

    return (host_ + port);
}

int Connection::GetPort()
{
    return port_;
}

void Connection::SetPort(int port)
{
    port_ = port;
}
