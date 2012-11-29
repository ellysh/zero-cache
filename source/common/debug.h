#ifndef DEBUG_H
#define DEBUG_H

#include <fstream>

namespace zero_cache
{

class Debug
{
public:
    Debug(std::string log_file);
    ~Debug();

    std::ostream& Log();
    void Log(const char* fmt, ...);

private:
    std::string log_file_;
    std::ofstream file_;
};

}

#endif
