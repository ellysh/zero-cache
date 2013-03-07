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
        cout << "error: can't OPEN device file" << endl;
    else if ( error == kWriteError )
        cout << "error: ioctl with WRITE command failed" << endl;
    else if ( error == kReadError )
        cout << "error: ioctl with READ command failed" << endl;
    else if ( error == kClearError )
        cout << "error: ioctl with CLEAR command failed" << endl;

    exit(1);
}
