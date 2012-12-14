#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <string>
#include <czmq.h>

namespace zero_cache
{

std::string IncrementPort(std::string connection, int increment);
std::string FrameToString(zframe_t* frame);
void SetPermission(std::string connection);

}

#endif
