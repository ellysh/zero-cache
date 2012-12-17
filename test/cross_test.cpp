#include <iostream>

#include <czmq.h>

#include "registrar_client.h"

using namespace std;
using namespace zero_cache;

void* WriteOperation(void* args)
{
    char* key = static_cast<char*>(args);
    RegistrarClient client("write.log", Connection("ipc:///var/run/zero-cache/0"), kDealer);

    client.WriteData(key, key, sizeof(key));
}

void* ReadOperation(void* args)
{
    usleep(3 * 1000 * 1000);
    const char* key = static_cast<char*>(args);
    RegistrarClient client("read.log", Connection("ipc:///var/run/zero-cache/0"), kDealer);

    char* result;
    result = static_cast<char*>(client.ReadData(key));
    assert( ! memcmp(result, key, sizeof(key)) );
    free(result);

    usleep(2 * 1000 * 1000);
    exit(0);
}

void StartWriteThread(const char* args)
{
    zthread_new(WriteOperation, const_cast<char*>(args));
}

void StartReadThread(const char* args)
{
    zthread_new(ReadOperation, const_cast<char*>(args));
}

int main()
{
    cout << "Start test..." << endl;

    StartWriteThread("1");
    StartWriteThread("2");
    StartWriteThread("3");
    StartWriteThread("4");

    StartReadThread("1");
    StartReadThread("2");
    StartReadThread("3");
    StartReadThread("4");

    while (true)
        usleep(1000);
}
