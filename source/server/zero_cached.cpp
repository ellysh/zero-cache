#include "reactor.h"

#include <iostream>

using namespace std;
using namespace zero_cache;

void WaitInput()
{
    char key;

    cin >> key;
}

int main()
{
    Reactor reactor("zero_cached.log");

    reactor.Start();

    WaitInput();

    return 0;
}
