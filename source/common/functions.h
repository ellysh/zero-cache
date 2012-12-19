#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <string>
#include <czmq.h>

namespace zero_cache
{

int FrameToInt(zframe_t* frame);
std::string FrameToString(zframe_t* frame);
int StringToInt(std::string& value);
void SetPermission(const char* connection);

}

#endif
