#ifndef ZERO_CACHE_H
#define ZERO_CACHE_H

#include <linux/ioctl.h>

#define MAJOR_NUM 100

#define IOCTL_WRITE_VALUE _IOW(MAJOR_NUM, 0, void *)
#define IOCTL_READ_VALUE _IOR(MAJOR_NUM, 1, void *)
#define IOCTL_WRITE_ARRAY _IOW(MAJOR_NUM, 2, void *)
#define IOCTL_READ_ARRAY _IOR(MAJOR_NUM, 3, void *)

#define DEVICE_FILE_NAME "/dev/zero_cache"

/* FIXME: Use the universal way to calculate pointer size */
#define POINTER_SIZE   8

struct Package
{
    size_t index;
    size_t size;
    unsigned char data[POINTER_SIZE];
};

#endif

