#include <iostream>

#include <string.h>
#include <stdlib.h>
#include <assert.h>

#include "registrar_client.h"
#include "thread.h"

using namespace std;
using namespace zero_cache;

void* WriteOperation(void* args)
{
    char* key = static_cast<char*>(args);
    RegistrarClient client("write.log", "ipc:///var/run/zero-cache/0", kDealer);

    client.WriteData(key, Package(key, sizeof(key)));
}

void* ReadOperation(void* args)
{
    const char* key = static_cast<char*>(args);
    RegistrarClient client("read.log", "ipc:///var/run/zero-cache/0", kDealer);

    Package result = client.ReadData(key);
    assert( ! memcmp(result.GetData(), key, sizeof(key)) );
    free(result.GetData());

    usleep(2 * 1000 * 1000);
    exit(0);
}

void StartWriteThread(const char* args)
{
    CreateThread(WriteOperation, const_cast<char*>(args));
}

void StartReadThread(const char* args)
{
    CreateThread(ReadOperation, const_cast<char*>(args));
}

int main()
{
    cout << "Start test..." << endl;

    StartWriteThread("1");
    StartWriteThread("2");
    StartWriteThread("3");
    StartWriteThread("4");

    usleep(3 * 1000 * 1000);

    StartReadThread("1");
    StartReadThread("2");
    StartReadThread("3");
    StartReadThread("4");

    while (true)
        usleep(1000);
}
