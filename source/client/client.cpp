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

void Client::WriteLong(const size_t offset, const long value)
{
    /* FIXME: Implement this method */
    int rc = ioctl(dev_file_, IOCTL_SET_MSG, 1024);
}

void Client::WriteDouble(const size_t offset, const double value)
{
    /* FIXME: Implement this method */
}

long Client::ReadLong(const size_t offset) const
{
    /* FIXME: Implement this method */
    long data;
    int rc = ioctl(dev_file_, IOCTL_GET_MSG, &data);

    return data;
}

double Client::ReadDouble(const size_t offset) const
{
    /* FIXME: Implement this method */
}
