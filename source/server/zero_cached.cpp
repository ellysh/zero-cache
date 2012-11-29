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
    Reactor reactor;

    reactor.Start();

    WaitInput();

    return 0;
}
