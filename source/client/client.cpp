#include "client.h"

#include <fcntl.h>
#include <sys/ioctl.h>
#include <string.h>

#define PRINTF Log
#include "speed_test.h"
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
    WriteData(index, &value);
}

void Client::WriteDouble(const size_t index, const double value)
{
    WriteData(index, &value);
}

void Client::WriteData(const size_t index, const void* value)
{
    PRE_TIME_MEASURE("RegistrarClient::WriteData() ")

    Package package;
    package.index = index;
    memcpy(&package.data, value, PACKAGE_DATA_SIZE);

    int rc = ioctl(dev_file_, IOCTL_SET_MSG, &package);

    if ( rc != 0 )
        Speaker::Instance()->PrintError(kSetCommandError);

    POST_TIME_MEASURE
}

long Client::ReadLong(const size_t index) const
{
    long result;
    ReadData(index, &result);

    return result;
}

double Client::ReadDouble(const size_t index) const
{
    double result;
    ReadData(index, &result);

    return result;
}

void Client::ReadData(const size_t index, void* result) const
{
    PRE_TIME_MEASURE("RegistrarClient::ReadData() ")

    Package package;
    package.index = index;

    int rc = ioctl(dev_file_, IOCTL_GET_MSG, &package);

    if ( rc != 0 )
        Speaker::Instance()->PrintError(kGetCommandError);

    memcpy(result, &package.data, PACKAGE_DATA_SIZE);

    POST_TIME_MEASURE
}
