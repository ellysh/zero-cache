#include <iostream>
#include <vector>

#include <string.h>
#include <stdlib.h>
#include <assert.h>

#include "client.h"

using namespace std;
using namespace zero_cache;

static const string kKey1 = "key 1";
static const string kKey2 = "key 2";

static const string kData = "test data 1";

void InitData(Client& client)
{
    client.WriteData(kKey1, Package(kData.c_str(), kData.size()));
    client.WriteData(kKey2, Package(kData.c_str(), kData.size()));
}

vector<string> ParseKeys(string& keys)
{
    vector<string> result;

    string tmp;
    for (int i = 0; i < keys.size(); i++)
    {
        if ( keys[i] != ';' )
            tmp += keys[i];
        else
        {
            result.push_back(tmp);
            tmp.clear();
        }
    }

    return result;
}

void CheckKeys(Client& client)
{
    string keys = client.GetKeys();

    vector<string> result = ParseKeys(keys);

    assert( result.size() == 2 );
    assert( result[0] == kKey1 );
    assert( result[1] == kKey2 );
}

int main()
{
    Client client("key_test.log", "ipc:///var/run/zero-cache/0", kDealer);

    cout << "Start test..." << endl;

    client.GetKeys();

    InitData(client);

    CheckKeys(client);
}
