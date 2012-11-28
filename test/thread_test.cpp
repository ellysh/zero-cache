#include <iostream>
#include <boost/lexical_cast.hpp>

#include <assert.h>
#include <czmq.h>

#include "container.h"
#include "speed_test.h"

using namespace std;
using namespace zero_cache;

static string gKey = "0";

void IncKey()
{
    int key = boost::lexical_cast<int>(gKey);
    key++;
    gKey = boost::lexical_cast<string>(key);
}

void* WriteLoop(void* args)
{
    Container* container = static_cast<Container*>(args);

    IncKey();

    while (true)
    {
        PRE_TIME_MEASURE("WriteData")
        container->WriteData(gKey, 100);
        POST_TIME_MEASURE
    }
}

void StartWriteThread(void* container)
{
    zthread_new(WriteLoop, container);
}

void* ReadLoop(void* args)
{
    Container* container = static_cast<Container*>(args);

    while (true)
    {
        PRE_TIME_MEASURE("WriteData")
        container->ReadData("1");
        POST_TIME_MEASURE
    }
}

void StartReadThread(void* container)
{
    zthread_new(ReadLoop, container);
}

int main()
{
    Container container;

    cout << "Start test..." << endl;

    StartWriteThread(&container);
    StartWriteThread(&container);
    StartWriteThread(&container);
    StartWriteThread(&container);

    //StartReadThread(&container);

    usleep(10 * 1000 * 1000);
}
