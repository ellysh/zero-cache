#ifndef KEY_LIST_H
#define KEY_LIST_H

#include <string>
#include <map>

#include "port_counter.h"
#include "types_zcache.h"

namespace zero_cache
{

class Connection;

class KeyList
{
public:
    typedef std::map<std::string, PortCounter*> KeyPort;

public:
    explicit KeyList(Connection& connection) : connection_(connection), current_counter_(NULL) {};
    ~KeyList();

    void AddKey(std::string key);
    int GetPort(std::string key);

    void SetKeyLimit(int key_limit);

private:
    Connection& connection_;
    PortCounter* current_counter_;
    KeyPort ports_;
    int key_limit_;

    DISALLOW_COPY_AND_ASSIGN(KeyList)
};

}

#endif
