#include <iostream>

#include "registrar_client.h"
#include "speed_test.h"

using namespace std;
using namespace zero_cache;

static const string kKey1 = "key1";
static const string kData1 = "test data 1";

static const string kKey2 = "key2";
static char kData2[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

void InitData(RegistrarClient& client)
{
    client.WriteData(kKey1, const_cast<char*>(kData1.c_str()), kData1.size());
    client.WriteData(kKey2, &kData2, sizeof(kData2));
}

void CheckData(RegistrarClient& client)
{
    char* result;
    result = static_cast<char*>(client.ReadData(kKey1));
    assert( ! memcmp(result, kData1.c_str(), kData1.size()) );
    free(result);

    result = static_cast<char*>(client.ReadData(kKey2));
    assert( ! memcmp(result, kData2, sizeof(kData2)) );
    free(result);
}

int main()
{
    RegistrarClient client("get_test.log", "ipc:///var/run/zero-cache/0", kDealer);

    cout << "Start test..." << endl;

    InitData(client);

    CheckData(client);
}
