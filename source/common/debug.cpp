#include "debug.h"

#include <iostream>

#include <stdio.h>
#include <string.h>
#include <stdarg.h>

using namespace std;
using namespace zero_cache;

static const char* kDefaultLogfile = "/dev/null";

Debug::Debug(const char* log_file)
{
#ifdef __DEBUG__
    if ( strlen(log_file) != 0 )
        file_.open(log_file, ios::out | ios::app);
    else
        file_.open(kDefaultLogfile, ios::out | ios::app);
#endif
}

Debug::~Debug()
{
#ifdef __DEBUG__
    file_.close();
#endif
}

void Debug::Log(const char* fmt, ...) const
{
#ifdef __DEBUG__
    char buf[4096];
    va_list arg_list;
    va_start(arg_list, fmt);
    vsprintf(buf, fmt, arg_list);

    file_ << buf;
    va_end(arg_list);
#endif
}

void Debug::PrintMsg(zmq_msg_t& msg) const
{
#ifdef __DEBUG__
    char* data_hex = static_cast<char*>(zmq_msg_data(&msg));
    file_ << " data = " << data_hex << endl;
#endif
}
