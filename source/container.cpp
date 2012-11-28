#include "container.h"

using namespace std;
using namespace zero_cache;

void Container::WriteData(string key, int data)
{
    data_[key] = data;
}

int Container::ReadData(string key)
{
    if (data_.count(key) != 0 )
        return data_[key];
    else
        return 0;
}
