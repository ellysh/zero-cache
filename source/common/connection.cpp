#include "connection.h"

#include <iostream>
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
    {
        cout << "error: undefined connection type" << endl;
        exit(1);
    }

    string port = connection.substr(pos, connection.size());

    port_ = StringToInt(port);
    if ( port_ < 0 )
    {
        cout << "error: specified socked file or tcp port is not in the number format" << endl;
        exit(1);
    }

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
