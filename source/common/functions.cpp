#include "functions.h"

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <sys/stat.h>

using namespace std;
using namespace zero_cache;

static const size_t kFileNamePos = 6;

void* zero_cache::ZmqMsgData(const zmq_msg_t& msg)
{
    return zmq_msg_data(const_cast<zmq_msg_t*>(&msg));
}

size_t zero_cache::ZmqMsgSize(const zmq_msg_t& msg)
{
    return zmq_msg_size(const_cast<zmq_msg_t*>(&msg));
}

port_t zero_cache::MsgToPort(const zmq_msg_t& msg)
{
    port_t* result = static_cast<port_t*>(ZmqMsgData(msg));

    return *result;
}

string zero_cache::MsgToString(const zmq_msg_t& msg)
{
    char* buffer =  static_cast<char*>(ZmqMsgData(msg));
    assert( buffer != NULL );
    string result(buffer, ZmqMsgSize(msg));

    return result;
}

KeyArray zero_cache::MsgToKeyArray(const zmq_msg_t& msg)
{
    char* buffer =  static_cast<char*>(ZmqMsgData(msg));
    assert( buffer != NULL );
    KeyArray result(buffer, buffer + ZmqMsgSize(msg));

    return result;
}

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

void zero_cache::MsgDataFree(void* data, void* hint)
{
    free(data);
}

void zero_cache::MsgInitString(zmq_msg_t& msg, const string& str)
{
    MsgInitData(msg, str.c_str(), str.size());
}

void zero_cache::MsgInitData(zmq_msg_t& msg, const void* data, const size_t size)
{
    zmq_msg_init_size(&msg, size);

    memcpy(zmq_msg_data(&msg), data, size);
}
