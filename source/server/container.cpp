#include "container.h"

#include <algorithm>

using namespace std;
using namespace zero_cache;

static void RemoveFrame(Container::DataMap::value_type frame_pair)
{
    zmq_msg_close(&frame_pair.second);
}

Container::~Container()
{
    for_each(map_.begin(), map_.end(),
             RemoveFrame);
}

void Container::WriteData(string& key, zmq_msg_t& data)
{
    if ( map_.count(key) != 0 )
        zmq_msg_copy(&map_[key], &data);
    else
    {
        zmq_msg_t msg;
        zmq_msg_copy(&msg, &data);
        map_.insert(DataMap::value_type(key, msg));
    }
}

zmq_msg_t* Container::ReadData(string& key)
{
    if ( map_.count(key) != 0 )
        return &map_[key];
    else
        return NULL;
}
