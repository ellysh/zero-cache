#include "client_wrap.h"

#include <stdlib.h>

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
    client_.WriteData(key, &value, sizeof(value));
}

void ClientWrap::WriteDouble(const string key, const double value)
{
    client_.WriteData(key, &value, sizeof(value));
}

void ClientWrap::WriteString(const string key, const string value)
{
    client_.WriteData(key, value.c_str(), value.size());
}

long ClientWrap::ReadLong(const string key) const
{
    void* data = client_.ReadData(key);

    if ( data == NULL )
        return 0;

    long result = *(static_cast<long*>(data));

    free(data);

    return result;
}

double ClientWrap::ReadDouble(const string key) const
{
    void* data = client_.ReadData(key);

    if ( data == NULL )
        return 0;

    double result = *(static_cast<double*>(data));

    free(data);

    return result;
}

string ClientWrap::ReadString(const string key) const
{
    void* data = client_.ReadData(key);

    if ( data == NULL )
        return "";

    string result(static_cast<char*>(data));

    free(data);

    return result;
}

KeyArray ClientWrap::GetKeys()
{
    return client_.GetKeys();
}
