#include "debug_client.h"

#include <assert.h>

#include "debug.h"

using namespace std;
using namespace zero_cache;

DebugClient::DebugClient(string log_file)
{
    debug_ = new Debug(log_file);
    assert(debug_ != NULL);
}

DebugClient::~DebugClient()
{
    delete debug_;
}
