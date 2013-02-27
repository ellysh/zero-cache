#include <iostream>

#include <string.h>
#include <stdlib.h>
#include <assert.h>

#include "client.h"
#include "thread.h"

using namespace std;
using namespace zero_cache;

void* WriteLoop(void* args)
{
    const char* key = static_cast<char*>(args);
    Client client(key, "ipc:///var/run/zero-cache/0", kDealer);

    while (true)
    {
        client.WriteData(key, Package(args, sizeof(args)));
        usleep(1000);

        Package result = client.ReadData(key);
        assert( ! memcmp(result.GetData(), key, result.GetSize()) );
        result.FreeData();
        usleep(1000);
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
