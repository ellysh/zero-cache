#ifndef KEY_LIST_H
#define KEY_LIST_H

#include <string>
#include <map>

#include "types_zcache.h"

namespace zero_cache
{

class Connection;

class KeyList
{
public:
    typedef std::map<std::string, port_t> KeyPort;

public:
    explicit KeyList(const Connection& connection);
    ~KeyList();

    void AddKey(const std::string& key);
    port_t GetPort(const std::string& key) const;
    std::string GetKeys() const;

    void SetKeyLimit(const int key_limit);

private:
    int key_counter_;
    port_t current_port_;
    mutable KeyPort ports_;
    int key_limit_;

    DISALLOW_COPY_AND_ASSIGN(KeyList)
};

}

#endif
