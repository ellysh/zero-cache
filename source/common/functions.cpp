#include "functions.h"

#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>

using namespace std;
using namespace zero_cache;


int zero_cache::FrameToInt(zframe_t* frame)
{
    byte* buffer = zframe_data(frame);
    int result = *buffer;

    return result;
}

std::string zero_cache::FrameToString(zframe_t* frame)
{
    char* buffer =  zframe_strdup(frame);
    string result = buffer;
    free(buffer);

    return result;
}

void zero_cache::SetPermission(string connection)
{
    /* FIXME: Return from function if connection have TCP type */

    string file = connection.substr(6, connection.size());
    chmod(file.c_str(), S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
}
