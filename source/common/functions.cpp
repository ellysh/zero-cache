#include "functions.h"

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <sys/stat.h>

using namespace std;
using namespace zero_cache;

static const size_t kFileNamePos = 6;

port_t zero_cache::StringToPort(const string& value)
{
    char* endptr;
    port_t result = strtoul(value.c_str(), &endptr, 10);

    if ( endptr != value.c_str() )
        return result;
    else
        return kErrorPort;
}

void zero_cache::SetPermission(const char* connection)
{
    if ( strlen(connection) <= kFileNamePos )
        return;

    const char* file = connection + kFileNamePos;
    chmod(file, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
}

port_t zero_cache::GenerateId(const void* pointer)
{
    srand(reinterpret_cast<unsigned long>(pointer));

    port_t result = rand() % 0x10000;

    return result;
}
