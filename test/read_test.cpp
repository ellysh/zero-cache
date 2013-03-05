#include <iostream>

#include <stdlib.h>
#include <assert.h>

#include "typed_client.h"
#include "thread.h"

using namespace std;
using namespace zero_cache;

void* WriteReadLoop(void* args)
{
    const char* log_file = static_cast<char*>(args);
    TypedClient client(log_file);

    char* endptr;
    size_t index = strtoul(log_file, &endptr, 10);
    long data = index;
    long result;

    while (true)
    {
        client.WriteLong(index, data);
        usleep(1000);

        result = client.ReadLong(index);
        assert( result == data );
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
