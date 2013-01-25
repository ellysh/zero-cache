#ifndef DEBUG_H
#define DEBUG_H

#include <fstream>
#include <zmq.h>

#include "types_zcache.h"

namespace zero_cache
{

class Debug
{
public:
    Debug(const char* log_file);
    virtual ~Debug();

    void Log(const char* fmt, ...);
    void PrintMsg(zmq_msg_t& msg);

private:
    std::ofstream file_;

    std::ostream& Log();

    DISALLOW_COPY_AND_ASSIGN(Debug);
};

}

#endif
