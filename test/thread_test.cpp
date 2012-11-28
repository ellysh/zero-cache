#include <iostream>
#include <assert.h>
#include <czmq.h>

using namespace std;
//using namespace zero_cache;

void* SendLoop(void* object)
{
    /* FIXME: Implement this method */
#if 0
    StateClient client(kMySql, "simunit", "localhost", "simunit", "simunit");
    ObjectState state = kDisable;

    while (true)
    {
        cout << "object = " << static_cast<char*>(object) << endl;
        client.SetState(string(static_cast<char*>(object)), state);
        WaitOperation();
    }
#endif
}

void StartSendThread(char* object)
{
    zthread_new(SendLoop, object);
}

int main()
{
    cout << "Start test..." << endl;

    StartSendThread("test_bus1");
    StartSendThread("test_bus2");
    StartSendThread("test_codec1");
    StartSendThread("test_codec2");

    usleep(10 * 1000 * 1000);
}
