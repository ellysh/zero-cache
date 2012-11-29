#include <iostream>
#include <boost/lexical_cast.hpp>

#include <assert.h>
#include <czmq.h>

#include "reactor.h"
#include "client.h"
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
    Client client;

    IncKey();
    string data = gKey;

    while (true)
    {
        PRE_TIME_MEASURE(data)
        client.WriteData(data);
        POST_TIME_MEASURE
        usleep(100);
    }
}

void StartWriteThread()
{
    zthread_new(WriteLoop, NULL);
}

int main()
{
    Reactor reactor;

    reactor.Start();

    cout << "Start test..." << endl;

    StartWriteThread();
    StartWriteThread();
    StartWriteThread();
    StartWriteThread();

    usleep(10 * 1000 * 1000);
}
