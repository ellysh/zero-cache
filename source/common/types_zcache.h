#ifndef TYPES_ZCACHE_H
#define TYPES_ZCACHE_H

namespace zero_cache
{

/* A macro to disallow the copy constructor and operator= functions.
 * This should be used in the private: declarations for a class. */
#define DISALLOW_COPY_AND_ASSIGN(TypeName) \
private: \
    TypeName(const TypeName&);               \
    TypeName& operator=(const TypeName&);

static const int kEmptyPort = -1;

enum Command
{
    kWrite = 0,
    kRead
};

enum SocketType
{
    kDealer = 0,
    kPubSub
};

}

#endif
