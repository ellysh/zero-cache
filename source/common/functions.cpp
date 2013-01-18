#include "functions.h"

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <sys/stat.h>

using namespace std;
using namespace zero_cache;

static const size_t kFileNamePos = 6;

port_t zero_cache::MsgToPort(zmq_msg_t& msg)
{
    port_t* result = (port_t*)zmq_msg_data(&msg);

    return *result;
}

string zero_cache::MsgToString(zmq_msg_t& msg)
{
    char* buffer =  (char*)zmq_msg_data(&msg);
    assert( buffer != NULL );
    string result(buffer, zmq_msg_size(&msg));

    return result;
}

port_t zero_cache::StringToPort(string& value)
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

port_t zero_cache::GenerateId(void* pointer)
{
    srand((unsigned long)pointer);
    /* FIXME: Use rand() % 0x1000000000 instead this */
    port_t result = rand() % 0x10000;

    return result;
}

bool zero_cache::IsMsgEqual(zmq_msg_t& left, zmq_msg_t& right)
{
    size_t left_size = zmq_msg_size(&left);

    if ( left_size != zmq_msg_size(&right) )
        return false;

    void* left_data = zmq_msg_data(&left);
    void* right_data = zmq_msg_data(&right);
    int is_not_equal = memcmp(left_data, right_data, left_size);

    if ( is_not_equal )
        return false;
    else
        return true;
}

void zero_cache::MsgDataFree(void* data, void* hint)
{
    free(data);
}

void zero_cache::MsgInitString(zmq_msg_t& msg, string& str)
{
    MsgInitData(msg, (void*)str.c_str(), str.size());
}

void zero_cache::MsgInitData(zmq_msg_t& msg, void* data, size_t size)
{
    zmq_msg_init_size(&msg, size);

    memcpy(zmq_msg_data(&msg), data, size);
}
