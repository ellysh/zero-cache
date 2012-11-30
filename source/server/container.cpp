#include "container.h"

using namespace std;
using namespace zero_cache;

Container::~Container()
{
    /* FIXME: Implement map_ cleanup here */
}

void Container::WriteData(string key, zframe_t* data)
{
    if ( map_.count(key) != 0 )
        zframe_reset(map_[key], zframe_data(data), zframe_size(data));
    else
        map_[key] = data;
}

zframe_t* Container::ReadData(string key)
{
    if ( map_.count(key) != 0 )
        return map_[key];
    else
        return 0;
}
