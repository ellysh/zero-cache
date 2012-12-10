#ifndef KEY_LIST_H
#define KEY_LIST_H

#include <string>
#include <map>

#include "connection.h"
#include "types_zcache.h"

namespace zero_cache
{

class KeyList
{
public:
    typedef std::map<std::string, Connection*> KeyConnection;

public:
    explicit KeyList(std::string connection) : connection_str_(connection), current_connection_(NULL) {};
    ~KeyList();

    void AddKey(std::string key);
    std::string GetConnection(std::string key);

    void SetKeyLimit(int key_limit);

private:
    std::string connection_str_;
    Connection* current_connection_;
    KeyConnection connections_;
    int key_limit_;

    DISALLOW_COPY_AND_ASSIGN(KeyList)
};

}

#endif
