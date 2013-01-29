#include <iostream>

#include <string.h>
#include <stdlib.h>
#include <assert.h>

#include "registrar_client.h"

using namespace std;
using namespace zero_cache;

static const string kKey1 = "key 1";
static const string kKey2 = "key 2";

static const string kData = "test data 1";

void InitData(RegistrarClient& client)
{
    client.WriteData(kKey1, const_cast<char*>(kData.c_str()), kData.size());
    client.WriteData(kKey2, const_cast<char*>(kData.c_str()), kData.size());
}

void CheckKeys(RegistrarClient& client)
{
    KeyArray keys = client.GetKeys();

    string result(keys.begin(), keys.end());
    cout << "CheckKeys() - keys = " << result << endl;
}

int main()
{
    RegistrarClient client("key_test.log", "ipc:///var/run/zero-cache/0", kDealer);

    cout << "Start test..." << endl;

    InitData(client);

    CheckKeys(client);
}
