#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <string>

#include <czmq.h>
#include <stdlib.h>
#include <stdio.h>

namespace zero_cache
{

/* FIXME: Move implementation of these functions to the functions.cpp file */
static std::string IncrementPort(std::string connection, int increment)
{
    size_t pos = connection.find_last_of('/') + 1;
    std::string port = connection.substr(pos, connection.size());

    int num_port = atoi(port.c_str());
    num_port++;

    char new_port[100];
    sprintf(new_port, "%d", num_port);

    std::string result = connection.substr(0, pos);
    result += new_port;
    return result;
}

static std::string FrameToString(zframe_t* frame)
{
    char* buffer =  zframe_strdup(frame);
    std::string result = buffer;
    free(buffer);

    return result;
}

}

#endif
