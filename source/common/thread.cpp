#include "thread.h"

#include <pthread.h>

using namespace zero_cache;

void zero_cache::CreateThread(thread_fn* func, void* data)
{
    pthread_t thread;

    pthread_create(&thread, NULL, func, data);
}
