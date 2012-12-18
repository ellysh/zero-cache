#ifndef SINGLETON_H
#define SINGLETON_H

#include <cstddef>

namespace serial
{

template <typename T>
class Singleton
{
public:
    static T* Instance()
    {
        if (instance_ == NULL)
            instance_ = new T();

        return instance_;
    }

private:
    static T* instance_;
    Singleton() {};
};

template <typename T>
T* Singleton<T>::instance_ = NULL;

}

#endif
