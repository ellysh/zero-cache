#include "functions.h"

#include <stdlib.h>
#include <stdio.h>

using namespace std;
using namespace zero_cache;

string zero_cache::IncrementPort(string connection, int increment)
{
    size_t pos = connection.find_last_of('/') + 1;
    string port = connection.substr(pos, connection.size());

    int num_port = atoi(port.c_str());
    num_port++;

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
