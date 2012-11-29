#include <iostream>

#include <czmq.h>

#include "client.h"
#include "speed_test.h"

using namespace std;
using namespace zero_cache;

static const string kKey1 = "key1";
static const string kData1 = "test data 1";

static const string kKey2 = "key2";
static const string kData2 = "test data 2";

static const string kKey3 = "key3";
static const string kData3 = "test data 3";


void InitData(Client& client)
{
    client.WriteData(kKey1, const_cast<char*>(kData1.c_str()), kData1.size());
    client.WriteData(kKey2, const_cast<char*>(kData2.c_str()), kData2.size());
    client.WriteData(kKey3, const_cast<char*>(kData3.c_str()), kData3.size());
}

void CheckData(Client& client)
{
    string result;

    result = static_cast<char*>(client.ReadData(kKey1));
    assert( result == kData1 );

    result = static_cast<char*>(client.ReadData(kKey2));
    assert( result == kData2 );

    result = static_cast<char*>(client.ReadData(kKey3));
    assert( result == kData3 );
}

int main()
{
    Client client;

    cout << "Start test..." << endl;

    InitData(client);

    CheckData(client);
}
