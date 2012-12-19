#include "debug.h"

#include <iostream>

#include <stdio.h>
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

ostream& Debug::Log()
{
    return file_;
}

void Debug::Log(const char* fmt, ...)
{
    char buf[4096];
    va_list arg_list;
    va_start( arg_list, fmt );
    vsprintf( buf, fmt, arg_list );

    Log() << buf << endl;
    va_end( arg_list );
}

void Debug::PrintFrame(zframe_t* frame)
{
#ifdef __DEBUG__
    char* data_hex = zframe_strhex(frame);
    file_ << " data = " << data_hex << endl;
    free(data_hex);
#endif
}
