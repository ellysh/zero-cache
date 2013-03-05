#include <iostream>

#include <string.h>
#include <assert.h>

#include "untyped_client.h"

using namespace std;
using namespace zero_cache;

static const size_t kIndex1 = 0;
static const string kData1 = "test data 1";

static const size_t kIndex2 = 1;
static const unsigned char kData2[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

void InitData(UntypedClient& client)
{
    client.WriteData(kIndex1, kData1.c_str(), kData1.size());
    client.WriteData(kIndex2, kData2, sizeof(kData2));
}

void CheckData(UntypedClient& client)
{
    char result_s[20];
    client.ReadData(kIndex1, result_s, kData1.size());
    assert( ! memcmp(result_s, kData1.c_str(), kData1.size()) );

    unsigned char result_a[20];
    client.ReadData(kIndex2, result_a, sizeof(kData2));
    assert( ! memcmp(result_a, kData2, sizeof(kData2) ) );
}

int main()
{
    UntypedClient client("array_test.log");

    cout << "Start test..." << endl;

    InitData(client);

    CheckData(client);
}
