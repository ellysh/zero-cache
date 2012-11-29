#include "reactor.h"

using namespace zero_cache;

int main()
{
    Reactor reactor;

    reactor.Start();

    while (true)
        usleep(1000);

    return 0;
}
