#include "untyped_client.h"

#include <fcntl.h>
#include <sys/ioctl.h>
#include <string.h>

#define PRINTF Log
#include "speed_test.h"
#include "speaker.h"

#include "zero_cache.h"

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

void UntypedClient::WriteValue(const size_t index, const void* value, const size_t size)
{
    PRE_TIME_MEASURE("UntypedClient::WriteValue() ")

    Package package;
    package.index = index;
    package.size = size;
    memcpy(&package.data, value, POINTER_SIZE);

    int rc = ioctl(dev_file_, IOCTL_WRITE_VALUE, &package);

    if ( rc != 0 )
        Speaker::Instance()->PrintError(kWriteError);

    POST_TIME_MEASURE
}

void UntypedClient::ReadValue(const size_t index, void* result, const size_t size) const
{
    PRE_TIME_MEASURE("UntypedClient::ReadValue() ")

    Package package;
    package.index = index;
    package.size = size;

    int rc = ioctl(dev_file_, IOCTL_READ_VALUE, &package);

    if ( rc != 0 )
        Speaker::Instance()->PrintError(kReadError);

    memcpy(result, &package.data, size);

    POST_TIME_MEASURE
}

void UntypedClient::WriteArray(const size_t index, const void* array, const size_t size)
{
    PRE_TIME_MEASURE("UntypedClient::WriteArray() ")

    Package package;
    package.index = index;
    package.size = size;

    unsigned long address = reinterpret_cast<unsigned long>(array);
    memcpy(&package.data, &address, POINTER_SIZE);

    int rc = ioctl(dev_file_, IOCTL_WRITE_ARRAY, &package);

    if ( rc != 0 )
        Speaker::Instance()->PrintError(kWriteError);

    POST_TIME_MEASURE
}

void UntypedClient::ReadArray(const size_t index, void* result, const size_t size) const
{
    /* FIXME: This function is the same as WriteArray() */
    PRE_TIME_MEASURE("UntypedClient::ReadArray() ")

    Package package;
    package.index = index;
    package.size = size;

    unsigned long address = reinterpret_cast<unsigned long>(result);
    memcpy(&package.data, &address, POINTER_SIZE);

    int rc = ioctl(dev_file_, IOCTL_READ_ARRAY, &package);

    if ( rc != 0 )
        Speaker::Instance()->PrintError(kReadError);

    POST_TIME_MEASURE
}

void UntypedClient::ClearCache()
{
    PRE_TIME_MEASURE("UntypedClient::ClearCache() ")

    Package package;
    package.index = 0;

    int rc = ioctl(dev_file_, IOCTL_CLEAR_CACHE, &package);

    if ( rc != 0 )
        Speaker::Instance()->PrintError(kClearError);

    POST_TIME_MEASURE
}
