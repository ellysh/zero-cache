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
    Debug(const char* log_file);
    virtual ~Debug();

    std::ostream& Log();
    void Log(const char* fmt, ...);
    void PrintFrame(zframe_t* frame);

private:
    std::ofstream file_;

    DISALLOW_COPY_AND_ASSIGN(Debug);
};

}

#endif
