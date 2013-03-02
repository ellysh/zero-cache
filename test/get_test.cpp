#include <iostream>

#include <string.h>
#include <stdlib.h>
#include <assert.h>

#include "client.h"

using namespace std;
using namespace zero_cache;

static const size_t kIndex1 = 0;
static const long kData1 = 1024;

static const size_t kIndex2 = 1;
static const double kData2 = 17.255;

void InitData(Client& client)
{
    client.WriteLong(kIndex1, kData1);
    client.WriteDouble(kIndex2, kData2);
}

void CheckData(Client& client)
{
    long result_l = client.ReadLong(kIndex1);
    assert( result_l == kData1 );

    double result_d = client.ReadDouble(kIndex2);
    assert( result_d == kData2 );
}

int main()
{
    Client client("get_test.log");

    cout << "Start test..." << endl;

    InitData(client);

    CheckData(client);
}
