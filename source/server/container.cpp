#include "container.h"

#include <algorithm>

using namespace std;
using namespace zero_cache;

static void RemoveMsg(Container::DataMap::value_type msg_pair)
{
    zmq_msg_close(&msg_pair.second);
}

Container::~Container()
{
    for_each(map_.begin(), map_.end(),
             RemoveMsg);
}

void Container::WriteData(string& key, zmq_msg_t& data)
{
    if ( map_.count(key) != 0 )
        zmq_msg_copy(&map_[key], &data);
    else
    {
        size_t size = zmq_msg_size(&data);

        zmq_msg_t msg;
        zmq_msg_init_size(&msg, size);
        memcpy(zmq_msg_data(&msg), zmq_msg_data(&data), size);

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
