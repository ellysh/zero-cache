#include <iostream>

#include <czmq.h>

#include "registrar_client.h"
#include "speed_test.h"

using namespace std;
using namespace zero_cache;

static char kData[1000];

void* WriteLoop(void* args)
{
    const char* data = static_cast<char*>(args);
    RegistrarClient client(data, "ipc:///tmp/0", kDealer);

    while (true)
    {
        PRE_TIME_MEASURE(data)
        client.WriteData(data, &kData, sizeof(kData));
        POST_TIME_MEASURE
        usleep(100);
    }
}

void StartWriteThread(const char* args)
{
    zthread_new(WriteLoop, const_cast<char*>(args));
}

void WaitInput()
{
    char key;
    cin >> key;
}

int main()
{
    cout << "Start test..." << endl;

    StartWriteThread("1");
    StartWriteThread("2");
    StartWriteThread("3");
    StartWriteThread("4");

    WaitInput();
}
