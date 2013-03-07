#define TRUE    1
#define FALSE   0

void set_pool_index(const size_t cache_index, const size_t size)
{
    memcpy(&gCache[cache_index], &gIndexPool, sizeof(gIndexPool));
    gIndexPool = gIndexPool + size;
}

size_t get_pool_index(const size_t cache_index)
{
    size_t result;
    memcpy(&result, &gCache[cache_index], sizeof(result));

    return result;
}

int is_pool_limit(const size_t index, const size_t size)
{
    if ( CACHE_SIZE < (index + size) )
    {
        printk(KERN_INFO "zero_cache: limit of the memory pool have been reached");
        return TRUE;
    }
    else
        return FALSE;
}

void* data_to_pointer(const unsigned char const * data)
{
    void* result;
    result = (void*)(*(unsigned long*)data);

    return result;
}

int is_data_empty(const size_t index)
{
    unsigned long data;

    memcpy(&data, gCache[index], sizeof(data));

    if ( data == 0 )
        return TRUE;
    else
        return FALSE;
}

void clear_cache(void)
{
    memset(&gCache, 0x00, sizeof(gCache));
    memset(&gPool, 0x00, sizeof(gPool));
    gIndexPool = 0;
}
