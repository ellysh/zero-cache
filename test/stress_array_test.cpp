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
    UntypedClient client("");
    client.ClearCache();

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
