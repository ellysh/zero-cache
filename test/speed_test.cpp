#include <iostream>

#include <czmq.h>

#include "registrar_client.h"

using namespace std;
using namespace zero_cache;

void* WriteLoop(void* args)
{
    const char* key = static_cast<char*>(args);
    RegistrarClient client(key, Connection("ipc:///var/run/zero-cache/0"), kDealer);

    while (true)
    {
        client.WriteData(key, args, 1);
        usleep(500);
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
