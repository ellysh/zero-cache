#ifndef KEY_LIST_H
#define KEY_LIST_H

#include <string>
#include <map>

#include "port_counter.h"
#include "types_zcache.h"

namespace zero_cache
{

class KeyList
{
public:
    typedef std::map<std::string, PortCounter*> KeyPort;

public:
    explicit KeyList(std::string connection) : connection_str_(connection), current_counter_(NULL) {};
    ~KeyList();

    void AddKey(std::string key);
    std::string GetConnection(std::string key);

    void SetKeyLimit(int key_limit);

private:
    std::string connection_str_;
    PortCounter* current_counter_;
    KeyPort ports_;
    int key_limit_;

    DISALLOW_COPY_AND_ASSIGN(KeyList)
};

}

#endif
