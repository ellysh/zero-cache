#include "client.h"

#include <fcntl.h>
#include <sys/ioctl.h>

#include "speaker.h"

using namespace std;
using namespace zero_cache;

Client::Client(const char* log_file) : Debug(log_file)
{
    dev_file_ = open(DEVICE_FILE_NAME, 0);

    if ( dev_file_ < 0 )
        Speaker::Instance()->PrintError(kOpenDevFileError);
}

Client::~Client()
{
    close(dev_file_);
}

void Client::WriteLong(const size_t index, const long value)
{
    Package package;
    package.index = index;
    package.data = value;

    int rc = ioctl(dev_file_, IOCTL_SET_MSG, &package);

    if ( rc != 0 )
        Speaker::Instance()->PrintError(kSetCommandError);
}

void Client::WriteDouble(const size_t index, const double value)
{
    /* FIXME: Implement this method */
}

long Client::ReadLong(const size_t index) const
{
    Package package;
    package.index = index;

    int rc = ioctl(dev_file_, IOCTL_GET_MSG, &package);

    if ( rc != 0 )
        Speaker::Instance()->PrintError(kGetCommandError);

    return package.data;
}

double Client::ReadDouble(const size_t index) const
{
    /* FIXME: Implement this method */
}
