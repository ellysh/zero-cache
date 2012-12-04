#include "reactor.h"

using namespace std;
using namespace zero_cache;

int main()
{
    Reactor reactor("zero_cached.log");

    reactor.Start();

    return 0;
}
