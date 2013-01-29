#ifndef TYPES_ZCACHE_H
#define TYPES_ZCACHE_H

#include <vector>
#include <string>

namespace zero_cache
{

/* A macro to disallow the copy constructor and operator= functions.
 * This should be used in the private: declarations for a class. */
#define DISALLOW_COPY_AND_ASSIGN(TypeName) \
private: \
    TypeName(const TypeName&);               \
    TypeName& operator=(const TypeName&);

typedef unsigned long port_t;
typedef std::vector<unsigned char> KeyArray;

enum Command
{
    kWrite = 0,
    kRead,
    kGetPort,
    kGetKeys
};

enum SocketType
{
    kDealer = 0,
    kPubSub
};

static const port_t kErrorPort = -1;
static std::string kTcpProtocol = "tcp://";
static std::string kIpcProtocol = "ipc://";

}

#endif
