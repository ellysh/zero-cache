#include <iostream>

#include <string.h>
#include <stdlib.h>
#include <assert.h>

#include "untyped_client.h"
#include "thread.h"

using namespace std;
using namespace zero_cache;

void* WriteReadLoop(void* args)
{
    const char* log_file = static_cast<char*>(args);
    UntypedClient client(log_file);

    char* endptr;
    size_t index = strtoul(log_file, &endptr, 10);
    char result[10];

    while (true)
    {
        client.WriteArray(index, log_file, strlen(log_file));
        usleep(1000);

        client.ReadArray(index, result, strlen(log_file));
        assert( ! memcmp(result, log_file, strlen(log_file)) );
        usleep(1000);
    }
}

void StartWriteThread(const char* args)
{
    CreateThread(WriteReadLoop, const_cast<char*>(args));
}

void WaitInput()
{
    char key;
    cin >> key;
}

int main()
{
    cout << "Start test..." << endl;

    StartWriteThread("31");
    StartWriteThread("32");
    StartWriteThread("33");
    StartWriteThread("34");
    StartWriteThread("35");
    StartWriteThread("36");
    StartWriteThread("37");
    StartWriteThread("38");
    StartWriteThread("39");
    StartWriteThread("40");
    StartWriteThread("41");
    StartWriteThread("42");
    StartWriteThread("43");
    StartWriteThread("44");
    StartWriteThread("45");
    StartWriteThread("46");

    WaitInput();
}
