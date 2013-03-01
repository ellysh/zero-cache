#include "client.h"

using namespace std;
using namespace zero_cache;

Client::Client(const char* log_file) : Debug(log_file)
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

string Client::GetKeys()
{
    /* FIXME: Implement this method */
}
