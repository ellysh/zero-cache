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

void Speaker::PrintError(const ErrorType error) const
{
    if ( error == kOpenDevFileError )
        cout << "error: can't open device file" << endl;

    exit(1);
}
