#ifndef ZERO_CACHE_H
#define ZERO_CACHE_H

#include <linux/ioctl.h>

#define MAJOR_NUM 100

#define IOCTL_SET_MSG _IOR(MAJOR_NUM, 0, void *)

#define IOCTL_GET_MSG _IOR(MAJOR_NUM, 1, void *)

#define DEVICE_FILE_NAME "/dev/zero_cache"

typedef unsigned long cell_t;

struct Package
{
    size_t offset;
    cell_t data;
};

#endif

