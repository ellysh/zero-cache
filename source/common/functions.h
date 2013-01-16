#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <string>
#include <czmq.h>

#include "types_zcache.h"

namespace zero_cache
{

/* FIXME: Remove this deprecated frame functions */
port_t FrameToPort(zframe_t* frame);
std::string FrameToString(zframe_t* frame);

port_t MsgToPort(zmq_msg_t& frame);

port_t StringToPort(std::string& value);
void SetPermission(const char* connection);
port_t GenerateId(void* pointer);
bool IsMsgEqual(zmq_msg_t& left, zmq_msg_t& right);

}

#endif
