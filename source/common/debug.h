#ifndef DEBUG_H
#define DEBUG_H

#include <fstream>

#include "types_zcache.h"

namespace zero_cache
{

class Debug
{
public:
    Debug(const char* log_file);
    virtual ~Debug();

    void Log(const char* fmt, ...) const;
    void PrintMsg(void* msg) const;

private:
    mutable std::ofstream file_;

    DISALLOW_COPY_AND_ASSIGN(Debug);
};

}

#endif
