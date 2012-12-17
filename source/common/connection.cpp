#include "connection.h"

using namespace std;
using namespace zero_cache;

Connection::Connection(std::string connection) : connection_(connection)
{
    /* FIXME: Implement connection string parsing */
}

string Connection::GetString()
{
    return connection_;
}

string Connection::GetPort()
{
    size_t pos = connection_.find_last_of('/') + 1;

    string port = connection_.substr(pos, connection_.size());

    return port;
}
