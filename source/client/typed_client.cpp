#include "typed_client.h"

using namespace std;
using namespace zero_cache;

TypedClient::TypedClient(const char* log_file) : client_(log_file)
{
}

void TypedClient::WriteLong(const size_t index, const long value)
{
    client_.WriteValue(index, &value, sizeof(value));
}

void TypedClient::WriteDouble(const size_t index, const double value)
{
    client_.WriteValue(index, &value, sizeof(value));
}

long TypedClient::ReadLong(const size_t index) const
{
    long result;
    client_.ReadValue(index, &result, sizeof(result));

    return result;
}

double TypedClient::ReadDouble(const size_t index) const
{
    double result;
    client_.ReadValue(index, &result, sizeof(result));

    return result;
}
