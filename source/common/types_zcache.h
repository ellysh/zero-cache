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

/* Macros for binary functor for STL container definition */
#define BINARY_FUNCTOR(Name, type1, name1, type2, name2) \
struct Name : public binary_function<type1, type2, void> \
{ \
    void operator()(type1 name1, type2 name2) const \
    {

#define END_BINARY_FUNCTOR \
    } \
};

}

#endif
