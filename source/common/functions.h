#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <string>
#include <zmq.h>

#include "types_zcache.h"

namespace zero_cache
{

port_t MsgToPort(zmq_msg_t& msg);
std::string MsgToString(zmq_msg_t& msg);
KeyArray MsgToKeyArray(zmq_msg_t& msg);

port_t StringToPort(std::string& value);
void SetPermission(const char* connection);
port_t GenerateId(void* pointer);

void MsgDataFree(void* data, void* hint);
void MsgInitString(zmq_msg_t& msg, std::string& str);
void MsgInitData(zmq_msg_t& msg, void* data, size_t size);

Command DecodeCommand(zmq_msg_t& msg);

}

#endif
