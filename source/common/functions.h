#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <string>
#include <czmq.h>

#include "types_zcache.h"

namespace zero_cache
{

port_t MsgToPort(zmq_msg_t& msg);
std::string MsgToString(zmq_msg_t& msg);

port_t StringToPort(std::string& value);
void SetPermission(const char* connection);
port_t GenerateId(void* pointer);
bool IsMsgEqual(zmq_msg_t& left, zmq_msg_t& right);
void MsgDataFree(void* data, void* hint);

}

#endif
