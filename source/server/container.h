#ifndef CONTAINER_H
#define CONTAINER_H

#include <string>
#include <map>

#include <boost/thread/mutex.hpp>

namespace zero_cache
{

class Container
{
private:
    typedef std::map<std::string, int> Data;

public:
    void WriteData(std::string key, int data);
    int ReadData(std::string key);

protected:
    Data data_;
    boost::mutex mutex_;
};

}

#endif
