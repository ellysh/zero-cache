#include <iostream>

#include <string.h>
#include <stdlib.h>
#include <assert.h>

#include "client.h"

using namespace std;
using namespace zero_cache;

static const string kKey1 = "key1";
static const string kData1 = "test data 1";

static const string kKey2 = "key2";
static char kData2[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

static const string kKey3 = "key3";

void InitData(Client& client)
{
    client.WriteData(kKey1, Package(kData1.c_str(), kData1.size()));
    client.WriteData(kKey2, Package(&kData2, sizeof(kData2)));
}

void CheckData(Client& client)
{
    Package result = client.ReadData(kKey1);
    assert( ! memcmp(result.GetData(), kData1.c_str(), kData1.size()) );
    result.FreeData();

    result = client.ReadData(kKey2);
    assert( ! memcmp(result.GetData(), kData2, sizeof(kData2)) );
    result.FreeData();

    result = client.ReadData(kKey3);
    assert( result.GetData() == NULL );
}

int main()
{
    Client client("get_test.log", "ipc:///var/run/zero-cache/0", kDealer);

    cout << "Start test..." << endl;

    InitData(client);

    CheckData(client);
}
