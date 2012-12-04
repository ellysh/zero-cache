#include "program_options.h"

#include <algorithm>

using namespace std;
using namespace zero_cache;

char* ProgramOptions::GetOption(const string& option)
{
    char ** itr = find(begin_, end_, option);

    if ( (itr != end_) && (++itr != end_) )
        return *itr;
    else
        return 0;
}

bool ProgramOptions::IsOptionExist(const string& option)
{
    return find(begin_, end_, option) != end_;
}

