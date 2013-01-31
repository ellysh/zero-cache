#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <string>
#include <zmq.h>

#include "types_zcache.h"

namespace zero_cache
{

void* ZmqMsgData(const zmq_msg_t& msg);
size_t ZmqMsgSize(const zmq_msg_t& msg);

port_t MsgToPort(const zmq_msg_t& msg);
std::string MsgToString(const zmq_msg_t& msg);
KeyArray MsgToKeyArray(const zmq_msg_t& msg);

port_t StringToPort(const std::string& value);
void SetPermission(const char* connection);
port_t GenerateId(const void* const pointer);

void MsgDataFree(void* data, void* hint);
void MsgInitString(zmq_msg_t& msg, std::string& str);
void MsgInitData(zmq_msg_t& msg, const void* data, const size_t size);

}

#endif
