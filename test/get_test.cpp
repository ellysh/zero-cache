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
    Package package;
    package.offset = 0;
    package.pointer = malloc(kData1.size());
    memcpy(package.pointer, kData1.c_str(), kData1.size());
    package.size = kData1.size();

    client.WriteData(kKey1, package);
    free(package.pointer);

    package.offset = sizeof(size_t) + kData1.size();
    package.pointer = malloc(sizeof(kData2));
    memcpy(package.pointer, &kData2, sizeof(kData2));
    package.size = sizeof(kData2);

    client.WriteData(kKey2, package);
    free(package.pointer);
}

void CheckData(Client& client)
{
    Package result = client.ReadData(kKey1);
    assert( ! memcmp(result.pointer, kData1.c_str(), kData1.size()) );
    free(result.pointer);

    result = client.ReadData(kKey2);
    assert( ! memcmp(result.pointer, kData2, sizeof(kData2)) );
    free(result.pointer);

    result = client.ReadData(kKey3);
    assert( result.pointer == NULL );
}

int main()
{
    Client client("get_test.log");

    cout << "Start test..." << endl;

    InitData(client);

    CheckData(client);
}
