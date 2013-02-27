#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <string>

#include "types_zcache.h"

namespace zero_cache
{

port_t StringToPort(const std::string& value);
void SetPermission(const char* connection);
port_t GenerateId(const void* const pointer);

}

#endif
