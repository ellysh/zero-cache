#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/device.h>
#include <linux/cdev.h>
#include <linux/slab.h>
#include <asm/uaccess.h>

#include "zero_cache.h"

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Ilya Shpigor <petrsum@gmail.com>");
MODULE_DESCRIPTION("Kernel data cache module");

#define CLASS       "zero_cache_class"
#define DEVICE      "zero_cache"
#define CACHE_SIZE  100000

static struct Device
{
    dev_t number;
    struct cdev chrdev;
    struct class* class;
} gDevice;

DECLARE_RWSEM(gSem);

static unsigned char gCache[CACHE_SIZE][POINTER_SIZE];
static unsigned char gPool[CACHE_SIZE];
static size_t gIndexPool = 0;

#include "functions.c"

static long zc_ioctl(struct file *file, unsigned int command, unsigned long arg)
{
    struct Package* package;
    package = (struct Package*)arg;

    if ( (package->index) < 0 || (CACHE_SIZE < package->index) )
    {
        printk(KERN_INFO "zero_cache: array index %lu out of bounds %d\n", package->index, CACHE_SIZE);
        return -1;
    }

    switch (command)
    {
    case IOCTL_WRITE_VALUE:
        down_write(&gSem);
        copy_from_user(&gCache[package->index], &package->data, POINTER_SIZE);
        up_write(&gSem);
        break;

    case IOCTL_READ_VALUE:
        down_read(&gSem);
        copy_to_user(&package->data, &gCache[package->index], POINTER_SIZE);
        up_read(&gSem);
        break;

    case IOCTL_WRITE_ARRAY:
        down_write(&gSem);
        if ( is_pool_limit(gIndexPool, package->size) )
        {
            up_write(&gSem);
            return -1;
        }

        if ( is_data_empty(package->index) )
            set_pool_index(package->index, package->size);

        copy_from_user(&gPool[get_pool_index(package->index)],
                       data_to_pointer(&package->data[0]), package->size);
        up_write(&gSem);
        break;

    case IOCTL_READ_ARRAY:
        if ( is_pool_limit(get_pool_index(package->index), package->size) )
            return -1;

        down_read(&gSem);
        copy_to_user(data_to_pointer(&package->data[0]),
                     &gPool[get_pool_index(package->index)], package->size);
        up_read(&gSem);
        break;

    case IOCTL_CLEAR_CACHE:
        down_write(&gSem);
        clear_cache();
        up_write(&gSem);
        break;
    }

    return 0;
}

int register_device(struct file_operations* fops)
{
    if ( alloc_chrdev_region(&gDevice.number, 0, 1, DEVICE ) < 0 )
        return -1;

    gDevice.class = class_create(THIS_MODULE, CLASS);
    if ( gDevice.class == NULL )
    {
        unregister_chrdev_region(gDevice.number, 1);
        return -1;
    }

    if ( device_create(gDevice.class, NULL, gDevice.number, NULL, DEVICE) == NULL )
    {
        class_destroy(gDevice.class);
        unregister_chrdev_region(gDevice.number, 1);
        return -1;
    }

    cdev_init(&gDevice.chrdev, fops);
    if ( cdev_add(&gDevice.chrdev, gDevice.number, 1) == -1 )
    {
        device_destroy(gDevice.class, gDevice.number);
        class_destroy(gDevice.class);
        unregister_chrdev_region(gDevice.number, 1);
        return -1;
    }
    return 0;
}

static struct file_operations zc_fops =
{
    .owner   = THIS_MODULE,
    .unlocked_ioctl = zc_ioctl
};

static int __init zc_init(void)
{
    int rc;
    rc = register_device(&zc_fops);

    clear_cache();

    printk(KERN_INFO "zero_cache: init rc=%d\n", rc);
    return rc;
}

static void __exit zc_exit(void)
{
    cdev_del(&gDevice.chrdev);
    device_destroy(gDevice.class, gDevice.number);
    class_destroy(gDevice.class);
    unregister_chrdev_region(gDevice.number, 1);

    printk(KERN_INFO "zero_cache: exit\n");
}

module_init(zc_init);
module_exit(zc_exit);

