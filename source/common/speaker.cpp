#include "speaker.h"

#include <iostream>

#include <stdlib.h>

using namespace std;
using namespace zero_cache;

Speaker* Speaker::instance_ = NULL;

Speaker* Speaker::Instance()
{
    if (instance_ == NULL)
        instance_ = new Speaker();

    return instance_;
}

void Speaker::PrintError(ErrorType error)
{
    if ( error == kSocketTypeError )
        cout << "error: undefined connection type" << endl;
    else if ( error == kSocketNameError )
        cout << "error: specified socked file or tcp port is not in the number format" << endl;

    exit(1);
}
