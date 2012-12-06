#include <iostream>

#include <czmq.h>

#include "registrar_client.h"
#include "speed_test.h"

using namespace std;
using namespace zero_cache;

void* WriteLoop(void* args)
{
    const char* data = static_cast<char*>(args);
    RegistrarClient client(data, "ipc:///tmp/0");

    while (true)
    {
        PRE_TIME_MEASURE(data)
        client.WriteData(data, args, 1);
        POST_TIME_MEASURE
        usleep(10);
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
    StartWriteThread("5");
    StartWriteThread("6");
    StartWriteThread("7");
    StartWriteThread("8");
    StartWriteThread("9");
    StartWriteThread("10");
    StartWriteThread("11");
    StartWriteThread("12");
    StartWriteThread("13");
    StartWriteThread("14");
    StartWriteThread("15");
    StartWriteThread("16");

    WaitInput();
}
