#include "untyped_client.h"

#include <fcntl.h>
#include <sys/ioctl.h>
#include <string.h>

#define PRINTF Log
#include "speed_test.h"
#include "speaker.h"

using namespace std;
using namespace zero_cache;

UntypedClient::UntypedClient(const char* log_file) : Debug(log_file)
{
    dev_file_ = open(DEVICE_FILE_NAME, 0);

    if ( dev_file_ < 0 )
        Speaker::Instance()->PrintError(kOpenDevFileError);
}

UntypedClient::~UntypedClient()
{
    close(dev_file_);
}

void UntypedClient::WriteData(const size_t index, const void* value, const size_t size)
{
    PRE_TIME_MEASURE("UntypedClient::WriteData() ")

    Package package;
    package.index = index;
    package.size = size;
    memcpy(&package.data, value, POINTER_SIZE);

    int rc = ioctl(dev_file_, IOCTL_SET_MSG, &package);

    if ( rc != 0 )
        Speaker::Instance()->PrintError(kSetCommandError);

    POST_TIME_MEASURE
}

void UntypedClient::ReadData(const size_t index, void* result, const size_t size) const
{
    PRE_TIME_MEASURE("UntypedClient::ReadData() ")

    Package package;
    package.index = index;
    package.size = size;

    int rc = ioctl(dev_file_, IOCTL_GET_MSG, &package);

    if ( rc != 0 )
        Speaker::Instance()->PrintError(kGetCommandError);

    memcpy(result, &package.data, size);

    POST_TIME_MEASURE
}
