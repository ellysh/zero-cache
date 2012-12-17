#include "connection.h"

#include <stdlib.h>

using namespace std;
using namespace zero_cache;

Connection::Connection(std::string connection) : connection_(connection)
{
    /* FIXME: Implement connection string parsing */
}

string Connection::GetString()
{
    /* FIXME: Concatenate result from conection_ and port_ variables */
    return connection_;
}

int Connection::GetPort()
{
    /* FIXME: Add checking to TCP connection type */
    size_t pos = connection_.find_last_of('/') + 1;

    string port = connection_.substr(pos, connection_.size());

    /* FIXME: Add checking to success conversion to int type */
    return atoi(port.c_str());
}

void Connection::SetPort(int port)
{
    port_ = port;
}
