#include "functions.h"

#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>

using namespace std;
using namespace zero_cache;

string zero_cache::IncrementPort(string connection, int increment)
{
    /* FIXME: Add checking to TCP connection type */
    size_t pos = connection.find_last_of('/') + 1;
    string port = connection.substr(pos, connection.size());

    int num_port = atoi(port.c_str());
    num_port = num_port + increment;

    char new_port[100];
    sprintf(new_port, "%d", num_port);

    string result = connection.substr(0, pos);
    result += new_port;
    return result;
}

string zero_cache::FrameToString(zframe_t* frame)
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
