#ifndef PROGRAM_OPTIONS_H
#define PROGRAM_OPTIONS_H

#include <string>

#include "types_zcache.h"

namespace zero_cache
{

class ProgramOptions
{
public:
    ProgramOptions(char** begin, char** end) : begin_(begin), end_(end) {};

    char* GetOption(const std::string& option);
    bool IsOptionExist(const std::string& option);

private:
    char** begin_;
    char** end_;

    DISALLOW_COPY_AND_ASSIGN(ProgramOptions)
};

}

#endif
