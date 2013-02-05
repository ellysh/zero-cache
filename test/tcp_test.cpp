#include <iostream>

#include <string.h>
#include <stdlib.h>
#include <assert.h>

#include "registrar_client.h"

using namespace std;
using namespace zero_cache;

static const string kKey = "key2";
static char kData[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

void InitData(RegistrarClient& client)
{
    client.WriteData(kKey, Package(&kData, sizeof(kData)));
}

void CheckData(RegistrarClient& client)
{
    Package result = client.ReadData(kKey);
    assert( ! memcmp(result.GetData(), kData, sizeof(kData)) );
    result.FreeData();
}

int main()
{
    RegistrarClient client("tcp_test.log", "tcp://localhost:5570", kDealer);
    client.SetHost("localhost:");

    cout << "Start test..." << endl;

    InitData(client);

    CheckData(client);
}
