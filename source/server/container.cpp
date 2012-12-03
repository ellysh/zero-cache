#include "container.h"

#include <algorithm>

using namespace std;
using namespace zero_cache;

static void RemoveFrame(Container::DataMap::value_type frame_pair)
{
    zframe_destroy(&frame_pair.second);
}

Container::~Container()
{
    for_each(map_.begin(), map_.end(),
             RemoveFrame);
}

void Container::WriteData(string key, zframe_t* data)
{
    if ( map_.count(key) != 0 )
        zframe_reset(map_[key], zframe_data(data), zframe_size(data));
    else
    {
        zframe_t* frame = zframe_dup(data);
        map_.insert(DataMap::value_type(key, frame));
    }
}

zframe_t* Container::ReadData(string key)
{
    if ( map_.count(key) != 0 )
        return map_[key];
    else
        return NULL;
}
