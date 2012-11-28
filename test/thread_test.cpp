#include <iostream>
#include <assert.h>
#include <czmq.h>

#include "container.h"
#include "speed_test.h"

using namespace std;
using namespace zero_cache;

void* SendLoop(void* args)
{
    Container* container = static_cast<Container*>(args);

    char id[10];
    sprintf(id, "%p", args);

    while (true)
    {
        PRE_TIME_MEASURE("WriteData")
        container->WriteData(id, 100);
        POST_TIME_MEASURE
    }
}

void StartSendThread(void* container)
{
    zthread_new(SendLoop, container);
}

int main()
{
    Container container;

    cout << "Start test..." << endl;

    StartSendThread(&container);
    StartSendThread(&container);
    StartSendThread(&container);
    StartSendThread(&container);

    usleep(10 * 1000 * 1000);
}
