#include "client.h"

#include <fcntl.h>

#include "speaker.h"
#include "zero_cache.h"

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

void Client::WriteData(const string& key, const Package package) const
{
    /* FIXME: Implement this method */
}

Package Client::ReadData(const string& key)
{
    /* FIXME: Implement this method */
}

string Client::GetKeys()
{
    /* FIXME: Implement this method */
}
