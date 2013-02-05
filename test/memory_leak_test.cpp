#include <iostream>

#include "registrar_client.h"
#include "thread.h"

using namespace std;
using namespace zero_cache;

static char kData[1000];

void* WriteLoop(void* args)
{
    const char* key = static_cast<char*>(args);
    RegistrarClient client(key, "ipc:///var/run/zero-cache/0", kDealer);

    while (true)
    {
        client.WriteData(key, Package(&kData, sizeof(kData)));
        usleep(100);
    }
}

void StartWriteThread(const char* args)
{
    CreateThread(WriteLoop, const_cast<char*>(args));
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
