#include "client.h"

#include "connection.h"

using namespace std;
using namespace zero_cache;

Client::Client(const char* log_file, Connection connection, const SocketType type)
{
    /* FIXME: Implement this method */
}

void Client::WriteData(const string& key, const Package package) const
{
    /* FIXME: Implement this method */
}

Package Client::ReadData(const string& key)
{
    /* FIXME: Implement this method */
}
