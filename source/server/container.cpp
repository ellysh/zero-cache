#include "container.h"

using namespace std;
using namespace zero_cache;

void Container::WriteData(string key, int data)
{
    mutex_.lock();
    data_[key] = data;
    mutex_.unlock();
}

int Container::ReadData(string key)
{
    mutex_.lock();
    if (data_.count(key) != 0 )
        return data_[key];
    else
        return 0;
    mutex_.unlock();
}
