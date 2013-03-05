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

void UntypedClient::WriteData(const size_t index, const void* value)
{
    PRE_TIME_MEASURE("RegistrarUntypedClient::WriteData() ")

    Package package;
    package.index = index;
    package.size = POINTER_SIZE;
    memcpy(&package.data, value, POINTER_SIZE);

    int rc = ioctl(dev_file_, IOCTL_SET_MSG, &package);

    if ( rc != 0 )
        Speaker::Instance()->PrintError(kSetCommandError);

    POST_TIME_MEASURE
}

void UntypedClient::ReadData(const size_t index, void* result) const
{
    PRE_TIME_MEASURE("RegistrarUntypedClient::ReadData() ")

    Package package;
    package.index = index;
    package.size = POINTER_SIZE;

    int rc = ioctl(dev_file_, IOCTL_GET_MSG, &package);

    if ( rc != 0 )
        Speaker::Instance()->PrintError(kGetCommandError);

    memcpy(result, &package.data, POINTER_SIZE);

    POST_TIME_MEASURE
}
