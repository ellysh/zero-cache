#include <iostream>

#include "registrar_client.h"

using namespace std;
using namespace zero_cache;

static const string kKey = "key2";
static char kData[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

void InitData(RegistrarClient& client)
{
    client.WriteData(kKey, &kData, sizeof(kData));
}

void CheckData(RegistrarClient& client)
{
    char* result;
    result = static_cast<char*>(client.ReadData(kKey));
    assert( ! memcmp(result, kData, sizeof(kData)) );
    free(result);
}

int main()
{
    RegistrarClient client("tcp_test.log", "tcp://localhost:5570", kDealer);
    client.SetHost("localhost:");

    cout << "Start test..." << endl;

    InitData(client);

    CheckData(client);
}
