#ifndef THREAD_H
#define THREAD_H

namespace zero_cache
{

typedef void* (thread_fn) (void *data);

void CreateThread(thread_fn* function, void* data);

}

#endif
