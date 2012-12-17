#ifndef CONNECTION_H
#define CONNECTION_H

#include <string>

namespace zero_cache
{

class Connection
{
public:
    Connection(std::string connection);
    std::string GetString();

private:
    std::string connection_;
};

}

#endif
