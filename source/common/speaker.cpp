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
    else if ( error == kSetCommandError )
        cout << "error: ioctl with IOCTL_SET_MSG command failed" << endl;
    else if ( error == kGetCommandError )
        cout << "error: ioctl with IOCTL_GET_MSG command failed" << endl;

    exit(1);
}
