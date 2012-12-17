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
