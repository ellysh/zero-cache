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

void zero_cache::SetPermission(string connection)
{
    if ( connection.size() <= kFileNamePos )
        return;

    string file = connection.substr(kFileNamePos, connection.size());
    chmod(file.c_str(), S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
}
