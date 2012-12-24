#include "functions.h"

#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>

#include "types_zcache.h"

using namespace std;
using namespace zero_cache;

static const size_t kFileNamePos = 6;

int zero_cache::FrameToInt(zframe_t* frame)
{
    int* result = (int*)zframe_data(frame);

    return *result;
}

std::string zero_cache::FrameToString(zframe_t* frame)
{
    char* buffer =  zframe_strdup(frame);
    string result = buffer;
    free(buffer);

    return result;
}

int zero_cache::StringToInt(string& value)
{
    char* endptr;
    int result = strtol(value.c_str(), &endptr, 10);

    if ( endptr != value.c_str() )
        return result;
    else
        return kErrorConv;
}

void zero_cache::SetPermission(const char* connection)
{
    if ( strlen(connection) <= kFileNamePos )
        return;

    const char* file = connection + kFileNamePos;
    chmod(file, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
}

string zero_cache::GenerateId(void* pointer)
{
    char address[16];
    sprintf(address, "%p", pointer);

    char number[5];
    sprintf(number, "%04x", randof(0x10000));

    string result(address, 2, 12);
    result += number;
    return result;
}
