#include <iostream>

#include <string.h>
#include <stdlib.h>
#include <assert.h>

#include "client_typed.h"

using namespace std;
using namespace zero_cache;

static string gKeyLong = "key1";
static long gDataLong = 1024;

static string gKeyDouble = "key2";
static double gDataDouble = 100.53;

static string gKeyString = "key3";
static string gDataString = "test data";

void InitData(ClientTyped& client)
{
    client.WriteLong(gKeyLong, gDataLong);
    client.WriteDouble(gKeyDouble, gDataDouble);
    client.WriteString(gKeyString, gDataString);
}

void CheckData(ClientTyped& client)
{
    assert( gDataLong == client.ReadLong(gKeyLong) );
    assert( gDataDouble == client.ReadDouble(gKeyDouble) );
    assert( gDataString == client.ReadString(gKeyString) );
}

int main()
{
    ClientTyped client("wrap_test.log", "ipc:///var/run/zero-cache/0", kDealer);

    cout << "Start test..." << endl;

    InitData(client);

    CheckData(client);
}
