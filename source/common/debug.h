#ifndef DEBUG_H
#define DEBUG_H

#include <fstream>
#include <czmq.h>

#include "types_zcache.h"

namespace zero_cache
{

class Debug
{
public:
    Debug(std::string log_file);
    ~Debug();

    std::ostream& Log();
    void Log(const char* fmt, ...);
    void PrintFrame(zframe_t* frame);

private:
    std::string log_file_;
    std::ofstream file_;

    DISALLOW_COPY_AND_ASSIGN(Debug);
};

}

#endif
