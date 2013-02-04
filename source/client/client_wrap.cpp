#include "client_wrap.h"

using namespace std;
using namespace zero_cache;

ClientWrap::ClientWrap(const char* log_file, Connection connection, const SocketType type) :
    client_(log_file, connection, type)
{
}

void ClientWrap::SetQueueSize(const int size)
{
    client_.SetQueueSize(size);
}

void ClientWrap::SetHost(const string host)
{
    client_.SetHost(host);
}

void ClientWrap::WriteLong(const string key, const long value)
{
    /* FIXME: Implement this method */
}

void ClientWrap::WriteDouble(const string key, const double value)
{
    /* FIXME: Implement this method */
}

void ClientWrap::WriteString(const string key, const string value)
{
    /* FIXME: Implement this method */
}

long ClientWrap::ReadLong(const string key) const
{
    /* FIXME: Implement this method */
    return 0;
}

double ClientWrap::ReadDouble(const string key) const
{
    /* FIXME: Implement this method */
    return 0;
}

string ClientWrap::ReadString(const string key) const
{
    /* FIXME: Implement this method */
    return "";
}

KeyArray ClientWrap::GetKeys()
{
    return client_.GetKeys();
}
