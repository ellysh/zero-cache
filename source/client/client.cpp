#include "client.h"

#include <fcntl.h>
#include <sys/ioctl.h>
#include <string.h>

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
    memcpy(&package.data, &value, PACKAGE_DATA_SIZE);

    int rc = ioctl(dev_file_, IOCTL_SET_MSG, &package);

    if ( rc != 0 )
        Speaker::Instance()->PrintError(kSetCommandError);
}

void Client::WriteDouble(const size_t index, const double value)
{
    Package package;
    package.index = index;
    memcpy(&package.data, &value, PACKAGE_DATA_SIZE);

    int rc = ioctl(dev_file_, IOCTL_SET_MSG, &package);

    if ( rc != 0 )
        Speaker::Instance()->PrintError(kSetCommandError);
}

long Client::ReadLong(const size_t index) const
{
    Package package;
    package.index = index;

    int rc = ioctl(dev_file_, IOCTL_GET_MSG, &package);

    if ( rc != 0 )
        Speaker::Instance()->PrintError(kGetCommandError);

    long result;
    memcpy(&result, &package.data, PACKAGE_DATA_SIZE);

    return result;
}

double Client::ReadDouble(const size_t index) const
{
    Package package;
    package.index = index;

    int rc = ioctl(dev_file_, IOCTL_GET_MSG, &package);

    if ( rc != 0 )
        Speaker::Instance()->PrintError(kGetCommandError);

    double result;
    memcpy(&result, &package.data, PACKAGE_DATA_SIZE);

    return result;
}
