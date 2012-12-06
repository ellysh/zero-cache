#ifndef KEY_LIST_H
#define KEY_LIST_H

#include <string>
#include <map>

#include "types_zcache.h"

namespace zero_cache
{

class KeyList
{
public:
    KeyList() {};

    void AddKey(std::string key);
    std::string GetConnection(std::string key);

private:
    DISALLOW_COPY_AND_ASSIGN(KeyList)
};

}

#endif
