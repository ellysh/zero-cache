#include <iostream>

#include <string.h>
#include <stdlib.h>
#include <assert.h>

#include "client.h"

using namespace std;
using namespace zero_cache;

static const size_t kOffset1 = 0;
static const long kData1 = 1024;

void InitData(Client& client)
{
    client.WriteLong(kOffset1, kData1);
}

void CheckData(Client& client)
{
    long result = client.ReadLong(kOffset1);
    assert( result == kData1 );
}

int main()
{
    Client client("get_test.log");

    cout << "Start test..." << endl;

    InitData(client);

    CheckData(client);
}
